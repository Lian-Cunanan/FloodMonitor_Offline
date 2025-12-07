/*
 * FLOOD MONITORING SYSTEM
<<<<<<< HEAD
 * Professional ESP32-based Flood Monitor with Database Integration
 * 
 * Author: Lian Cunanan
 * GitHub: https://github.com/Lian Cunanan
 * Email: liancunanan2@gmail.com
 * 
 * Features:
 * - Real-time sensor monitoring (Water, Temperature, Humidity, Rain, Light)
 * - Automatic flood gate control with configurable thresholds
 * - Professional responsive web interface with captive portal
 * - Internal LittleFS database with 10-minute data logging
 * - User authentication and activity tracking
 * - Three operation modes: AUTO, MAINTENANCE, SLEEP
 * - WebSocket real-time data streaming
 * - Factory reset and system status monitoring
 * 
 * Hardware Requirements:
 * - ESP32 Development Board
 * - Ultrasonic Water Level Sensor (HC-SR04)
 * - DHT22 Temperature/Humidity Sensor
 * - Rain Detection Sensor
 * - LDR Light Sensor
 * - Servo Motor for Gate Control
 * 
 * Compliant with CPE 414 Exam Requirements
 * Includes CAPTIVE PORTAL (Auto-Redirect)
 * 
 * License: MIT
 * Version: 1.0.0
 * Last Updated: December 2024
=======
 * Compliant with CPE 414 Exam Requirements
 * Includes CAPTIVE PORTAL (Auto-Redirect)
>>>>>>> d5a1704f3b13828ef3fbae00aa481f41e2ef0706
 */

#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <WebSocketsServer.h>
#include <ESP32Servo.h>
#include <DHT.h>
#include <EEPROM.h>
#include <DNSServer.h> 

#include "config.h"
#include "Sensors.h"     
#include "index_html.h"  
#include "style_css.h"   
#include "script_js.h"   
#include "login_html.h"
#include "database.h"

// --- Global Objects ---
SensorManager sensors; 
Servo floodGate;
DHT dht(DHT_PIN, DHT_TYPE);
DNSServer dnsServer; 
DatabaseManager database;

AsyncWebServer server(80);
WebSocketsServer webSocket(81);

SystemMode currentMode = MODE_AUTO; 
unsigned long lastLogTime = 0;
unsigned long lastReadTime = 0;

// 10-minute logging (600,000 milliseconds)
const unsigned long LOG_INTERVAL_10MIN = 10 * 60 * 1000;

// --- Function Prototypes ---
void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length);
void broadcastData();
void logData();
void enterSleepMode();
void handleGateLogic();

// --- ISR for Mode Switching ---
volatile bool buttonPressed = false;
void IRAM_ATTR isrWake() {
  buttonPressed = true;
}

// --- CAPTIVE PORTAL HANDLER ---
class CaptiveRequestHandler : public AsyncWebHandler {
public:
  CaptiveRequestHandler() {}
  virtual ~CaptiveRequestHandler() {}

  bool canHandle(AsyncWebServerRequest *request){
    return true; 
  }

  void handleRequest(AsyncWebServerRequest *request) {
    request->send_P(200, "text/html", login_html); 
  } 
};

void setup() {
  Serial.begin(115200);
  EEPROM.begin(EEPROM_SIZE);
  
  // Initialize database first
  Serial.println("Initializing database...");
  if (!database.initializeDatabase()) {
    Serial.println("Database initialization failed!");
  } else {
    Serial.println("Database ready on ESP32 internal storage");
  }
  
  sensors.init();
  attachInterrupt(digitalPinToInterrupt(WAKE_UP_PIN), isrWake, FALLING);

  // 1. Setup WiFi AP
  WiFi.softAP("FloodMonitor_Network");
  Serial.print("AP IP: "); Serial.println(WiFi.softAPIP());

  // 2. Start DNS Server 
  dnsServer.start(DNS_PORT, "*", WiFi.softAPIP());

  // 3. Setup Web Server Routes
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
  });
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/css", style_css);
  });
  server.on("/script.js", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/javascript", script_js);
  });

  // Maintenance Command
  server.on("/gate", HTTP_GET, [&](AsyncWebServerRequest *request){
    if (currentMode == MODE_MAINTENANCE && request->hasParam("state")) {
      String state = request->getParam("state")->value();
      if (state == "OPEN") sensors.setGate(true);
      else sensors.setGate(false);
      request->send(200, "text/plain", "OK");
    } else {
      request->send(403, "text/plain", "Not in Maintenance Mode");
    }
  });

  // Add database-related endpoints
  server.on("/sensor-data", HTTP_GET, [](AsyncWebServerRequest *request){
    String data = database.getSensorData(100);
    request->send(200, "application/json", data);
  });

  server.on("/storage-status", HTTP_GET, [](AsyncWebServerRequest *request){
    String status = database.getStorageStatus();
    request->send(200, "application/json", status);
  });

  server.on("/activity-logs", HTTP_GET, [](AsyncWebServerRequest *request){
    String logs = database.getActivityLogs(50);
    request->send(200, "application/json", logs);
  });

  server.on("/factory-reset", HTTP_POST, [](AsyncWebServerRequest *request){
    if (database.factoryReset()) {
      request->send(200, "text/plain", "Factory reset successful");
      ESP.restart();
    } else {
      request->send(500, "text/plain", "Factory reset failed");
    }
  });

  server.on("/log", HTTP_POST, [](AsyncWebServerRequest *request){}, NULL,
    [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total){
      String body = String((char*)data);
      // Parse and log activity (simplified)
      database.logActivity("WEB_ACTION", "user", body);
      request->send(200, "text/plain", "logged");
    });

  // 4. Add "Catch-All" Handler for Captive Portal
  server.addHandler(new CaptiveRequestHandler()).setFilter(ON_AP_FILTER);

  server.begin();
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);

  Serial.println("System Started in AUTO Mode");
  
  // Log system startup
  database.logActivity("SYSTEM_STARTUP", "system", "Flood monitor initialized");
}

void loop() {
  // 5. PROCESS DNS REQUESTS
  dnsServer.processNextRequest(); 

  webSocket.loop();
  unsigned long now = millis();

  // Mode Switching Logic
  if (buttonPressed) {
    delay(50); // Debounce
    buttonPressed = false;
    SystemMode oldMode = currentMode;
    
    if (currentMode == MODE_AUTO) currentMode = MODE_MAINTENANCE;
    else if (currentMode == MODE_MAINTENANCE) currentMode = MODE_SLEEP;
    else currentMode = MODE_AUTO;
    
    Serial.println("Mode Changed");
    
    // Log mode change to database
    String modeChange = "From " + getModeString(oldMode) + " to " + getModeString(currentMode);
    database.logActivity("MODE_CHANGE", "system", modeChange);
  }

  // State Machine
  switch (currentMode) {
    case MODE_AUTO:
      if (now - lastReadTime > SENSOR_READ_INTERVAL) {
        lastReadTime = now;
        sensors.readAll();
        handleGateLogic();
        broadcastData();
      }
      
      // Log sensor data every 10 minutes
      if (now - lastLogTime > LOG_INTERVAL_10MIN) {
        logSensorDataToDatabase();
        lastLogTime = now;
      }
      break;

    case MODE_MAINTENANCE:
      if (now - lastReadTime > SENSOR_READ_INTERVAL) {
        lastReadTime = now;
        sensors.readAll();
        broadcastData(); 
      }
      
      // Still log in maintenance mode but less frequently
      if (now - lastLogTime > LOG_INTERVAL_10MIN) {
        logSensorDataToDatabase();
        lastLogTime = now;
      }
      break;

    case MODE_SLEEP:
      Serial.println("Entering Deep Sleep...");
      database.logActivity("SYSTEM_SLEEP", "system", "Entering deep sleep mode");
      enterSleepMode(); 
      break;
  }
}

// New function to get mode as string
String getModeString(SystemMode mode) {
  switch(mode) {
    case MODE_AUTO: return "AUTO";
    case MODE_MAINTENANCE: return "MAINTENANCE";
    case MODE_SLEEP: return "SLEEP";
    default: return "UNKNOWN";
  }
}

// Enhanced sensor logging function
void logSensorDataToDatabase() {
  Serial.println("=== 10-MINUTE SENSOR LOG ===");
  
  // Read all current sensor values
  float waterLevel = sensors.getWaterPercent();
  String gateStatus = sensors.isGateOpen() ? "OPEN" : "CLOSED";
  float temperature = sensors.getTemp();
  float humidity = sensors.getHumidity();
  String rainStatus = (sensors.getRainRaw() < RAIN_THRESHOLD) ? "RAINING" : "NO_RAIN";
  int lightValue = sensors.getLightRaw();
  
  // Log to database
  bool success = database.logSensorData(
    waterLevel,
    gateStatus, 
    temperature,
    humidity,
    rainStatus,
    lightValue
  );
  
  if (success) {
    Serial.println("✓ Sensor data logged to ESP32 database");
    
    // Log critical conditions
    if (waterLevel >= WATER_OPEN_PERCENT) {
      database.logActivity("SENSOR_ALERT", "system", 
        "CRITICAL: Water level " + String(waterLevel) + "% - Gate should be OPEN");
    } else if (waterLevel >= WATER_SAFE_PERCENT) {
      database.logActivity("SENSOR_WARNING", "system", 
        "WARNING: Water level " + String(waterLevel) + "% - Monitoring closely");
    }
    
    if (temperature > 40.0) {
      database.logActivity("SENSOR_ALERT", "system", 
        "HIGH TEMPERATURE: " + String(temperature) + "°C");
    }
    
    if (rainStatus == "RAINING") {
      database.logActivity("WEATHER_ALERT", "system", "Rain detected - Water level may rise");
    }
    
  } else {
    Serial.println("✗ Failed to log sensor data to database");
    database.logActivity("SYSTEM_ERROR", "system", "Failed to log sensor data");
  }
  
  // Print current storage status
  database.printStorageInfo();
}

// Separate function for cleaner logic
void handleGateLogic() {
  int currentLevel = sensors.getWaterPercent();
  bool wasOpen = sensors.isGateOpen();
  
  // Logic: 
  // 1. If Water >= 70% -> OPEN Gate
  // 2. If Water < 60%  -> CLOSE Gate
  // 3. If between 60% and 70% -> Do nothing (Stay in previous state)
  
  if (currentLevel >= WATER_OPEN_PERCENT) {
    if (!sensors.isGateOpen()) {
      Serial.println("Critical Level! Opening Gate.");
      sensors.setGate(true);
      
      // Log gate action to database
      database.logActivity("GATE_AUTO_OPEN", "system", 
        "Water level " + String(currentLevel) + "% - Auto opened gate");
    }
  } 
  else if (currentLevel < WATER_SAFE_PERCENT) {
    if (sensors.isGateOpen()) {
      Serial.println("Level Safe. Closing Gate.");
      sensors.setGate(false);
      
      // Log gate action to database
      database.logActivity("GATE_AUTO_CLOSE", "system", 
        "Water level " + String(currentLevel) + "% - Auto closed gate");
    }
  }
}

void enterSleepMode() {
  sensors.setGate(false); // Ensure safe state before sleep
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_33, 0); 
  esp_deep_sleep_start();
}

void logData() {
  // This function is now handled by logSensorDataToDatabase()
  Serial.println("Legacy logData() called - use logSensorDataToDatabase() instead");
}

// Helper to ensure float string has a dot separator
String formatFloat(float val) {
  if (isnan(val)) return "0.0";
  String s = String(val, 1);
  s.replace(',', '.'); // Force dot for JSON compatibility
  return s;
}

void broadcastData() {
  String modeStr;
  if(currentMode == MODE_AUTO) modeStr = "AUTO";
  else if(currentMode == MODE_MAINTENANCE) modeStr = "MAINTENANCE";
  else modeStr = "SLEEP";

  String rainStatus = (sensors.getRainRaw() < RAIN_THRESHOLD) ? "Raining" : "No Rain";
  String gateStatus = sensors.isGateOpen() ? "OPEN" : "CLOSED";
  
  int waterPercent = sensors.getWaterPercent();

  // Format safely
  String tempStr = formatFloat(sensors.getTemp());
  String humStr = formatFloat(sensors.getHumidity());

  String jsonString = "{";
  jsonString += "\"mode\":\"" + modeStr + "\"";
  jsonString += ", \"temp\":" + tempStr;
  jsonString += ", \"humidity\":" + humStr;
  jsonString += ", \"water_raw\":" + String(sensors.getWaterRaw());
  jsonString += ", \"water_percent\":" + String(waterPercent);
  jsonString += ", \"rain_raw\":" + String(sensors.getRainRaw());
  jsonString += ", \"rain_status\":\"" + rainStatus + "\"";
  jsonString += ", \"light_raw\":" + String(sensors.getLightRaw());
  jsonString += ", \"gate_status\":\"" + gateStatus + "\"";
  jsonString += "}";
  
  webSocket.broadcastTXT(jsonString);
}

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
  if (type == WStype_CONNECTED) {
    IPAddress ip = webSocket.remoteIP(num);
    Serial.printf("[%u] Connected from %s\n", num, ip.toString().c_str());
  }
}