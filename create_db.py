import sqlite3
import hashlib
import os
from datetime import datetime

def hash_password(password):
    """Hash password with salt"""
    salt = "flood_monitor_salt_2024"
    return hashlib.sha256((password + salt).encode()).hexdigest()

def create_database():
    """Create the SQLite database with comprehensive user info"""
    db_path = 'flood_monitor.db'
    
    # Remove existing database if it exists
    if os.path.exists(db_path):
        os.remove(db_path)
        print("🗑️ Removed existing database")
    
    conn = sqlite3.connect(db_path)
    cursor = conn.cursor()
    
    print("📊 Creating database tables...")
    
    # Create comprehensive users table
    cursor.execute('''
        CREATE TABLE users (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            username TEXT UNIQUE NOT NULL,
            email TEXT UNIQUE NOT NULL,
            password_hash TEXT NOT NULL,
            first_name TEXT,
            last_name TEXT,
            full_name TEXT,
            phone_number TEXT,
            address TEXT,
            city TEXT,
            country TEXT DEFAULT 'Philippines',
            role TEXT DEFAULT 'user',
            is_active INTEGER DEFAULT 1,
            email_verified INTEGER DEFAULT 0,
            profile_image TEXT,
            date_of_birth DATE,
            gender TEXT,
            emergency_contact TEXT,
            emergency_phone TEXT,
            created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
            updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
            last_login TIMESTAMP NULL,
            login_count INTEGER DEFAULT 0
        )
    ''')
    
    # Create sessions table
    cursor.execute('''
        CREATE TABLE sessions (
            session_id TEXT PRIMARY KEY,
            user_id INTEGER,
            created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
            expires_at TIMESTAMP NOT NULL,
            ip_address TEXT,
            user_agent TEXT,
            device_info TEXT,
            location TEXT,
            is_active INTEGER DEFAULT 1,
            FOREIGN KEY (user_id) REFERENCES users (id) ON DELETE CASCADE
        )
    ''')
    
    # Create user_logs table for comprehensive activity tracking
    cursor.execute('''
        CREATE TABLE user_logs (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            user_id INTEGER,
            action TEXT NOT NULL,
            ip_address TEXT,
            user_agent TEXT,
            timestamp TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
            details TEXT,
            success INTEGER DEFAULT 1,
            FOREIGN KEY (user_id) REFERENCES users (id) ON DELETE CASCADE
        )
    ''')
    
    # Create user_preferences table
    cursor.execute('''
        CREATE TABLE user_preferences (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            user_id INTEGER UNIQUE,
            theme TEXT DEFAULT 'light',
            language TEXT DEFAULT 'en',
            timezone TEXT DEFAULT 'Asia/Manila',
            notifications_email INTEGER DEFAULT 1,
            notifications_sms INTEGER DEFAULT 0,
            alert_threshold INTEGER DEFAULT 80,
            created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
            updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
            FOREIGN KEY (user_id) REFERENCES users (id) ON DELETE CASCADE
        )
    ''')
    
    print("👤 Creating default users with full information...")
    
    # Create comprehensive admin user
    admin_password = "admin123"
    admin_hash = hash_password(admin_password)
    
    cursor.execute('''
        INSERT INTO users (
            username, email, password_hash, first_name, last_name, full_name,
            phone_number, address, city, role, email_verified
        ) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)
    ''', (
        'admin', 
        'admin@floodmonitor.com', 
        admin_hash, 
        'System', 
        'Administrator',
        'System Administrator',
        '+63 912 345 6789',
        '123 Main Street, Barangay 1',
        'Manila',
        'admin',
        1
    ))
    
    admin_id = cursor.lastrowid
    
    # Create admin preferences
    cursor.execute('''
        INSERT INTO user_preferences (user_id, alert_threshold, notifications_email, notifications_sms)
        VALUES (?, ?, ?, ?)
    ''', (admin_id, 75, 1, 1))
    
    # Create test user with full info
    user_password = "user123"
    user_hash = hash_password(user_password)
    
    cursor.execute('''
        INSERT INTO users (
            username, email, password_hash, first_name, last_name, full_name,
            phone_number, address, city, role, gender, date_of_birth
        ) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)
    ''', (
        'testuser', 
        'user@floodmonitor.com', 
        user_hash,
        'John',
        'Doe', 
        'John Doe',
        '+63 917 123 4567',
        '456 Test Avenue, Barangay 2',
        'Quezon City',
        'user',
        'Male',
        '1990-01-01'
    ))
    
    user_id = cursor.lastrowid
    
    # Create user preferences
    cursor.execute('''
        INSERT INTO user_preferences (user_id, theme, alert_threshold)
        VALUES (?, ?, ?)
    ''', (user_id, 'dark', 85))
    
    # Create indexes for better performance
    cursor.execute('CREATE INDEX idx_users_username ON users(username)')
    cursor.execute('CREATE INDEX idx_users_email ON users(email)')
    cursor.execute('CREATE INDEX idx_users_active ON users(is_active)')
    cursor.execute('CREATE INDEX idx_sessions_user_id ON sessions(user_id)')
    cursor.execute('CREATE INDEX idx_sessions_expires ON sessions(expires_at)')
    cursor.execute('CREATE INDEX idx_logs_user_id ON user_logs(user_id)')
    cursor.execute('CREATE INDEX idx_logs_action ON user_logs(action)')
    
    # Create trigger to update updated_at timestamp
    cursor.execute('''
        CREATE TRIGGER update_users_timestamp 
        AFTER UPDATE ON users
        BEGIN
            UPDATE users SET updated_at = CURRENT_TIMESTAMP WHERE id = NEW.id;
        END
    ''')
    
    conn.commit()
    
    # Verify database creation
    cursor.execute("SELECT name FROM sqlite_master WHERE type='table'")
    tables = cursor.fetchall()
    
    cursor.execute("SELECT COUNT(*) FROM users")
    user_count = cursor.fetchone()[0]
    
    conn.close()
    
    print("✅ Database created successfully!")
    print(f"📁 Database file: {os.path.abspath(db_path)}")
    print(f"📋 Tables: {', '.join([table[0] for table in tables])}")
    print(f"👥 Users created: {user_count}")
    print("\n🔑 Default Login Credentials:")
    print("   Admin: admin / admin123")
    print("   User:  testuser / user123")
    print("\n📊 Database Features:")
    print("   ✅ Comprehensive user profiles")
    print("   ✅ Session management")
    print("   ✅ Activity logging")
    print("   ✅ User preferences")
    print("   ✅ Auto-updating timestamps")

def view_all_users():
    """View all user information in the database"""
    if not os.path.exists('flood_monitor.db'):
        print("❌ Database not found. Run create_database() first.")
        return
    
    conn = sqlite3.connect('flood_monitor.db')
    cursor = conn.cursor()
    
    print("\n📊 All User Information:")
    print("=" * 80)
    
    cursor.execute('''
        SELECT 
            id, username, email, first_name, last_name, full_name,
            phone_number, address, city, role, is_active, 
            email_verified, created_at, last_login, login_count
        FROM users ORDER BY created_at
    ''')
    
    users = cursor.fetchall()
    
    for user in users:
        print(f"👤 User ID: {user[0]}")
        print(f"   Username: {user[1]}")
        print(f"   Email: {user[2]}")
        print(f"   Name: {user[5] if user[5] else f'{user[3]} {user[4]}'}")
        print(f"   Phone: {user[6] if user[6] else 'Not provided'}")
        print(f"   Address: {user[7] if user[7] else 'Not provided'}")
        print(f"   City: {user[8] if user[8] else 'Not provided'}")
        print(f"   Role: {user[9]}")
        print(f"   Status: {'Active' if user[10] else 'Inactive'}")
        print(f"   Email Verified: {'Yes' if user[11] else 'No'}")
        print(f"   Registered: {user[12]}")
        print(f"   Last Login: {user[13] if user[13] else 'Never'}")
        print(f"   Login Count: {user[14]}")
        print("-" * 40)
    
    conn.close()

if __name__ == "__main__":
    print("🌊 Comprehensive Flood Monitor Database Setup")
    print("=" * 50)
    
    choice = input("\n1. Create new database\n2. View all users\n3. Both\nChoose (1/2/3): ").strip()
    
    if choice == "1":
        create_database()
    elif choice == "2":
        view_all_users()
    elif choice == "3":
        create_database()
        view_all_users()
    else:
        print("Invalid choice. Creating new database...")
        create_database()
