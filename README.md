# 🌊 IoT Flood Monitoring System (Offline)

<<<<<<< HEAD
A comprehensive ESP32-based flood monitoring system with real-time web dashboard for water level monitoring, environmental sensors, and automated flood gate control.

![System Status](https://img.shields.io/badge/Status-Active-brightgreen)
![Platform](https://img.shields.io/badge/Platform-ESP32-blue)
![License](https://img.shields.io/badge/License-MIT-yellow)
=======
An ESP32-based flood monitoring system with offline web interface for real-time water level monitoring and gate control.
test commit
## Authors
- **Lian Cunanan**
- **Ardyan Perez**
- **Kenneth Manarang**
- **Aldrich Icat**
- **Charles Mirande**
>>>>>>> 92f8a5a07aade09f9c60a8c48e064cfe966886c4

## 👥 Authors
- **Lian Cunanan** - Lead Developer
- **Ardyan Perez** - Hardware Engineer  
- **Kenneth Manarang** - Backend Developer
- **Aldrich Icat** - UI/UX Designer
- **Charles Mirande** - Systems Integrator

## 📋 Table of Contents
- [Features](#features)
- [System Architecture](#system-architecture)
- [Hardware Requirements](#hardware-requirements)
- [Software Requirements](#software-requirements)
- [Installation Guide](#installation-guide)
- [Web Dashboard](#web-dashboard)
- [API Endpoints](#api-endpoints)
- [Troubleshooting](#troubleshooting)
- [Contributing](#contributing)

## ✨ Features

### 🌡️ Environmental Monitoring
- **Real-time water level detection** with visual gauge display
- **Temperature and humidity monitoring** using DHT sensors
- **Light intensity measurement** for day/night detection
- **Rain detection** with intensity measurement

### 🚪 Automated Control
- **Smart flood gate control** based on water level thresholds
- **Manual override** capability through web interface
- **Emergency protocols** for critical water levels

### 📱 Web Interface
- **Responsive dashboard** works on mobile and desktop
- **Real-time updates** via WebSocket connection
- **Visual indicators** for all sensor readings
- **Offline operation** - no internet required

### 🔧 System Features
- **WiFi connectivity** with access point fallback
- **Data logging** to local storage
- **Configuration via web interface**
- **OTA (Over-The-Air) updates**

## 🏗️ System Architecture

```
┌─────────────────┐    ┌──────────────┐    ┌─────────────────┐
│   Sensors       │───▶│    ESP32     │───▶│  Web Dashboard  │
│                 │    │              │    │                 │
│ • Water Level   │    │ • WiFi       │    │ • Real-time UI  │
│ • Temperature   │    │ • Web Server │    │ • Controls      │
│ • Humidity      │    │ • WebSocket  │    │ • Monitoring    │
│ • Rain          │    │ • Data Logger│    │ • Alerts        │
│ • Light         │    └──────────────┘    └─────────────────┘
└─────────────────┘           │
                              ▼
                    ┌──────────────────┐
                    │   Flood Gate     │
                    │   (Servo Motor)  │
                    └──────────────────┘
```

## 🔧 Hardware Requirements

### Core Components
| Component | Model/Type | Quantity | Purpose |
|-----------|------------|----------|---------|
| **Microcontroller** | ESP32 DevKit V1 | 1 | Main controller |
| **Water Level Sensor** | Ultrasonic HC-SR04 | 1 | Distance measurement |
| **Temperature/Humidity** | DHT22 | 1 | Environmental data |
| **Rain Sensor** | YL-83 Rain Module | 1 | Precipitation detection |
| **Light Sensor** | LDR/Photoresistor | 1 | Light intensity |
| **Servo Motor** | SG90 Micro Servo | 1 | Gate control |
| **Power Supply** | 5V 2A Adapter | 1 | System power |

### Optional Components
- **LCD Display** (16x2 I2C) - Local status display
- **Buzzer** - Audio alerts
- **LED Indicators** - Status lights
- **SD Card Module** - Extended data logging

## 💻 Software Requirements

### Arduino IDE Setup

1. **Install ESP32 Board Package:**
   ```
   File → Preferences → Additional Board Manager URLs:
   https://dl.espressif.com/dl/package_esp32_index.json
   ```

2. **Required Libraries:**
   ```
   Tools → Manage Libraries → Install:
   ```
   - `ESPAsyncWebServer` by lacamera
   - `AsyncTCP` by dvarrel
   - `ArduinoJson` by Benoit Blanchon
   - `DHT sensor library` by Adafruit
   - `NewPing` by Tim Eckel
   - `ESP32Servo` by Kevin Harrington

## 🚀 Installation Guide

### Step 1: Hardware Setup
```
ESP32 Pin Connections:
├── Water Level Sensor (HC-SR04)
│   ├── VCC → 5V
│   ├── GND → GND  
│   ├── Trig → GPIO 5
│   └── Echo → GPIO 18
├── DHT22 Sensor
│   ├── VCC → 3.3V
│   ├── GND → GND
│   └── Data → GPIO 4
├── Rain Sensor
│   ├── VCC → 3.3V
│   ├── GND → GND
│   └── Analog → GPIO 34
├── Light Sensor (LDR)
│   ├── One end → 3.3V
│   ├── Other end → GPIO 35 & 10kΩ resistor to GND
└── Servo Motor
    ├── VCC → 5V
    ├── GND → GND
    └── Signal → GPIO 2
```

### Step 2: Software Installation

1. **Clone Repository:**
   ```bash
   git clone https://github.com/Lian-Cunanan/FloodMonitor_Offline.git
   cd FloodMonitor_Offline
   ```

2. **Configure WiFi:**
   ```cpp
   // In main sketch file, update:
   const char* ssid = "YOUR_WIFI_NAME";
   const char* password = "YOUR_WIFI_PASSWORD";
   ```

3. **Upload Code:**
   - Open `.ino` file in Arduino IDE
   - Select Board: "ESP32 Dev Module"
   - Select correct COM Port
   - Click Upload

### Step 3: Access Dashboard
1. Open Serial Monitor (115200 baud)
2. Note the IP address displayed
3. Open browser and navigate to: `http://[ESP32_IP]`

## 📊 Web Dashboard

### Main Features
- **📈 Real-time Gauges** - Water level with visual percentage
- **🌡️ Environmental Panel** - Temperature, humidity, light readings  
- **🌧️ Weather Status** - Rain detection and intensity
- **🚪 Gate Control** - Current status and manual override
- **🔴 Connection Status** - WebSocket connection indicator

### Dashboard Preview
The web interface features:
- Responsive grid layout
- Real-time data updates every 2 seconds
- Visual alerts for critical water levels
- Mobile-friendly design
- Offline operation capability

## 🔌 API Endpoints

| Endpoint | Method | Description |
|----------|--------|-------------|
| `/` | GET | Main dashboard |
| `/data` | GET | JSON sensor data |
| `/gate/toggle` | POST | Toggle gate state |
| `/config` | GET/POST | System configuration |
| `/logs` | GET | Historical data |

### Example API Response:
```json
{
  "waterLevel": 75,
  "waterRaw": 450,
  "temperature": 28.5,
  "humidity": 65,
  "lightLevel": 512,
  "rainStatus": "No Rain",
  "rainIntensity": 0,
  "gateStatus": "OPEN",
  "timestamp": "2024-01-15T10:30:00Z"
}
```

## 🐛 Troubleshooting

### Common Issues

**❌ ESP32 not connecting to WiFi**
- Check WiFi credentials
- Verify signal strength
- Try different WiFi channel

**❌ Sensors reading zero values**
- Check wiring connections
- Verify power supply (5V for sensors)
- Test individual sensors

**❌ Web interface not loading**
- Check ESP32 IP address
- Try different browser
- Clear browser cache

**❌ WebSocket connection failed**
- Refresh page
- Check network connectivity
- Restart ESP32

### Debug Mode
Enable debug output in code:
```cpp
#define DEBUG_MODE 1
```

## 🤝 Contributing

1. Fork the repository
2. Create feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit changes (`git commit -m 'Add AmazingFeature'`)
4. Push to branch (`git push origin feature/AmazingFeature`)
5. Open Pull Request

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 📞 Support

For support and questions:
- 📧 Email: [your-email@domain.com]
- 🐛 Issues: [GitHub Issues](https://github.com/Lian-Cunanan/FloodMonitor_Offline/issues)
- 📖 Documentation: [Wiki](https://github.com/Lian-Cunanan/FloodMonitor_Offline/wiki)

---

**⭐ If you found this project helpful, please give it a star!**
