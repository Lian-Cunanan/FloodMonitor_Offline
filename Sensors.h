#pragma once
#include "config.h"

// NOTE: Do NOT define Enums or Constants here. They are inside config.h

class SensorManager {
  private:
    float temp;
    float humidity;
    int waterRaw;
    int rainRaw;
    int lightRaw;
    unsigned long lastServoMoveTime = 0; // To track when we last moved the servo
    bool gateOpenState = false;          // Explicitly track if gate is OPEN (true) or CLOSED (false)
    
    // New variables for Time-Based Balancing
    long currentSimulatedPosMs = 0;      // Virtual Position: 0ms (Closed) to 5000ms (Fully Open)
    unsigned long activeTimeoutDuration = 5000; // Dynamically calculated run-time

  public:
    void init() {
      dht.begin();
      pinMode(WAKE_UP_PIN, INPUT_PULLUP);
      
      // Control sensor power
      analogSetPinAttenuation(WATER_LEVEL_PIN, ADC_11db);
      analogSetPinAttenuation(RAIN_SENSOR_PIN, ADC_11db);
      analogSetPinAttenuation(LDR_PIN, ADC_11db);

      // Initialize Servo State
      floodGate.attach(SERVO_PIN);
      floodGate.write(0); // Start Closed
      gateOpenState = false; 
      currentSimulatedPosMs = 0;
      lastServoMoveTime = millis(); 
      activeTimeoutDuration = 5000;
    }

    // --- ACCURACY IMPROVEMENT: Averaging Filter ---
    // Takes 10 readings and averages them to remove noise/spikes
    int readWaterLevelAverage() {
      long sum = 0;
      const int numReadings = 10;
      for (int i = 0; i < numReadings; i++) {
        sum += analogRead(WATER_LEVEL_PIN);
        delay(5); // Tiny delay to allow ADC to settle
      }
      return sum / numReadings;
    }

    void readAll() {
      // DHT Logic with basic error handling
      float newTemp = dht.readTemperature();
      float newHum = dht.readHumidity();

      // Check if any reads failed
      if (isnan(newTemp) || isnan(newHum)) {
        // Serial.println("DEBUG: Failed to read from DHT sensor!"); 
        // Keep old values if read fails to prevent 0.0 flickering
      } else {
        temp = newTemp;
        humidity = newHum;
      }
      
      // Use the filtered average reading for water
      waterRaw = readWaterLevelAverage(); 
      
      rainRaw = analogRead(RAIN_SENSOR_PIN);
      lightRaw = analogRead(LDR_PIN);
      
      // Basic error handling for NaN on other sensors if needed
      if (isnan(temp)) temp = 0.0;
      if (isnan(humidity)) humidity = 0.0;

      // --- SERVO HOUSEKEEPING (Runs in ALL Modes) ---
      // Detach servo after the CALCULATED duration is reached to stop buzzing
      if (floodGate.attached()) {
         if (millis() - lastServoMoveTime > activeTimeoutDuration) {
           floodGate.detach(); 
         }
      }
    }

    // --- GATE LOGIC & CONTROL ---
    
    void manageGate(int currentWaterPercent) {
      // 1. Hysteresis Logic (State Transitions)
      if (currentWaterPercent >= WATER_OPEN_PERCENT) {
        // Critical Level: Open Gate if not already open
        if (!gateOpenState) {
          setGate(true);
        }
      } 
      else if (currentWaterPercent < WATER_SAFE_PERCENT) {
        // Safe Level: Close Gate if currently open
        if (gateOpenState) {
          setGate(false);
        }
      }
    }

    // Manual or Automatic Actuator Control
    void setGate(bool open) {
      unsigned long now = millis();
      
      // 1. UPDATE VIRTUAL POSITION
      // Calculate how far the gate moved during the previous state
      if (floodGate.attached()) {
        unsigned long elapsed = now - lastServoMoveTime;
        if (gateOpenState) { // Was Opening
           currentSimulatedPosMs += elapsed;
        } else { // Was Closing
           currentSimulatedPosMs -= elapsed;
        }
      } else {
        // If detached, we assume it finished the previous move and is at the limit
        currentSimulatedPosMs = gateOpenState ? 5000 : 0;
      }
      
      // Clamp values to physical limits (0ms to 5000ms)
      if (currentSimulatedPosMs > 5000) currentSimulatedPosMs = 5000;
      if (currentSimulatedPosMs < 0) currentSimulatedPosMs = 0;

      // 2. SET NEW STATE & DURATION
      if (!floodGate.attached()) {
        floodGate.attach(SERVO_PIN);
      }

      if (open) {
        // OPEN COMMAND - Rotate "Backward" / Fully Open (180 deg)
        floodGate.write(180); 
        gateOpenState = true;
        // Formula: Need to travel from Current Pos to 5000
        activeTimeoutDuration = 5000 - currentSimulatedPosMs;
      } else {
        // CLOSE COMMAND - Rotate "Forward" / Closed (0 deg)
        floodGate.write(0);  
        gateOpenState = false;
        // Formula: Need to travel from Current Pos to 0
        activeTimeoutDuration = currentSimulatedPosMs;
      }
      
      // Reset timer so the housekeeping knows when to start counting
      lastServoMoveTime = now; 
    }

    // Check gate status using our tracking variable
    bool isGateOpen() {
      return gateOpenState;
    }

    // Getters
    float getTemp() { return temp; }
    float getHumidity() { return humidity; }
    int getWaterRaw() { return waterRaw; }
    int getRainRaw() { return rainRaw; }
    int getLightRaw() { return lightRaw; }
    
    // Convert Raw Analog using Calibration Values
    int getWaterPercent() {
      // map(value, fromLow, fromHigh, toLow, toHigh)
      // Uses the updated calibration from config.h
      int percent = map(waterRaw, WATER_MIN_RAW, WATER_MAX_RAW, 0, 100);
      return constrain(percent, 0, 100);
    }
};