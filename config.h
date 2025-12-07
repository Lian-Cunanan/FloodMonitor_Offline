#pragma once
<<<<<<< HEAD
#include <Arduino.h>
#include <ESP32Servo.h>
#include <DHT.h>
#include <EEPROM.h>
#include <DNSServer.h> 

// --- 1. System Modes (Enum) ---
enum SystemMode {
  MODE_AUTO,
  MODE_MAINTENANCE,
  MODE_SLEEP
};

// --- 2. Pin Definitions ---
=======

// --- 1. Wi-Fi Settings ---
const char *ssid = "FloodMonitor_Network";
const char *password = "12345678";

// --- 2. Sensor Pins ---
>>>>>>> d5a1704f3b13828ef3fbae00aa481f41e2ef0706
#define WATER_LEVEL_PIN  34
#define RAIN_SENSOR_PIN  35
#define DHT_PIN          22
#define LDR_PIN          32
#define SERVO_PIN        13
<<<<<<< HEAD
#define WAKE_UP_PIN      33 

// --- 3. Constants ---
#define DHT_TYPE DHT22
#define EEPROM_SIZE 64
const byte DNS_PORT = 53;

// --- 4. Logic Thresholds & Calibration ---
const int RAIN_THRESHOLD = 2000;    
const int WATER_OPEN_PERCENT = 70;  
const int WATER_SAFE_PERCENT = 60;  

// *** SENSOR CALIBRATION ***
// Updated based on your physical readings:
// 1% Submerged = ~1500-1750 Raw -> Set MIN to 1500
// 80% Submerged = ~3100 Raw -> Extrapolates to ~3500 for 100%
const int WATER_MIN_RAW = 2700;     
const int WATER_MAX_RAW = 3500;   

// --- 5. Timing ---
const unsigned long LOG_INTERVAL = 600000; 
const unsigned long SENSOR_READ_INTERVAL = 2000; 

// --- 6. Global Variables (Externs) ---
extern SystemMode currentMode;
extern Servo floodGate;
extern DHT dht;
extern DNSServer dnsServer;
=======

// --- 3. Sensor Configuration ---
#define DHT_TYPE DHT22

// --- 4. Logic Thresholds (Adjust these!) ---
// Set the raw analog value (0-4095) from the water sensor that triggers the gate
#define WATER_THRESHOLD 3000 
// Set the raw analog value (0-4095) that indicates rain (lower = more sensitive)
#define RAIN_THRESHOLD  2000 

// --- 5. Global Variables ---
Servo floodGate;
int gateAngle = 0; // 0 = Closed, 90 = Open
DHT dht(DHT_PIN, DHT_TYPE);

AsyncWebServer server(80); // Server on port 80
WebSocketsServer webSocket(81); // WebSocket on port 81
>>>>>>> d5a1704f3b13828ef3fbae00aa481f41e2ef0706
