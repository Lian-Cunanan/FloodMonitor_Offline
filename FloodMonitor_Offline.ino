/*
 * FLOOD MONITORING SYSTEM
 * Compliant with CPE 414 Exam Requirements
 * Includes DATABASE AUTHENTICATION, CAPTIVE PORTAL & 10-MIN LOGGING
 * UPDATED: Light Sleep Mode + Browser Time Sync
 */

#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <WebSocketsServer.h>
#include <ESP32Servo.h>
#include <DHT.h>
#include <EEPROM.h>
#include <DNSServer.h> 
#include <time.h> // Required for time syncing

#include "config.h"
#include "Sensors.h"     
#include "database.h"    
#include "index_html.h"  
#include "style_css.h"   
#include "script_js.h"   
#include "login_html.h"

// --- Global Objects ---
SensorManager sensors;
Servo floodGate;
DHT dht(DHT_PIN, DHT_TYPE);
DNSServer dnsServer; 
DatabaseManager database;

AsyncWebServer server(80);
WebSocketsServer webSocket(81);

SystemMode currentMode = MODE_AUTO;
unsigned long lastLogTime = 0;   // Tracks the last time we saved to database
unsigned long lastReadTime = 0;  // Tracks the last time we read sensors
const unsigned long LOG_INTERVAL_10MIN = 10 * 60 * 1000; // 600,000 ms = 10 Minutes

// --- Function Prototypes ---
void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length);
void broadcastData();
void enterSleepMode();
void handleGateLogic();
String getModeString(SystemMode mode);
void logSensorDataToDatabase();

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
    request->redirect("/login"); 
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

  // --- WEB SERVER ROUTES ---

  // A. Main Dashboard (PROTECTED)
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    if (request->hasHeader("Cookie") && request->header("Cookie").indexOf("ESPSESSIONID=1") != -1) {
      request->send_P(200, "text/html", index_html);
    } else {
      request->redirect("/login");
    }
  });

  // B. Login Page
  server.on("/login", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", login_html);
  });

  // C. Static Assets
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/css", style_css);
  });

  server.on("/script.js", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/javascript", script_js);
  });

  // --- AUTHENTICATION API ---
  server.on("/auth/login", HTTP_POST, [](AsyncWebServerRequest *request){
    String username, password;
    if (request->hasParam("username", true) && request->hasParam("password", true)) {
      username = request->getParam("username", true)->value();
      password = request->getParam("password", true)->value();

      if (database.validateLogin(username, password)) {
        AsyncWebServerResponse *response = request->beginResponse(200, "text/plain", "Login Success");
        response->addHeader("Set-Cookie", "ESPSESSIONID=1; Path=/; Max-Age=3600"); 
        request->send(response);
      } else {
        request->send(401, "text/plain", "Invalid Username or Password");
      }
    } else {
      request->send(400, "text/plain", "Missing Credentials");
    }
  });

  server.on("/auth/register", HTTP_POST, [](AsyncWebServerRequest *request){
    String username, email, password;
    if (request->hasParam("username", true) && request->hasParam("password", true)) {
      username = request->getParam("username", true)->value();
      password = request->getParam("password", true)->value();
      email = request->hasParam("email", true) ? request->getParam("email", true)->value() : "";

      if (database.userExists(username, email)) {
        request->send(409, "text/plain", "User already exists");
      } else {
        if (database.registerUser(username, email, password)) {
          request->send(200, "text/plain", "Registration Successful");
        } else {
          request->send(500, "text/plain", "Database Write Failed");
        }
      }
    } else {
      request->send(400, "text/plain", "Missing Data");
    }
  });

  server.on("/auth/logout", HTTP_POST, [](AsyncWebServerRequest *request){
    AsyncWebServerResponse *response = request->beginResponse(200, "text/plain", "Logged Out");
    response->addHeader("Set-Cookie", "ESPSESSIONID=0; Path=/; Max-Age=0");
    request->send(response);
  });

  // --- SYSTEM CONTROL ROUTES ---
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

  // *** NEW: SYNC TIME WITH BROWSER ***
  server.on("/sync-time", HTTP_GET, [](AsyncWebServerRequest *request){
    if(request->hasParam("t")) {
      unsigned long t = request->getParam("t")->value().toInt();
      struct timeval tv;
      tv.tv_sec = t;
      tv.tv_usec = 0;
      settimeofday(&tv, NULL); // Sets ESP32 internal clock to Real Time
      Serial.printf("Time Synced to: %lu\n", t);
      request->send(200, "text/plain", "Time Synced");
    } else {
      request->send(400, "text/plain", "No time provided");
    }
  });

  // *** FETCH ALL RECORDS FOR DOWNLOAD ***
  server.on("/sensor-data", HTTP_GET, [](AsyncWebServerRequest *request){
    String data = database.getSensorData(500); 
    request->send(200, "application/json", data);
  });

  server.on("/storage-status", HTTP_GET, [](AsyncWebServerRequest *request){
    String status = database.getStorageStatus();
    request->send(200, "application/json", status);
  });

  server.on("/factory-reset", HTTP_POST, [](AsyncWebServerRequest *request){
    if (database.factoryReset()) {
      request->send(200, "text/plain", "Factory reset successful");
      delay(1000);
      ESP.restart();
    } else {
      request->send(500, "text/plain", "Factory reset failed");
    }
  });

  server.addHandler(new CaptiveRequestHandler()).setFilter(ON_AP_FILTER);

  server.begin();
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);

  Serial.println("System Started in AUTO Mode");
  database.logActivity("SYSTEM_STARTUP", "system", "Flood monitor initialized");
}

void loop() {
  dnsServer.processNextRequest();
  webSocket.loop(); // Websocket must run in ALL modes for dashboard access
  unsigned long now = millis();

  // Mode Switching Logic
  if (buttonPressed) {
    delay(50); // Debounce
    buttonPressed = false;
    SystemMode oldMode = currentMode;
    
    // Cycle modes
    if (currentMode == MODE_AUTO) currentMode = MODE_MAINTENANCE;
    else if (currentMode == MODE_MAINTENANCE) currentMode = MODE_SLEEP;
    else currentMode = MODE_AUTO;
    
    Serial.println("Mode Changed");
    String modeChange = "From " + getModeString(oldMode) + " to " + getModeString(currentMode);
    database.logActivity("MODE_CHANGE", "system", modeChange);

    if (currentMode == MODE_SLEEP) {
        enterSleepMode();
    }
  }

  // --- MAIN STATE MACHINE ---
  switch (currentMode) {
    case MODE_AUTO:
      // 1. Read Sensors every 2 seconds
      if (now - lastReadTime > SENSOR_READ_INTERVAL) {
        lastReadTime = now;
        sensors.readAll();
        handleGateLogic();
        broadcastData();
      }
      
      // 2. Log Data every 10 Minutes (600,000 ms)
      if (now - lastLogTime > LOG_INTERVAL_10MIN) {
        logSensorDataToDatabase();
        lastLogTime = now; // Reset timer
      }
      break;

    case MODE_MAINTENANCE:
      // In Maintenance, we read sensors to show status, but GATE is manual
      if (now - lastReadTime > SENSOR_READ_INTERVAL) {
        lastReadTime = now;
        sensors.readAll();
        broadcastData(); 
      }
      
      // We ALSO log in Maintenance mode to keep the history complete
      if (now - lastLogTime > LOG_INTERVAL_10MIN) {
        logSensorDataToDatabase();
        lastLogTime = now; // Reset timer
      }
      break;

    case MODE_SLEEP:
      // "LIGHT SLEEP / FAKE SLEEP"
      // 1. No new sensor readings (save processing/power)
      // 2. No Database logging (save storage)
      // 3. Keep WiFi alive so dashboard works
      
      // We broadcast occasionally just to update the "Mode: SLEEP" text on the UI
      if (now - lastReadTime > 2000) {
        lastReadTime = now;
        broadcastData(); // Sends the old data + "SLEEP" status
      }
      break;
  }
}

String getModeString(SystemMode mode) {
  switch(mode) {
    case MODE_AUTO: return "AUTO";
    case MODE_MAINTENANCE: return "MAINTENANCE";
    case MODE_SLEEP: return "SLEEP";
    default: return "UNKNOWN";
  }
}

// This function handles the actual saving to database.h
void logSensorDataToDatabase() {
  Serial.println("=== SAVING 10-MINUTE LOG ===");
  float waterLevel = sensors.getWaterPercent();
  String gateStatus = sensors.isGateOpen() ? "OPEN" : "CLOSED";
  float temperature = sensors.getTemp();
  float humidity = sensors.getHumidity();
  String rainStatus = (sensors.getRainRaw() < RAIN_THRESHOLD) ? "RAINING" : "NO_RAIN";
  int lightValue = sensors.getLightRaw();

  // This writes to the file system
  bool success = database.logSensorData(waterLevel, gateStatus, temperature, humidity, rainStatus, lightValue);
  
  if (success) {
    Serial.println("✓ Data Saved Successfully");
  } else {
    Serial.println("✗ Save Failed (Check Memory/Storage)");
  }
  
  // Check for critical alerts to log separately
  if (waterLevel >= WATER_OPEN_PERCENT) {
    database.logActivity("SENSOR_ALERT", "system", "CRITICAL: Water level " + String(waterLevel) + "%");
  }
}

void handleGateLogic() {
  int currentLevel = sensors.getWaterPercent();
  if (currentLevel >= WATER_OPEN_PERCENT) {
    if (!sensors.isGateOpen()) {
      Serial.println("Critical Level! Opening Gate.");
      sensors.setGate(true);
      database.logActivity("GATE_AUTO_OPEN", "system", "Auto opened gate");
    }
  } 
  else if (currentLevel < WATER_SAFE_PERCENT) {
    if (sensors.isGateOpen()) {
      Serial.println("Level Safe. Closing Gate.");
      sensors.setGate(false);
      database.logActivity("GATE_AUTO_CLOSE", "system", "Auto closed gate");
    }
  }
}

void enterSleepMode() {
  // Modified for Light Sleep: Only close gate, do not shut down WiFi/CPU
  sensors.setGate(false); 
  Serial.println(">> Entering Sleep Mode (WiFi Active, Sensors Paused) <<");
}

String formatFloat(float val) {
  if (isnan(val)) return "0.0";
  String s = String(val, 1);
  s.replace(',', '.');
  return s;
}

void broadcastData() {
  String modeStr = getModeString(currentMode);
  String rainStatus = (sensors.getRainRaw() < RAIN_THRESHOLD) ? "Raining" : "No Rain";
  String gateStatus = sensors.isGateOpen() ? "OPEN" : "CLOSED";
  int waterPercent = sensors.getWaterPercent();

  String jsonString = "{";
  jsonString += "\"mode\":\"" + modeStr + "\"";
  jsonString += ", \"temp\":" + formatFloat(sensors.getTemp());
  jsonString += ", \"humidity\":" + formatFloat(sensors.getHumidity());
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