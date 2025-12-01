<div align="center">

# 🌊 IoT Flood Monitor Pro
### *Real-Time Flood Monitoring & Control System*

[![Made with ESP32](https://img.shields.io/badge/Made%20with-ESP32-blue?style=for-the-badge&logo=espressif)](https://www.espressif.com/)
[![Arduino IDE](https://img.shields.io/badge/Arduino-IDE-00979D?style=for-the-badge&logo=arduino&logoColor=white)](https://www.arduino.cc/)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg?style=for-the-badge)](https://opensource.org/licenses/MIT)
[![Status: Active](https://img.shields.io/badge/Status-Active%20Development-brightgreen?style=for-the-badge)](https://github.com/Lian-Cunanan/FloodMonitor_Offline)

*An ESP32-based flood monitoring system with web dashboard for water level monitoring, environmental sensors, and flood gate control.*

---

### 🏆 **Student Project** | 📱 **Web-Based** | 🔧 **Open Source**

</div>

## 🎯 **Project Overview**

The **IoT Flood Monitor Pro** is a student-developed flood monitoring system designed for educational purposes and potential real-world deployment. Built with ESP32 and modern web technologies, it provides flood detection, environmental monitoring, and basic automated response capabilities.

### 🌟 **Key Features**

- 🎨 **Modern Web Interface** - Clean dashboard with real-time data display
- 🔐 **User Authentication** - Login and registration system with SQLite
- 📊 **Sensor Monitoring** - Real-time water level, temperature, and humidity readings
- 🤖 **Basic Automation** - Simple flood gate control mechanism
- 📱 **Responsive Design** - Works on desktop and mobile browsers
- ⚡ **ESP32 Powered** - Efficient microcontroller with WiFi connectivity

## 👥 **Development Team**

<table align="center">
  <tr>
    <td align="center">
      <img src="profile_pictures/Lian.jpg" width="100px;" style="border-radius: 50%;" alt="Lian Cunanan"/><br />
      <sub><b>🚀 Lian Cunanan</b></sub><br />
      <sub>Lead Developer & System Architect</sub><br />
      <a href="https://github.com/Lian-Cunanan">GitHub</a> | 
      <a href="https://www.linkedin.com/in/lian-vince-cunanan-3930212a4/">LinkedIn</a>
    </td>
    <td align="center">
      <img src="profile_pictures/ardyan.jpg" width="100px;" style="border-radius: 50%;" alt="Ardyan Perez"/><br />
      <sub><b>🔧 Ardyan Perez</b></sub><br />
      <sub>Hardware Engineer & IoT Specialist</sub>
    </td>
    <td align="center">
      <img src="profile_pictures/kenneth.jpg" width="100px;" style="border-radius: 50%;" alt="Kenneth Manarang"/><br />
      <sub><b>💻 Kenneth Manarang</b></sub><br />
      <sub>Backend Developer & Database Engineer</sub>
    </td>
  </tr>
  <tr>
    <td align="center">
      <img src="profile_pictures/aldrich.jpg" width="100px;" style="border-radius: 50%;" alt="Aldrich Icat"/><br />
      <sub><b>🎨 Aldrich Icat</b></sub><br />
      <sub>UI/UX Designer & Frontend Developer</sub>
    </td>
    <td align="center">
      <img src="profile_pictures/Charles.png" width="100px;" style="border-radius: 50%;" alt="Charles Mirande"/><br />
      <sub><b>⚙️ Charles Mirande</b></sub><br />
      <sub>Systems Integrator & Testing</sub>
    </td>
    <td align="center">
      <img src="https://images.unsplash.com/photo-1522202176988-66273c2fd55f?w=100&h=100&fit=crop&crop=faces&auto=format" width="100px;" style="border-radius: 50%;" alt="Team Collaboration"/><br />
      <sub><b>🤝 Collaborative Team</b></sub><br />
      <sub>Innovation & Learning</sub>
    </td>
  </tr>
</table>

## 📸 **Project Screenshots**

<div align="center">

### 🖥️ **Web Dashboard**
*Clean and intuitive monitoring interface*

### 📱 **Mobile Responsive**
*Accessible on all devices*

### 🔐 **Login System**
*Secure user authentication*

> **Note:** This is a student project showcasing IoT and web development skills. Interface screenshots available upon request.

</div>

## ✨ **Available Features**

<table>
<tr>
<td width="50%">

### 🌊 **Basic Monitoring**
- **Water Level Detection** with ultrasonic sensor (HC-SR04)
- **Temperature & Humidity** monitoring (DHT22)
- **Real-time Data Display** on web dashboard
- **Simple Data Logging** with timestamps
- **Basic Alert System** for high water levels

</td>
<td width="50%">

### 🎛️ **Simple Control**
- **Manual Flood Gate Control** via web interface
- **Servo Motor Integration** for gate mechanism
- **Remote Access** through ESP32 web server
- **Status Monitoring** with visual indicators
- **Manual Override** capabilities

</td>
</tr>
<tr>
<td>

### 🔒 **User Management**
- **Registration & Login** system
- **SQLite Database** for user storage
- **Session Management** with cookies
- **Basic Security** with password hashing
- **Activity Logging** for user actions

</td>
<td>

### 📊 **Web Interface**
- **Responsive Design** using CSS Grid/Flexbox
- **Real-time Updates** via JavaScript
- **Interactive Controls** for system management
- **Professional Styling** with modern CSS
- **Mobile-Friendly** layout

</td>
</tr>
</table>

## 🏗️ **System Architecture**

```
┌─────────────────┐    ┌──────────────┐    ┌─────────────────┐
│   Sensors       │───▶│    ESP32     │───▶│  Web Dashboard  │
│                 │    │              │    │                 │
│ • Water Level   │    │ • WiFi       │    │ • Real-time UI  │
│ • Temperature   │    │ • Web Server │    │ • Controls      │
│ • Humidity      │    │ • SQLite     │    │ • User Login    │
│ • Rain (Opt.)   │    │ • Data Logger│    │ • Monitoring    │
│ • Light (Opt.)  │    │ • Auth System│    │ • Analytics     │
└─────────────────┘    └──────────────┘    └─────────────────┘
                              │
                              ▼
                    ┌──────────────────┐
                    │   Flood Gate     │
                    │   (Servo Motor)  │
                    └──────────────────┘
```

### 🌐 **Network Architecture**

```
Internet ←→ Router ←→ ESP32 ←→ Sensors
    ↑           ↑        ↑        ↑
    │           │        │        └─ DHT22, HC-SR04, etc.
    │           │        └─ Web Server (Port 80)
    │           └─ 2.4GHz WiFi
    └─ Remote Access via Browser
```

## 🔧 **Hardware Requirements**

<div align="center">

| Component | Specification | Quantity | Status |
|-----------|--------------|----------|--------|
| **🔌 ESP32 DevKit** | V1 or compatible | 1 | ✅ Required |
| **📏 Ultrasonic Sensor** | HC-SR04 | 1 | ✅ Required |
| **🌡️ DHT Sensor** | DHT22 or DHT11 | 1 | ✅ Required |
| **⚙️ Servo Motor** | SG90 Micro Servo | 1 | ✅ Required |
| **🔋 Power Supply** | 5V 2A adapter | 1 | ✅ Required |
| **🌧️ Rain Sensor** | YL-83 or compatible | 1 | ✅ Required |
| **💡 Light Sensor** | LDR + 10kΩ resistor | 1 | ✅ Required |
| **📡 WiFi Network** | 2.4GHz compatible | 1 | ✅ Required |

</div>

### 🔌 **Pin Configuration**

<div align="center">

#### **ESP32 DevKit V1 Wiring Diagram**

```
                    ┌─────────────────────────────────┐
                    │         ESP32 DevKit V1         │
                    │                                 │
       ┌────────────┤ 🔌 Power & Ground              │
       │            ├─────────────────────────────────┤
       │      3.3V ─┤ ⚡ 3.3V  ── DHT22 VCC          │
       │        5V ─┤ ⚡ 5V    ── HC-SR04 VCC        │
       │       GND ─┤ ⚪ GND   ── Common Ground       │
       │            │                                 │
       │            ├─────────────────────────────────┤
       │            │ 📡 Digital GPIO Pins           │
  ┌────┴─────┐      ├─────────────────────────────────┤
  │ Sensors  │      │                                 │
  │          │ GPIO2─┤ 🔴 D2    ── Servo Signal       │
  │ 🌊 Water │ GPIO4─┤ 🟢 D4    ── DHT22 Data        │
  │ 🌡️ Temp  │ GPIO5─┤ 🔵 D5    ── HC-SR04 Trigger   │
  │ 💧 Humid │GPIO18─┤ 🟡 D18   ── HC-SR04 Echo      │
  │ 🌧️ Rain  │GPIO34─┤ 🟠 A2    ── Rain Sensor       │
  │ 💡 Light │GPIO35─┤ 🟣 A3    ── LDR Light Sensor  │
  └──────────┘      │                                 │
                    └─────────────────────────────────┘
```

#### **Detailed Connection Table**

| 🎯 Component | 📍 ESP32 Pin | 🔗 Connection Type | ⚡ Power | 📝 Notes |
|-------------|-------------|------------------|---------|----------|
| **🌊 HC-SR04** | | | | **Ultrasonic Distance** |
| └ VCC | 5V Rail | Power | 5V | High power requirement |
| └ GND | GND | Ground | 0V | Common ground |
| └ Trig | GPIO 5 | Digital Output | 3.3V | Trigger pulse |
| └ Echo | GPIO 18 | Digital Input | 3.3V | Distance measurement |
| **🌡️ DHT22** | | | | **Temperature & Humidity** |
| └ VCC | 3.3V | Power | 3.3V | Low power sensor |
| └ GND | GND | Ground | 0V | Common ground |
| └ Data | GPIO 4 | Digital I/O | 3.3V | One-wire protocol |
| **⚙️ SG90 Servo** | | | | **Flood Gate Control** |
| └ VCC | 5V Rail | Power | 5V | Motor power |
| └ GND | GND | Ground | 0V | Common ground |
| └ Signal | GPIO 2 | PWM Output | 3.3V | Position control |
| **🌧️ Rain Sensor** | | | | **Precipitation Detection** |
| └ VCC | 3.3V | Power | 3.3V | Sensor power |
| └ GND | GND | Ground | 0V | Common ground |
| └ AO | GPIO 34 | Analog Input | 0-3.3V | Moisture level |
| **💡 LDR Sensor** | | | | **Light Monitoring** |
| └ Signal | GPIO 35 | Analog Input | 0-3.3V | Light intensity |
| └ 10kΩ Resistor | GND | Pull-down | - | Voltage divider |

</div>

#### **🔧 Wiring Best Practices**

<div align="center">

| ⚠️ **Safety Guidelines** | ✅ **Best Practices** |
|------------------------|---------------------|
| 🔴 **Power Off** before wiring | 🟢 **Double-check** all connections |
| ⚡ **5V Rail** for high-power devices | 🔵 **3.3V Logic** for data signals |
| 🌍 **Common Ground** for all components | 📏 **Short Wires** to reduce interference |
| 🔌 **Separate Power** for servo motor | 🛡️ **Use Breadboard** for prototyping |

</div>

#### **📊 Power Consumption Analysis**

```
Total System Power Requirements:
┌─────────────────────────────────────┐
│  Component    │ Voltage │ Current   │
├─────────────────────────────────────┤
│  🔧 ESP32     │  3.3V   │  240mA    │
│  🌊 HC-SR04   │  5.0V   │   15mA    │
│  🌡️ DHT22     │  3.3V   │   2.5mA   │
│  ⚙️ SG90      │  5.0V   │  100-600mA │
│  🌧️ Rain      │  3.3V   │   20mA    │
│  💡 LDR       │  3.3V   │   0.1mA   │
├─────────────────────────────────────┤
│  💡 Total Max │  5.0V   │  ~900mA   │
└─────────────────────────────────────┘

Recommended: 5V 2A Power Supply
```

## 💻 **Required Libraries**

Install these libraries in Arduino IDE:

```cpp
// Core Libraries (Required)
- ESPAsyncWebServer by me-no-dev
- AsyncTCP by me-no-dev  
- ArduinoJson by Benoit Blanchon
- DHT sensor library by Adafruit

// Sensor Libraries
- NewPing by Tim Eckel (for HC-SR04)
- ESP32Servo by Kevin Harrington

// Optional Libraries
- sqlite3 by Richard T. Hatch (if using database)
```

## 🚀 **Installation Guide**

### 📋 **Step 1: Setup Arduino IDE**
1. Install Arduino IDE 2.0+
2. Add ESP32 board package:
   - File → Preferences → Additional Board Manager URLs
   - Add: `https://dl.espressif.com/dl/package_esp32_index.json`
3. Install ESP32 boards via Board Manager

### 📚 **Step 2: Install Libraries**
```bash
Arduino IDE → Tools → Manage Libraries
Search and install each library from the list above
```

### 📥 **Step 3: Get the Code**
```bash
git clone https://github.com/Lian-Cunanan/FloodMonitor_Offline.git
cd FloodMonitor_Offline
```

### ⚙️ **Step 4: Configure WiFi**
```cpp
// In FloodMonitor_ESP32.ino, update:
const char* ssid = "Your_WiFi_Name";
const char* password = "Your_WiFi_Password";
```

### 🔌 **Step 5: Wire Components**
- Follow the pin configuration diagram above
- Double-check all connections
- Ensure proper power supply (5V for servo/ultrasonic, 3.3V for DHT)

### ⬆️ **Step 6: Upload Code**
1. Select Board: "ESP32 Dev Module"
2. Select correct COM Port
3. Upload the sketch
4. Open Serial Monitor (115200 baud)
5. Note the IP address displayed

### 🌐 **Step 7: Access System**
```
Web Interface: http://[ESP32_IP]/
Login Page:    http://[ESP32_IP]/login
```

## 📱 **User Interface**

### 🎨 **Design Features**
- **Clean Dashboard** with real-time sensor readings
- **Interactive Gauges** showing water levels
- **Responsive Layout** for mobile and desktop
- **User Authentication** with registration/login
- **Control Interface** for flood gate management

### 🔧 **Available Controls**
- **Water Level Monitor** with visual gauge
- **Temperature Display** from DHT sensor
- **Humidity Readings** with trend indicators
- **Gate Control** with open/close buttons
- **User Management** with login/logout

## 🐛 **Troubleshooting**

<details>
<summary><b>🔧 Common Issues & Solutions</b></summary>

### ❌ **ESP32 Won't Connect to WiFi**
- ✅ Verify 2.4GHz network (ESP32 doesn't support 5GHz)
- ✅ Check WiFi credentials in code
- ✅ Ensure strong signal strength
- ✅ Try mobile hotspot for testing

### ❌ **Sensors Not Reading**
- ✅ Check wiring connections
- ✅ Verify power supply voltages
- ✅ Test with simple sensor examples first
- ✅ Use multimeter to check connections

### ❌ **Web Page Won't Load**
- ✅ Check ESP32 IP address in Serial Monitor
- ✅ Ensure ESP32 and device on same network
- ✅ Try different browsers
- ✅ Check for typos in IP address

### ❌ **Upload Errors**
- ✅ Select correct board and port
- ✅ Press BOOT button during upload if needed
- ✅ Check USB cable connection
- ✅ Close Serial Monitor before uploading

</details>

## 🎓 **Educational Value**

This project demonstrates:
- **IoT Development** with ESP32 microcontroller
- **Web Development** using HTML, CSS, JavaScript
- **Database Integration** with SQLite
- **Sensor Interfacing** and data collection
- **Real-time Communication** between hardware and web interface
- **System Integration** combining multiple technologies

## 🔮 **Possible Improvements**

- [ ] 📧 **Email Notifications** for critical water levels
- [ ] 📊 **Data Visualization** with charts and graphs
- [ ] 🌙 **Dark Mode** for better user experience
- [ ] 📱 **Mobile App** for remote monitoring
- [ ] ☁️ **Cloud Integration** for remote access
- [ ] 🔔 **Push Notifications** for alerts
- [ ] 📈 **Historical Data Analysis**
- [ ] 🗺️ **GPS Integration** for location tracking

## 📄 **License**

```
MIT License - Feel free to use for educational purposes
Copyright (c) 2024 Lian Cunanan & Team
```

## 📞 **Contact & Support**

<div align="center">

### 👨‍💻 **Project Lead - Lian Cunanan**

[![GitHub](https://img.shields.io/badge/GitHub-100000?style=for-the-badge&logo=github&logoColor=white)](https://github.com/Lian-Cunanan)
[![LinkedIn](https://img.shields.io/badge/LinkedIn-0077B5?style=for-the-badge&logo=linkedin&logoColor=white)](https://www.linkedin.com/in/lian-vince-cunanan-3930212a4/)
[![Facebook](https://img.shields.io/badge/Facebook-1877F2?style=for-the-badge&logo=facebook&logoColor=white)](https://www.facebook.com/lian.cunanan.50)

### 📧 **Get Help**
- 💬 **GitHub Issues** - For technical questions and bug reports
- 📖 **Documentation** - Check the installation guide above
- 🤝 **Community** - Feel free to fork and contribute

---

<sub>🎓 Built as a student project for learning IoT development | © 2024 Lian Cunanan</sub>

</div>
