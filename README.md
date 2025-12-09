<div align="center">

# 🌊 IoT Flood Monitor Pro
### *Real-Time Flood Monitoring & Control System*

[![Made with ESP32](https://img.shields.io/badge/Made%20with-ESP32-blue?style=for-the-badge&logo=espressif)](https://www.espressif.com/)
[![Arduino IDE](https://img.shields.io/badge/Arduino-IDE-00979D?style=for-the-badge&logo=arduino&logoColor=white)](https://www.arduino.cc/)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg?style=for-the-badge)](https://opensource.org/licenses/MIT)
[![Status: Production Ready](https://img.shields.io/badge/Status-Production%20Ready-brightgreen?style=for-the-badge)](https://github.com/Lian-Cunanan/FloodMonitor_Offline)

*A professional ESP32-based flood monitoring system with enterprise-grade web interface, secure authentication, real-time logging, and automated flood control capabilities.*

---

### 🏆 **Professional Grade** | 📱 **Modern Web Interface** | 🔧 **Production Ready**

</div>

---

## 🎯 **Project Overview**

The **IoT Flood Monitor Pro** is a complete, production-ready flood monitoring solution featuring a professional web dashboard, secure user authentication, comprehensive logging system, and automated flood control. Built with modern web technologies and enterprise-grade security for both educational and commercial deployment.

---

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

---

## 📸 **Project Screenshots**

<div align="center">

### 🖥️ **Web Dashboard**
*Clean and intuitive monitoring interface*

### 📱 **Mobile Responsive**
*Accessible on all devices*

### 🔐 **Login System**
*Secure user authentication*

> **Note:** This is a professional project showcasing IoT and web development skills. Interface screenshots available upon request.

</div>

---

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

---

## 🏗️ **System Architecture Overview**

### 🔄 **Main System Flow**

```mermaid
graph TB
    subgraph "🌊 Sensor Layer"
        A[💧 Water Level<br/>HC-SR04]
        B[🌡️ Temperature<br/>DHT22]
        C[💨 Humidity<br/>DHT22]
        D[🌧️ Rain Detection<br/>YL-83]
        E[💡 Light Sensor<br/>LDR]
    end
    
    subgraph "🔧 Processing Core"
        F[ESP32 Controller<br/>Dual Core 240MHz]
        G[📊 Data Processing<br/>Real-time Analysis]
        H[🗄️ SQLite Database<br/>Persistent Storage]
    end
    
    subgraph "🌐 Web Interface"
        I[📱 Dashboard UI<br/>Responsive Design]
        J[🔐 Authentication<br/>Secure Login]
        K[📊 Live Monitoring<br/>Real-time Updates]
    end
    
    subgraph "⚙️ Control Systems"
        L[🚪 Flood Gate<br/>Servo Control]
        M[🔄 Automation<br/>Smart Logic]
        N[📝 Activity Logs<br/>Complete Audit]
    end
    
    A --> F
    B --> F
    C --> F
    D --> F
    E --> F
    
    F --> G
    G --> H
    G --> I
    I --> J
    I --> K
    
    G --> M
    M --> L
    F --> N
    J --> N
    
    style F fill:#2563eb,stroke:#1d4ed8,stroke-width:3px,color:#fff
    style I fill:#10b981,stroke:#059669,stroke-width:2px,color:#fff
    style H fill:#f59e0b,stroke:#d97706,stroke-width:2px,color:#fff
    style L fill:#ef4444,stroke:#dc2626,stroke-width:2px,color:#fff
```

---

### 📡 **Data Flow Architecture**

```mermaid
graph LR
    subgraph "📊 Input Layer"
        S1[🌊 Water Level]
        S2[🌡️ Temperature]
        S3[💨 Humidity]
        S4[🌧️ Rain Status]
        S5[💡 Light Level]
    end
    
    subgraph "🔧 Processing Pipeline"
        P1[📥 Data Acquisition]
        P2[🔍 Validation & Filtering]
        P3[📊 Real-time Processing]
        P4[💾 Database Storage]
    end
    
    subgraph "🌐 Output Systems"
        O1[📱 Live Dashboard]
        O2[🔐 User Interface]
        O3[⚙️ Control Commands]
        O4[📝 Activity Logs]
    end
    
    S1 --> P1
    S2 --> P1
    S3 --> P1
    S4 --> P1
    S5 --> P1
    
    P1 --> P2
    P2 --> P3
    P3 --> P4
    
    P3 --> O1
    P4 --> O2
    P3 --> O3
    P2 --> O4
    
    style P1 fill:#3b82f6,stroke:#2563eb,stroke-width:2px,color:#fff
    style P3 fill:#10b981,stroke:#059669,stroke-width:2px,color:#fff
    style O1 fill:#f59e0b,stroke:#d97706,stroke-width:2px,color:#fff
```

---

### 🌐 **Network & Security Architecture**

```mermaid
graph TB
    subgraph "🌍 External Network"
        INT[🌐 Internet]
        RTR[📡 WiFi Router<br/>2.4GHz Network]
    end
    
    subgraph "🏠 Local Network"
        ESP[🔧 ESP32 Device<br/>192.168.x.x]
        SRV[⚡ Web Server<br/>Port 80]
        DB[(🗄️ SQLite DB<br/>Local Storage)]
    end
    
    subgraph "👥 Client Access"
        DSK[💻 Desktop Browser<br/>Full Interface]
        MOB[📱 Mobile Browser<br/>Responsive UI]
        TAB[🖥️ Tablet Interface<br/>Touch Optimized]
    end
    
    subgraph "🛡️ Security Layer"
        AUTH[🔐 Authentication<br/>bcrypt + Sessions]
        CSRF[🛡️ CSRF Protection<br/>Token Validation]
        SQL[💾 SQL Security<br/>Parameterized Queries]
    end
    
    INT -.-> RTR
    RTR -.-> ESP
    ESP --> SRV
    SRV --> DB
    
    SRV -.-> DSK
    SRV -.-> MOB
    SRV -.-> TAB
    
    SRV --> AUTH
    AUTH --> CSRF
    CSRF --> SQL
    
    style ESP fill:#2563eb,stroke:#1d4ed8,stroke-width:3px,color:#fff
    style SRV fill:#10b981,stroke:#059669,stroke-width:2px,color:#fff
    style AUTH fill:#ef4444,stroke:#dc2626,stroke-width:2px,color:#fff
```

---

## 🔧 **Hardware Requirements**

<div align="center">

| 🎯 **Component** | 📏 **Specifications** | 🔌 **Power Requirements** | 📝 **Notes** |
|------------------|----------------------|---------------------------|---------------|
| **ESP32 DevKit V1** | 38-pin, dual-core 240MHz | 3.3V @ 240mA | Main microcontroller |
| **HC-SR04 Ultrasonic** | 2-400cm range, ±3mm accuracy | 5V @ 15mA | Water level detection |
| **DHT22 Sensor** | -40°C to 80°C, 0-100% RH | 3.3V @ 2.5mA | Temperature & humidity |
| **SG90 Servo Motor** | 180° rotation, 1.5kg torque | 5V @ 100-600mA | Flood gate control |
| **YL-83 Rain Sensor** | Analog + digital output | 3.3V @ 20mA | Rain detection |
| **LDR + Resistor** | Light-dependent resistor | 3.3V @ 0.1mA | Light monitoring |
| **Power Supply** | 5V 2A adapter | AC input | System power |
| **Breadboard & Wires** | Standard breadboard | - | Connections |

</div>

### ⚡ **Power Analysis & Requirements**

<div align="center">

| ⚙️ **Operating Mode** | 🔋 **Power Consumption** | ⏱️ **Duration** | 📊 **Efficiency** |
|----------------------|-------------------------|-----------------|------------------|
| **Normal Operation** | ~400mA @ 5V | Continuous | Optimized consumption |
| **Peak Load (Servo)** | ~900mA @ 5V | During gate operation | Short duration spikes |
| **Standby Mode** | ~300mA @ 5V | Sensor monitoring only | Power-efficient |
| **WiFi Transmission** | ~450mA @ 5V | Data upload periods | Burst communication |

</div>

---

## 🚀 **Installation & Setup Guide**

### 📋 **Development Environment Setup**

<div align="center">

| 🛠️ **Requirement** | 📊 **Version** | 🔗 **Download Source** | ✅ **Installation Steps** |
|--------------------|----------------|------------------------|-------------------------|
| **Arduino IDE** | 2.0 or newer | arduino.cc/downloads | Standard installation |
| **ESP32 Board Package** | Latest stable | Espressif Systems | Board Manager installation |
| **USB Drivers** | Platform-specific | Device manufacturer | System-dependent setup |

</div>

### 📚 **Arduino IDE Library Installation Guide**

<div align="center">

#### **Required Core Libraries**

| 📦 **Library Name** | 👨‍💻 **Author** | 🎯 **Purpose** | ⭐ **Priority** |
|--------------------|----------------|----------------|----------------|
| **WiFi** | Espressif | WiFi connectivity | Critical (Built-in) |
| **WebServer** | Espressif | HTTP web server | Critical (Built-in) |
| **FS** | Espressif | File system operations | Critical (Built-in) |
| **SPIFFS** | Espressif | Flash file storage | Essential (Built-in) |

#### **Database & JSON Libraries**

| 📦 **Library Name** | 👨‍💻 **Author** | 🎯 **Purpose** | ⭐ **Priority** |
|--------------------|----------------|----------------|----------------|
| **sqlite3** | Espressif | SQLite database | Critical |
| **ArduinoJson** | Benoit Blanchon | JSON data handling | Essential |

#### **Sensor Libraries**

| 📡 **Library Name** | 👨‍💻 **Author** | 🔧 **Compatible Sensors** | 🎯 **Usage** |
|--------------------|----------------|---------------------------|-------------|
| **DHT sensor library** | Adafruit | DHT22, DHT11 | Temperature & humidity |
| **NewPing** | Tim Eckel | HC-SR04 ultrasonic | Water level detection |
| **ESP32Servo** | Kevin Harrington | SG90, MG996R | Gate control servo |

#### **Display & Interface Libraries**

| 🖥️ **Library Name** | 👨‍💻 **Author** | 📊 **Features** | 🎯 **Usage** |
|--------------------|----------------|----------------|-------------|
| **LiquidCrystal_I2C** | Frank de Brabander | I2C LCD display | Status display |
| **Wire** | Arduino | I2C communication | Built-in ESP32 |

#### **Security & Authentication**

| 🔐 **Library Name** | 👨‍💻 **Author** | 🛡️ **Purpose** | 🎯 **Implementation** |
|--------------------|----------------|----------------|---------------------|
| **mbedtls** | ARM | Encryption/hashing | Built-in ESP32 |
| **Preferences** | Espressif | Secure storage | Built-in ESP32 |

</div>

### 🛠️ **Library Installation Commands**

```bash
# Arduino IDE Library Manager Installation
1. Open Arduino IDE → Tools → Manage Libraries
2. Search and install these libraries:
   - "DHT sensor library" by Adafruit
   - "NewPing" by Tim Eckel  
   - "ESP32Servo" by Kevin Harrington
   - "LiquidCrystal I2C" by Frank de Brabander
   - "ArduinoJson" by Benoit Blanchon

# Built-in ESP32 Libraries (Already Available)
- WiFi, WebServer, FS, SPIFFS
- Wire, Preferences, mbedtls
- sqlite3 (if using ESP32 with SQLite support)
```

### 🚫 **Libraries NOT Used in This Project**

The following libraries are **NOT required** for this implementation:
- ~~ESPAsyncWebServer~~ (Using built-in WebServer)
- ~~AsyncTCP~~ (Using synchronous connections)
- ~~OneWire~~ (Not using DS18B20 sensors)
- ~~DallasTemperature~~ (Using DHT22 instead)
- ~~NTPClient~~ (Using local timestamps)
- ~~PubSubClient~~ (No MQTT implementation)

### ✅ **Library Verification Checklist**

After installation, verify these libraries in Arduino IDE:

```cpp
// Essential includes used in the actual project
#include <WiFi.h>              // ✅ Built-in ESP32 - Network connectivity
#include <WebServer.h>         // ✅ Built-in ESP32 - HTTP server
#include <FS.h>                // ✅ Built-in ESP32 - File operations
#include <SPIFFS.h>            // ✅ Built-in ESP32 - Flash storage
#include <ArduinoJson.h>       // ✅ Library Manager - JSON handling
#include <DHT.h>               // ✅ Library Manager - Temperature/humidity
#include <NewPing.h>           // ✅ Library Manager - Ultrasonic sensor
#include <ESP32Servo.h>        // ✅ Library Manager - Servo control
#include <LiquidCrystal_I2C.h> // ✅ Library Manager - LCD display
#include <Wire.h>              // ✅ Built-in ESP32 - I2C communication
#include <Preferences.h>       // ✅ Built-in ESP32 - Settings storage
#include <sqlite3.h>           // ✅ ESP32 SQLite - Database operations
```

**🎯 Hardware-Specific Pin Definitions:**
```cpp
// Sensor pin assignments used in code
#define DHT_PIN 4              // DHT22 data pin
#define TRIG_PIN 5             // HC-SR04 trigger
#define ECHO_PIN 18            // HC-SR04 echo
#define SERVO_PIN 13           // Servo motor control
#define RAIN_PIN 34            // Rain sensor (analog)
#define LDR_PIN 35             // Light sensor (analog)
#define SDA_PIN 21             // I2C data (LCD)
#define SCL_PIN 22             // I2C clock (LCD)
```

---

## 📱 **User Interface Features**

### 🎨 **Dashboard Components**

<div align="center">

| 🖥️ **UI Component** | 📊 **Functionality** | 📱 **Mobile Support** | ⚡ **Real-Time Updates** |
|--------------------|---------------------|---------------------|-------------------------|
| **Water Level Gauge** | Animated SVG circle | Touch-friendly | 3-second intervals |
| **Environmental Grid** | Live sensor data | Responsive layout | Continuous monitoring |
| **Gate Control Panel** | Interactive buttons | Large touch targets | Immediate response |
| **System Alerts** | Priority notifications | Mobile-optimized | Event-driven updates |
| **Action Center** | Quick access tools | Swipe gestures | Context-sensitive |
| **Live Logs Display** | Real-time activity | Scrollable interface | Auto-refresh |

</div>

### 🔐 **Authentication Interface**

<div align="center">

| 🔑 **Auth Feature** | 🎨 **Design Element** | 🛡️ **Security Measure** | 📱 **Mobile Experience** |
|--------------------|----------------------|------------------------|------------------------|
| **Login Form** | Two-panel layout | Secure credential handling | Touch-optimized inputs |
| **Registration** | Tabbed interface | Password strength validation | Real-time feedback |
| **Session Management** | Seamless transitions | Auto-logout protection | Background persistence |
| **Error Handling** | User-friendly messages | Brute force protection | Graceful degradation |

</div>

---

## 🐛 **Troubleshooting Matrix**

### ❌ **Common Issues & Solutions**

<div align="center">

| 🚨 **Issue Category** | 🔍 **Problem** | ✅ **Solution** | 🎯 **Prevention** |
|----------------------|----------------|----------------|------------------|
| **Network Connectivity** | WiFi connection failure | Check 2.4GHz network | Use strong passwords |
| **Sensor Readings** | Inconsistent data | Verify wiring/power | Use quality components |
| **Web Interface** | Page loading issues | Check IP address | Clear browser cache |
| **Upload Errors** | Code deployment fails | Select correct board | Close serial monitor |
| **Authentication** | Login problems | Reset credentials | Check database integrity |
| **Performance** | System lag | Monitor memory usage | Optimize code |

</div>

---

## 🎓 **Educational & Professional Value**

### 📚 **Learning Outcomes Matrix**

<div align="center">

| 🎯 **Skill Category** | 📊 **Technical Focus** | 🏢 **Industry Application** | ⭐ **Proficiency Level** |
|----------------------|------------------------|----------------------------|------------------------|
| **Embedded Programming** | ESP32 + FreeRTOS | IoT device development | Advanced |
| **Web Development** | Full-stack technologies | Modern web applications | Professional |
| **Database Design** | SQLite + optimization | Data management systems | Intermediate |
| **Security Implementation** | Authentication + encryption | Cybersecurity practices | Advanced |
| **System Integration** | Hardware-software fusion | Industrial automation | Expert |
| **User Experience** | Responsive design | Interface development | Professional |

</div>

---

## 🔮 **Future Enhancement Roadmap**

<div align="center">

| 🚀 **Enhancement** | 📊 **Complexity** | ⏱️ **Timeline** | 💰 **Resource Requirement** |
|-------------------|------------------|----------------|---------------------------|
| **📧 Email Notifications** | Medium | 2-3 weeks | Moderate development |
| **📊 Data Visualization** | High | 4-6 weeks | Significant effort |
| **🌙 Dark Mode Interface** | Low | 1 week | Minimal resources |
| **📱 Mobile App** | High | 8-12 weeks | Major development |
| **☁️ Cloud Integration** | Very High | 12-16 weeks | Extensive resources |
| **🔔 Push Notifications** | Medium | 3-4 weeks | Moderate effort |
| **📈 AI Analytics** | Very High | 16+ weeks | Research & development |
| **🗺️ GPS Integration** | Medium | 2-4 weeks | Hardware additions |

</div>

---

## 📄 **Project Information**

<div align="center">

| 📋 **Project Details** | 📊 **Information** |
|------------------------|-------------------|
| **License** | MIT License - Educational & Commercial Use |
| **Development Status** | Production Ready |
| **Documentation** | Comprehensive & Professional |
| **Support** | GitHub Issues & Community |
| **Target Audience** | Students, Developers, IoT Enthusiasts |
| **Skill Level** | Intermediate to Advanced |

</div>

---

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

<sub>🎓 Professional IoT Development Project | Built for Learning & Real-World Application | © 2024 Lian Cunanan & Development Team</sub>

</div>
