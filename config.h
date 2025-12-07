#pragma once
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
#define WATER_LEVEL_PIN  34
#define RAIN_SENSOR_PIN  35
#define DHT_PIN          22
#define LDR_PIN          32
#define SERVO_PIN        13
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