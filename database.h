#pragma once
#include <WiFi.h>
#include <FS.h>
#include <SPIFFS.h>
#include <LittleFS.h>
#include <ArduinoJson.h>
#include <mbedtls/md.h>

class DatabaseManager {
private:
    // Use LittleFS instead of SPIFFS for better performance
    fs::FS* filesystem;
    bool useInternalStorage;
    
    String hashPassword(String password) {
        byte shaResult[32];
        mbedtls_md_context_t ctx;
        mbedtls_md_type_t md_type = MBEDTLS_MD_SHA256;
        
        mbedtls_md_init(&ctx);
        mbedtls_md_setup(&ctx, mbedtls_md_info_from_type(md_type), 0);
        mbedtls_md_starts(&ctx);
        mbedtls_md_update(&ctx, (const unsigned char*)password.c_str(), password.length());
        mbedtls_md_finish(&ctx, shaResult);
        mbedtls_md_free(&ctx);
        
        String hashedPassword = "";
        for(int i = 0; i < 32; i++) {
            if(shaResult[i] < 16) hashedPassword += "0";
            hashedPassword += String(shaResult[i], HEX);
        }
        return hashedPassword;
    }

    bool writeToFile(String filename, String data) {
        File file = filesystem->open(filename, FILE_WRITE);
        if (!file) {
            Serial.println("Failed to open file for writing: " + filename);
            return false;
        }
        file.print(data);
        file.close();
        Serial.println("Written to file: " + filename + " (" + String(data.length()) + " bytes)");
        return true;
    }

    String readFromFile(String filename) {
        File file = filesystem->open(filename, FILE_READ);
        if (!file) {
            Serial.println("Failed to open file for reading: " + filename);
            return "";
        }
        String content = file.readString();
        file.close();
        return content;
    }

public:
    DatabaseManager(bool internal = true) {
        useInternalStorage = internal;
        filesystem = internal ? &LittleFS : &SPIFFS;
    }

    bool initializeDatabase() {
        // Initialize filesystem based on choice
        bool fsInitialized = false;
        
        if (useInternalStorage) {
            fsInitialized = LittleFS.begin(true);
            Serial.println("Using LittleFS (Internal Flash Storage)");
        } else {
            fsInitialized = SPIFFS.begin(true);
            Serial.println("Using SPIFFS (External Storage)");
        }
        
        if (!fsInitialized) {
            Serial.println("Filesystem Mount Failed");
            return false;
        }
        
        // Show storage info
        printStorageInfo();
        
        // Create database files directly on ESP32
        createDatabaseFiles();
        
        Serial.println("Database files initialized on ESP32 internal storage");
        return true;
    }
    
    void printStorageInfo() {
        size_t totalBytes = filesystem->totalBytes();
        size_t usedBytes = filesystem->usedBytes();
        size_t freeBytes = totalBytes - usedBytes;
        
        Serial.println("=== ESP32 Storage Info ===");
        Serial.printf("Total: %u bytes (%.2f MB)\n", totalBytes, totalBytes / 1024.0 / 1024.0);
        Serial.printf("Used:  %u bytes (%.2f MB)\n", usedBytes, usedBytes / 1024.0 / 1024.0);
        Serial.printf("Free:  %u bytes (%.2f MB)\n", freeBytes, freeBytes / 1024.0 / 1024.0);
        Serial.printf("Usage: %.1f%%\n", (usedBytes * 100.0) / totalBytes);
        Serial.println("==========================");
    }
    
    bool createDatabaseFiles() {
        // Create users database with default admin
        createUsersDB();
        
        // Create sensors database with activity logging table
        createSensorsDB();
        
        // Create configuration database
        createConfigDB();
        
        return true;
    }
    
    bool createUsersDB() {
        String usersData = R"([
  {
    "id": 1,
    "username": "admin",
    "email": "admin@floodmonitor.esp32",
    "password": ")" + hashPassword("admin123") + R"(",
    "role": "administrator",
    "created": )" + String(millis()) + R"(,
    "is_active": true
  },
  {
    "id": 2,
    "username": "operator",
    "email": "operator@floodmonitor.esp32",
    "password": ")" + hashPassword("operator123") + R"(",
    "role": "operator",
    "created": )" + String(millis()) + R"(,
    "is_active": true
  }
])";
        
        return writeToFile("/users.db", usersData);
    }
    
    bool createSensorsDB() {
        String sensorsData = R"([
  {
    "id": 1,
    "timestamp": )" + String(millis()) + R"(,
    "waterLevel": 15.5,
    "gateStatus": "CLOSED",
    "temperature": 25.2,
    "humidity": 68.3,
    "rainStatus": "NO_RAIN",
    "lightValue": 420,
    "location": "ESP32_INTERNAL"
  }
])";
        
        return writeToFile("/sensors.db", sensorsData);
    }
    
    bool createConfigDB() {
        String configData = R"({
  "version": "1.0.0",
  "created": )" + String(millis()) + R"(",
  "storage_type": "ESP32_INTERNAL",
  "database": {
    "max_users": 50,
    "max_sensor_records": 500,
    "auto_cleanup": true,
    "cleanup_threshold": 450
  },
  "system": {
    "device_name": "FloodMonitor_ESP32",
    "wifi_ssid": "FloodMonitor_Network",
    "wifi_password": "12345678",
    "admin_timeout": 1800000,
    "sensor_interval": 15000
  },
  "sensors": {
    "water_level_pin": 2,
    "temperature_pin": 4,
    "humidity_pin": 4,
    "rain_pin": 5,
    "light_pin": 34,
    "gate_control_pin": 18,
    "gate_feedback_pin": 19
  },
  "thresholds": {
    "water_level_critical": 85.0,
    "water_level_warning": 65.0,
    "temperature_max": 50.0,
    "humidity_max": 90.0
  }
})";
        
        return writeToFile("/config.db", configData);
    }
    
    bool logSensorData(float waterLevel, String gateStatus, float temperature, float humidity, String rainStatus, int lightValue) {
        String content = readFromFile("/sensors.db");
        if (content == "") content = "[]";
        
        DynamicJsonDocument sensors(16384); // Increased buffer for ESP32
        DeserializationError error = deserializeJson(sensors, content);
        if (error) {
            Serial.println("Failed to parse sensor database");
            return false;
        }
        
        // ESP32 memory management - keep fewer records
        while (sensors.size() >= 200) {
            sensors.remove(0);
        }
        
        JsonObject newData = sensors.createNestedObject();
        newData["id"] = sensors.size() + 1;
        newData["timestamp"] = millis();
        newData["waterLevel"] = waterLevel;
        newData["gateStatus"] = gateStatus;
        newData["temperature"] = temperature;
        newData["humidity"] = humidity;
        newData["rainStatus"] = rainStatus;
        newData["lightValue"] = lightValue;
        newData["free_heap"] = ESP.getFreeHeap();
        newData["uptime"] = millis();
        
        String output;
        serializeJson(sensors, output);
        
        bool success = writeToFile("/sensors.db", output);
        
        if (success) {
            Serial.printf("Sensor data logged: W:%0.1f%% T:%0.1f°C H:%0.1f%% L:%d\n", 
                         waterLevel, temperature, humidity, lightValue);
        }
        
        return success;
    }
    
    bool logActivity(String action, String username, String details, int userId = 0) {
        String content = readFromFile("/activity.db");
        if (content == "") content = "[]";
        
        DynamicJsonDocument activities(8192);
        DeserializationError error = deserializeJson(activities, content);
        if (error) {
            Serial.println("Failed to parse activity database");
            return false;
        }
        
        // Keep only last 100 activities for ESP32 memory
        while (activities.size() >= 100) {
            activities.remove(0);
        }
        
        JsonObject newActivity = activities.createNestedObject();
        newActivity["id"] = activities.size() + 1;
        newActivity["timestamp"] = millis();
        newActivity["action"] = action;
        newActivity["username"] = username;
        newActivity["user_id"] = userId;
        newActivity["details"] = details;
        newActivity["ip"] = WiFi.localIP().toString();
        newActivity["free_heap"] = ESP.getFreeHeap();
        
        String output;
        serializeJson(activities, output);
        
        bool success = writeToFile("/activity.db", output);
        
        if (success) {
            Serial.printf("Activity logged: %s by %s\n", action.c_str(), username.c_str());
        }
        
        return success;
    }
    
    String getStorageStatus() {
        size_t totalBytes = filesystem->totalBytes();
        size_t usedBytes = filesystem->usedBytes();
        
        DynamicJsonDocument status(1024);
        status["storage_type"] = useInternalStorage ? "LittleFS" : "SPIFFS";
        status["total_bytes"] = totalBytes;
        status["used_bytes"] = usedBytes;
        status["free_bytes"] = totalBytes - usedBytes;
        status["usage_percent"] = (usedBytes * 100.0) / totalBytes;
        
        // Count records in each database
        status["user_count"] = countRecords("/users.db");
        status["sensor_count"] = countRecords("/sensors.db");
        status["activity_count"] = countRecords("/activity.db");
        
        // ESP32 system info
        status["chip_model"] = ESP.getChipModel();
        status["chip_revision"] = ESP.getChipRevision();
        status["cpu_freq"] = ESP.getCpuFreqMHz();
        status["flash_size"] = ESP.getFlashChipSize();
        status["free_heap"] = ESP.getFreeHeap();
        status["uptime"] = millis();
        
        String output;
        serializeJson(status, output);
        return output;
    }
    
    int countRecords(String filename) {
        String content = readFromFile(filename);
        if (content == "") return 0;
        
        DynamicJsonDocument doc(4096);
        DeserializationError error = deserializeJson(doc, content);
        if (error) return -1;
        
        if (doc.is<JsonArray>()) {
            return doc.size();
        } else if (doc.is<JsonObject>()) {
            return 1;
        }
        
        return 0;
    }
    
    bool backupToSD() {
        // If SD card is available, backup databases
        // This would require SD card library
        Serial.println("SD backup not implemented yet");
        return false;
    }
    
    bool factoryReset() {
        Serial.println("Performing factory reset...");
        
        // Remove all database files
        filesystem->remove("/users.db");
        filesystem->remove("/sensors.db");
        filesystem->remove("/activity.db");
        filesystem->remove("/config.db");
        
        // Recreate with defaults
        createDatabaseFiles();
        
        Serial.println("Factory reset completed");
        return true;
    }
    
    bool registerUser(String username, String email, String password) {
        if (userExists(username, email)) {
            Serial.println("User already exists: " + username);
            return false;
        }
        
        String content = readFromFile("/users.db");
        if (content == "") content = "[]";
        
        DynamicJsonDocument users(8192);
        DeserializationError error = deserializeJson(users, content);
        if (error) {
            Serial.println("Failed to parse users database");
            return false;
        }
        
        JsonObject newUser = users.createNestedObject();
        newUser["id"] = users.size() + 1;
        newUser["username"] = username;
        newUser["email"] = email;
        newUser["password"] = hashPassword(password);
        newUser["role"] = "user";
        newUser["created"] = millis();
        newUser["is_active"] = true;
        
        String output;
        serializeJson(users, output);
        
        if (writeToFile("/users.db", output)) {
            Serial.printf("User registered successfully: %s\n", username.c_str());
            logActivity("USER_REGISTERED", username, "New user account created");
            return true;
        }
        
        Serial.println("Failed to write user to database");
        return false;
    }
    
    bool validateLogin(String username, String password) {
        String content = readFromFile("/users.db");
        if (content == "") return false;
        
        DynamicJsonDocument users(8192);
        DeserializationError error = deserializeJson(users, content);
        if (error) return false;
        
        String hashedPassword = hashPassword(password);
        
        for (JsonObject user : users.as<JsonArray>()) {
            String userUsername = user["username"].as<String>();
            String userEmail = user["email"].as<String>();
            String userPassword = user["password"].as<String>();
            bool isActive = user["is_active"].as<bool>();
            
            if ((userUsername == username || userEmail == username) && 
                userPassword == hashedPassword && isActive) {
                Serial.printf("Login successful for: %s\n", username.c_str());
                logActivity("USER_LOGIN", username, "Successful login");
                return true;
            }
        }
        
        Serial.printf("Login failed for: %s\n", username.c_str());
        logActivity("LOGIN_FAILED", username, "Invalid credentials");
        return false;
    }
    
    String getUsername(String usernameOrEmail) {
        String content = readFromFile("/users.db");
        if (content == "") return "";
        
        DynamicJsonDocument users(8192);
        DeserializationError error = deserializeJson(users, content);
        if (error) return "";
        
        for (JsonObject user : users.as<JsonArray>()) {
            String userUsername = user["username"].as<String>();
            String userEmail = user["email"].as<String>();
            
            if (userUsername == usernameOrEmail || userEmail == usernameOrEmail) {
                return userUsername;
            }
        }
        
        return "";
    }
    
    bool userExists(String username, String email) {
        String content = readFromFile("/users.db");
        if (content == "") return false;
        
        DynamicJsonDocument users(8192);
        DeserializationError error = deserializeJson(users, content);
        if (error) return false;
        
        for (JsonObject user : users.as<JsonArray>()) {
            String userUsername = user["username"].as<String>();
            String userEmail = user["email"].as<String>();
            
            if (userUsername == username || userEmail == email) {
                return true;
            }
        }
        
        return false;
    }
    
    String getSensorData(int limit = 50) {
        String content = readFromFile("/sensors.db");
        if (content == "") return "[]";
        
        DynamicJsonDocument sensors(16384);
        DeserializationError error = deserializeJson(sensors, content);
        if (error) return "[]";
        
        // Return last 'limit' records
        DynamicJsonDocument result(16384);
        JsonArray resultArray = result.to<JsonArray>();
        
        int total = sensors.size();
        int start = max(0, total - limit);
        
        for (int i = start; i < total; i++) {
            resultArray.add(sensors[i]);
        }
        
        String output;
        serializeJson(result, output);
        return output;
    }
    
    String getActivityLogs(int limit = 50) {
        String content = readFromFile("/activity.db");
        if (content == "") return "[]";
        
        DynamicJsonDocument activities(8192);
        DeserializationError error = deserializeJson(activities, content);
        if (error) return "[]";
        
        // Return last 'limit' records
        DynamicJsonDocument result(8192);
        JsonArray resultArray = result.to<JsonArray>();
        
        int total = activities.size();
        int start = max(0, total - limit);
        
        for (int i = start; i < total; i++) {
            resultArray.add(activities[i]);
        }
        
        String output;
        serializeJson(result, output);
        return output;
    }
    
    // ...existing code...
};