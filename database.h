#pragma once
#include <WiFi.h>
#include <FS.h>
#include <SPIFFS.h>
#include <LittleFS.h>
#include <ArduinoJson.h>
#include <mbedtls/md.h>
#include <time.h>

class DatabaseManager {
private:
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
        if (internal) {
            filesystem = &LittleFS;
        } else {
            filesystem = &SPIFFS;
        }
    }

    bool initializeDatabase() {
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
        
        printStorageInfo();
        createDatabaseFiles();
        Serial.println("Database system ready");
        return true;
    }
    
    void printStorageInfo() {
        size_t totalBytes = useInternalStorage ? LittleFS.totalBytes() : SPIFFS.totalBytes();
        size_t usedBytes = useInternalStorage ? LittleFS.usedBytes() : SPIFFS.usedBytes();
        
        Serial.printf("Storage: %u / %u bytes used\n", usedBytes, totalBytes);
    }
    
    bool createDatabaseFiles() {
        createUsersDB();
        createSensorsDB();
        createConfigDB();
        return true;
    }
    
    bool createUsersDB() {
        if (filesystem->exists("/users.db")) {
            Serial.println("Users DB exists. Skipping creation.");
            return true;
        }
        
        Serial.println("Creating new Users DB...");
        String usersData = R"([
  {
    "id": 1,
    "username": "admin",
    "email": "admin@floodmonitor.esp32",
    "password": ")" + hashPassword("admin123") + R"(",
    "role": "administrator",
    "created": )" + String(millis()) + R"(,
    "is_active": true
  }
])";
        return writeToFile("/users.db", usersData);
    }
    
    bool createSensorsDB() {
        if (filesystem->exists("/sensors.db")) {
            Serial.println("Sensors DB exists. Preserving history.");
            return true;
        }

        Serial.println("Creating new Sensors DB...");
        String sensorsData = "[]"; 
        return writeToFile("/sensors.db", sensorsData);
    }
    
    bool createConfigDB() {
        if (filesystem->exists("/config.db")) {
            return true;
        }
        
        String configData = R"({
  "version": "1.0.0",
  "storage_type": "ESP32_INTERNAL",
  "system": {
    "device_name": "FloodMonitor_ESP32",
    "wifi_ssid": "FloodMonitor_Network"
  }
})";
        return writeToFile("/config.db", configData);
    }
    
    // --- Data Logging Functions (UPDATED FOR TIME SYNC) ---
    
    bool logSensorData(float waterLevel, String gateStatus, float temperature, float humidity, String rainStatus, int lightValue) {
        String content = readFromFile("/sensors.db");
        if (content == "") content = "[]";
        
        DynamicJsonDocument sensors(24000); // Increased buffer
        DeserializationError error = deserializeJson(sensors, content);
        if (error) {
            Serial.println("DB Parse Error (Resetting DB)");
            filesystem->remove("/sensors.db"); 
            return false;
        }
        
        // Keep only last 500 records
        while (sensors.size() >= 500) {
            sensors.remove(0);
        }
        
        JsonObject newData = sensors.createNestedObject();
        newData["id"] = sensors.size() + 1;
        
        // --- KEY CHANGE: Use Real Time (Seconds since 1970) ---
        time_t now;
        time(&now); // Get current time from ESP32 internal clock
        newData["timestamp"] = (unsigned long)now; 
        
        newData["waterLevel"] = waterLevel;
        newData["gateStatus"] = gateStatus;
        newData["temperature"] = temperature;
        newData["humidity"] = humidity;
        newData["rainStatus"] = rainStatus;
        newData["lightValue"] = lightValue;
        
        String output;
        serializeJson(sensors, output);
        return writeToFile("/sensors.db", output);
    }
    
    bool logActivity(String action, String username, String details, int userId = 0) {
        String content = readFromFile("/activity.db");
        if (content == "") content = "[]";
        
        DynamicJsonDocument activities(8192);
        DeserializationError error = deserializeJson(activities, content);
        if (error) return false;
        
        while (activities.size() >= 100) {
            activities.remove(0);
        }
        
        JsonObject newActivity = activities.createNestedObject();
        newActivity["action"] = action;
        newActivity["username"] = username;
        newActivity["details"] = details;
        newActivity["timestamp"] = millis(); // Activity logs can stay on millis for now
        
        String output;
        serializeJson(activities, output);
        return writeToFile("/activity.db", output);
    }
    
    String getStorageStatus() {
        size_t totalBytes = useInternalStorage ? LittleFS.totalBytes() : SPIFFS.totalBytes();
        size_t usedBytes = useInternalStorage ? LittleFS.usedBytes() : SPIFFS.usedBytes();
        
        DynamicJsonDocument status(1024);
        status["storage_type"] = useInternalStorage ? "LittleFS" : "SPIFFS";
        status["total_bytes"] = totalBytes;
        status["used_bytes"] = usedBytes;
        status["user_count"] = countRecords("/users.db");
        status["sensor_count"] = countRecords("/sensors.db");
        status["uptime"] = millis();
        
        String output;
        serializeJson(status, output);
        return output;
    }
    
    int countRecords(String filename) {
        String content = readFromFile(filename);
        if (content == "") return 0;
        DynamicJsonDocument doc(4096);
        deserializeJson(doc, content);
        return doc.size();
    }
    
    bool factoryReset() {
        Serial.println("Performing factory reset...");
        filesystem->remove("/users.db");
        filesystem->remove("/sensors.db");
        filesystem->remove("/activity.db");
        filesystem->remove("/config.db");
        createUsersDB();
        createSensorsDB(); 
        createConfigDB();
        return true;
    }
    
    // --- User Auth Functions ---
    
    bool registerUser(String username, String email, String password) {
        if (userExists(username, email)) return false;
        
        String content = readFromFile("/users.db");
        if (content == "") content = "[]";
        DynamicJsonDocument users(8192);
        deserializeJson(users, content);
        
        JsonObject newUser = users.createNestedObject();
        newUser["username"] = username;
        newUser["email"] = email;
        newUser["password"] = hashPassword(password);
        newUser["is_active"] = true;
        
        String output;
        serializeJson(users, output);
        return writeToFile("/users.db", output);
    }
    
    bool validateLogin(String username, String password) {
        String content = readFromFile("/users.db");
        DynamicJsonDocument users(8192);
        deserializeJson(users, content);
        String hashed = hashPassword(password);
        
        for (JsonObject user : users.as<JsonArray>()) {
            String u = user["username"].as<String>();
            String p = user["password"].as<String>();
            if (u == username && p == hashed) return true;
        }
        return false;
    }
    
    bool userExists(String username, String email) {
        String content = readFromFile("/users.db");
        DynamicJsonDocument users(8192);
        deserializeJson(users, content);
        for (JsonObject user : users.as<JsonArray>()) {
            String u = user["username"].as<String>();
            if (u == username) return true;
        }
        return false;
    }
    
    String getSensorData(int limit) {
        return readFromFile("/sensors.db"); 
    }
};