import sqlite3
import hashlib
import time
import os
from datetime import datetime

class DatabaseCreator:
    def __init__(self):
        self.output_dir = "."
        
    def hash_password(self, password):
        """Create SHA256 hash of password"""
        return hashlib.sha256(password.encode()).hexdigest()
    
    def create_users_db(self, with_admin=False):
        """Create SQLite users database file"""
        db_path = os.path.join(self.output_dir, "users.db")
        
        try:
            # Remove existing file
            if os.path.exists(db_path):
                os.remove(db_path)
            
            conn = sqlite3.connect(db_path)
            cursor = conn.cursor()
            
            # Create users table
            cursor.execute('''
                CREATE TABLE users (
                    id INTEGER PRIMARY KEY AUTOINCREMENT,
                    username TEXT UNIQUE NOT NULL,
                    email TEXT UNIQUE NOT NULL,
                    password TEXT NOT NULL,
                    role TEXT DEFAULT 'user',
                    created_at INTEGER DEFAULT (strftime('%s','now')),
                    last_login INTEGER,
                    is_active INTEGER DEFAULT 1
                )
            ''')
            
            # Create indexes
            cursor.execute('CREATE INDEX idx_users_username ON users(username)')
            cursor.execute('CREATE INDEX idx_users_email ON users(email)')
            
            if with_admin:
                # Insert default admin user (password: admin123)
                cursor.execute('''
                    INSERT INTO users (username, email, password, role, created_at)
                    VALUES (?, ?, ?, ?, ?)
                ''', ('admin', 'admin@floodmonitor.local', self.hash_password('admin123'), 'administrator', int(time.time())))
                
                # Insert test user (password: user123)
                cursor.execute('''
                    INSERT INTO users (username, email, password, role, created_at)
                    VALUES (?, ?, ?, ?, ?)
                ''', ('testuser', 'user@floodmonitor.local', self.hash_password('user123'), 'user', int(time.time())))
            
            conn.commit()
            conn.close()
            
            if with_admin:
                print("✓ users.db created with default users:")
                print("  - admin/admin123 (Administrator)")
                print("  - testuser/user123 (User)")
            else:
                print("✓ users.db created (empty SQLite database)")
            return True
            
        except Exception as e:
            print(f"✗ Error creating users.db: {e}")
            return False
    
    def create_sensors_db(self, with_sample=False):
        """Create SQLite sensor data database file"""
        db_path = os.path.join(self.output_dir, "sensors.db")
        
        try:
            # Remove existing file
            if os.path.exists(db_path):
                os.remove(db_path)
            
            conn = sqlite3.connect(db_path)
            cursor = conn.cursor()
            
            # Create sensor_data table
            cursor.execute('''
                CREATE TABLE sensor_data (
                    id INTEGER PRIMARY KEY AUTOINCREMENT,
                    timestamp INTEGER DEFAULT (strftime('%s','now')),
                    water_level REAL,
                    gate_status TEXT,
                    temperature REAL,
                    humidity REAL,
                    rain_status TEXT,
                    light_value INTEGER,
                    created_at DATETIME DEFAULT CURRENT_TIMESTAMP
                )
            ''')
            
            # Create alerts table
            cursor.execute('''
                CREATE TABLE alerts (
                    id INTEGER PRIMARY KEY AUTOINCREMENT,
                    alert_type TEXT NOT NULL,
                    severity TEXT NOT NULL,
                    message TEXT NOT NULL,
                    sensor_reading_id INTEGER,
                    acknowledged INTEGER DEFAULT 0,
                    created_at INTEGER DEFAULT (strftime('%s','now')),
                    FOREIGN KEY (sensor_reading_id) REFERENCES sensor_data(id)
                )
            ''')
            
            # Create indexes
            cursor.execute('CREATE INDEX idx_sensor_timestamp ON sensor_data(timestamp)')
            cursor.execute('CREATE INDEX idx_alerts_type ON alerts(alert_type)')
            cursor.execute('CREATE INDEX idx_alerts_severity ON alerts(severity)')
            
            if with_sample:
                # Insert sample sensor readings
                base_time = int(time.time())
                
                for i in range(10):
                    timestamp = base_time - (i * 60)  # Every minute backwards
                    cursor.execute('''
                        INSERT INTO sensor_data 
                        (timestamp, water_level, gate_status, temperature, humidity, rain_status, light_value)
                        VALUES (?, ?, ?, ?, ?, ?, ?)
                    ''', (
                        timestamp,
                        20.0 + (i * 2.5),
                        'CLOSED' if i % 2 == 0 else 'OPEN',
                        25.0 + (i * 0.5),
                        60.0 + (i * 1.2),
                        'NO_RAIN' if i < 5 else 'LIGHT_RAIN',
                        400 + (i * 10)
                    ))
                
                # Insert sample alert
                cursor.execute('''
                    INSERT INTO alerts (alert_type, severity, message, sensor_reading_id)
                    VALUES (?, ?, ?, ?)
                ''', ('WATER_LEVEL', 'WARNING', 'Water level approaching critical threshold', 1))
            
            conn.commit()
            conn.close()
            
            if with_sample:
                print("✓ sensors.db created with 10 sample readings and 1 alert")
            else:
                print("✓ sensors.db created (empty SQLite database)")
            return True
            
        except Exception as e:
            print(f"✗ Error creating sensors.db: {e}")
            return False
    
    def create_config_db(self):
        """Create SQLite configuration database file"""
        db_path = os.path.join(self.output_dir, "config.db")
        
        try:
            # Remove existing file
            if os.path.exists(db_path):
                os.remove(db_path)
            
            conn = sqlite3.connect(db_path)
            cursor = conn.cursor()
            
            # Create configuration table
            cursor.execute('''
                CREATE TABLE configuration (
                    id INTEGER PRIMARY KEY AUTOINCREMENT,
                    category TEXT NOT NULL,
                    key_name TEXT NOT NULL,
                    value_text TEXT,
                    value_number REAL,
                    value_boolean INTEGER,
                    description TEXT,
                    updated_at INTEGER DEFAULT (strftime('%s','now')),
                    UNIQUE(category, key_name)
                )
            ''')
            
            # Create system_info table
            cursor.execute('''
                CREATE TABLE system_info (
                    id INTEGER PRIMARY KEY,
                    version TEXT NOT NULL,
                    created_at INTEGER DEFAULT (strftime('%s','now')),
                    last_updated INTEGER DEFAULT (strftime('%s','now'))
                )
            ''')
            
            # Insert system info
            cursor.execute('''
                INSERT INTO system_info (id, version) VALUES (1, ?)
            ''', ('1.0.0',))
            
            # Insert configuration values
            configs = [
                ('database', 'max_users', None, 100, None, 'Maximum number of users allowed'),
                ('database', 'max_sensor_records', None, 1000, None, 'Maximum sensor records to keep'),
                ('database', 'auto_cleanup', None, None, 1, 'Enable automatic cleanup'),
                ('database', 'cleanup_threshold', None, 900, None, 'Cleanup when records exceed this number'),
                
                ('system', 'wifi_ssid', 'FloodMonitor_Network', None, None, 'WiFi network name'),
                ('system', 'wifi_password', '12345678', None, None, 'WiFi password'),
                ('system', 'admin_timeout', None, 3600000, None, 'Admin session timeout in milliseconds'),
                ('system', 'sensor_interval', None, 30000, None, 'Sensor reading interval in milliseconds'),
                
                ('thresholds', 'water_level_critical', None, 80.0, None, 'Critical water level percentage'),
                ('thresholds', 'water_level_warning', None, 60.0, None, 'Warning water level percentage'),
                ('thresholds', 'temperature_max', None, 45.0, None, 'Maximum temperature threshold'),
                ('thresholds', 'humidity_max', None, 95.0, None, 'Maximum humidity threshold'),
            ]
            
            cursor.executemany('''
                INSERT INTO configuration (category, key_name, value_text, value_number, value_boolean, description)
                VALUES (?, ?, ?, ?, ?, ?)
            ''', configs)
            
            conn.commit()
            conn.close()
            
            print("✓ config.db created with system settings (SQLite)")
            return True
            
        except Exception as e:
            print(f"✗ Error creating config.db: {e}")
            return False
    
    def create_logs_db(self):
        """Create SQLite system logs database file"""
        db_path = os.path.join(self.output_dir, "logs.db")
        
        try:
            # Remove existing file
            if os.path.exists(db_path):
                os.remove(db_path)
            
            conn = sqlite3.connect(db_path)
            cursor = conn.cursor()
            
            # Create logs table
            cursor.execute('''
                CREATE TABLE system_logs (
                    id INTEGER PRIMARY KEY AUTOINCREMENT,
                    timestamp INTEGER DEFAULT (strftime('%s','now')),
                    level TEXT NOT NULL,
                    component TEXT NOT NULL,
                    message TEXT NOT NULL,
                    details TEXT,
                    user_id INTEGER,
                    ip_address TEXT,
                    created_at DATETIME DEFAULT CURRENT_TIMESTAMP
                )
            ''')
            
            # Create indexes
            cursor.execute('CREATE INDEX idx_logs_timestamp ON system_logs(timestamp)')
            cursor.execute('CREATE INDEX idx_logs_level ON system_logs(level)')
            cursor.execute('CREATE INDEX idx_logs_component ON system_logs(component)')
            
            # Insert initial log
            cursor.execute('''
                INSERT INTO system_logs (level, component, message, details)
                VALUES (?, ?, ?, ?)
            ''', ('INFO', 'SYSTEM', 'Database files initialized', '{"version": "1.0.0"}'))
            
            conn.commit()
            conn.close()
            
            print("✓ logs.db created with initial log entry (SQLite)")
            return True
            
        except Exception as e:
            print(f"✗ Error creating logs.db: {e}")
            return False
    
    def show_menu(self):
        """Display interactive menu"""
        print("\n" + "="*50)
        print("🌊 Flood Monitor Database Creator")
        print("="*50)
        print("1. Create empty databases")
        print("2. Create databases with sample data")
        print("3. Create only users.db (empty)")
        print("4. Create only users.db (with admin)")
        print("5. Create only sensors.db")
        print("6. Create only config.db")
        print("7. Create all files (production ready)")
        print("8. Show existing database info")
        print("9. Delete all database files")
        print("0. Exit")
        print("-"*50)
    
    def show_database_info(self):
        """Show information about existing SQLite database files"""
        db_files = ["users.db", "sensors.db", "config.db", "logs.db"]
        
        print("\n📊 SQLite Database Files Information:")
        print("-"*50)
        
        for db_file in db_files:
            file_path = os.path.join(self.output_dir, db_file)
            if os.path.exists(file_path):
                size = os.path.getsize(file_path)
                modified = datetime.fromtimestamp(os.path.getmtime(file_path))
                print(f"✓ {db_file:<12} {size:>6} bytes  {modified.strftime('%Y-%m-%d %H:%M')}")
                
                # Show table info for SQLite files
                try:
                    conn = sqlite3.connect(file_path)
                    cursor = conn.cursor()
                    cursor.execute("SELECT name FROM sqlite_master WHERE type='table'")
                    tables = cursor.fetchall()
                    
                    for table in tables:
                        table_name = table[0]
                        cursor.execute(f"SELECT COUNT(*) FROM {table_name}")
                        count = cursor.fetchone()[0]
                        print(f"  └─ Table {table_name}: {count} records")
                    
                    conn.close()
                except Exception as e:
                    print(f"  └─ Error reading SQLite file: {e}")
            else:
                print(f"✗ {db_file:<12} Not found")
        print()
    
    def delete_all_files(self):
        """Delete all database files"""
        db_files = ["users.db", "sensors.db", "config.db", "logs.db"]
        deleted = 0
        
        for db_file in db_files:
            file_path = os.path.join(self.output_dir, db_file)
            try:
                if os.path.exists(file_path):
                    os.remove(file_path)
                    print(f"✓ Deleted {db_file}")
                    deleted += 1
            except Exception as e:
                print(f"✗ Error deleting {db_file}: {e}")
        
        if deleted > 0:
            print(f"\n🗑️ Deleted {deleted} database files")
        else:
            print("\n📝 No database files found to delete")
    
    def run(self):
        """Run the interactive database creator"""
        while True:
            self.show_menu()
            
            try:
                choice = input("Enter your choice (0-9): ").strip()
                
                if choice == "0":
                    print("\n👋 Goodbye!")
                    break
                
                elif choice == "1":
                    print("\n🔧 Creating empty databases...")
                    self.create_users_db(False)
                    self.create_sensors_db(False)
                    self.create_config_db()
                    self.create_logs_db()
                
                elif choice == "2":
                    print("\n🔧 Creating databases with sample data...")
                    self.create_users_db(True)
                    self.create_sensors_db(True)
                    self.create_config_db()
                    self.create_logs_db()
                
                elif choice == "3":
                    print("\n🔧 Creating empty users.db...")
                    self.create_users_db(False)
                
                elif choice == "4":
                    print("\n🔧 Creating users.db with admin...")
                    self.create_users_db(True)
                
                elif choice == "5":
                    print("\n🔧 Creating sensors.db...")
                    self.create_sensors_db(True)
                
                elif choice == "6":
                    print("\n🔧 Creating config.db...")
                    self.create_config_db()
                
                elif choice == "7":
                    print("\n🔧 Creating production-ready databases...")
                    self.create_users_db(True)
                    self.create_sensors_db(False)
                    self.create_config_db()
                    self.create_logs_db()
                    print("\n🎉 Production databases created successfully!")
                    print("📋 Default login: admin/admin123")
                
                elif choice == "8":
                    self.show_database_info()
                
                elif choice == "9":
                    confirm = input("⚠️  Delete all database files? (y/N): ").strip().lower()
                    if confirm == 'y':
                        self.delete_all_files()
                
                else:
                    print("❌ Invalid choice. Please try again.")
                
                if choice in "1234567":
                    print(f"\n✅ Operation completed!")
                    print("📁 Copy the .db files to your ESP32 SPIFFS partition")
                
                input("\nPress Enter to continue...")
                
            except KeyboardInterrupt:
                print("\n\n👋 Interrupted by user. Goodbye!")
                break
            except Exception as e:
                print(f"\n❌ Error: {e}")
                input("Press Enter to continue...")

if __name__ == "__main__":
    creator = DatabaseCreator()
    creator.run()
