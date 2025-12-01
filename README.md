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

## 🎯 **Project Overview**

The **IoT Flood Monitor Pro** is a complete, production-ready flood monitoring solution featuring a professional web dashboard, secure user authentication, comprehensive logging system, and automated flood control. Built with modern web technologies and enterprise-grade security for both educational and commercial deployment.

## 🌟 **Key Highlights**

<div align="center">

| 🎯 **Feature** | 📊 **Capability** | 🚀 **Technology** | ⭐ **Level** |
|---------------|------------------|------------------|-------------|
| **Real-Time Monitoring** | Live sensor data with 3-second updates | AJAX + SVG Animations | Professional |
| **User Authentication** | Complete registration/login system | SQLite + bcrypt | Enterprise |
| **Web Dashboard** | Responsive interface for all devices | HTML5 + CSS3 + JavaScript | Production |
| **Data Logging** | Export logs in TXT/CSV formats | Professional logging framework | Advanced |
| **Gate Control** | Automated flood gate management | Servo motor with PWM control | Industrial |
| **Security** | Session management + encryption | JWT-like tokens + SQL protection | Enterprise |

</div>

## ✨ **Complete Feature Matrix**

### 🌊 **Advanced Sensor Monitoring**

<div align="center">

| 📡 **Sensor Type** | 📏 **Range/Accuracy** | 🔌 **Interface** | 📊 **Features** |
|-------------------|---------------------|-----------------|----------------|
| **💧 Water Level (HC-SR04)** | 2-400cm range | Digital I/O | Animated gauge, color coding, trend analysis |
| **🌡️ Temperature (DHT22)** | -40°C to 80°C ±0.5°C | One-wire protocol | Real-time display, historical tracking |
| **💨 Humidity (DHT22)** | 0-100% ±2% RH | One-wire protocol | Live updates, trend indicators |
| **🌧️ Rain Detection (YL-83)** | Analog + Digital | ADC + GPIO | Weather status, precipitation alerts |
| **💡 Light Level (LDR)** | 0-4095 ADC units | Analog input | Ambient monitoring, day/night detection |

</div>

### 🎛️ **Professional Control Systems**

<div align="center">

| ⚙️ **Control Type** | 🔧 **Mechanism** | 🎯 **Precision** | 🛡️ **Safety Features** |
|--------------------|------------------|------------------|----------------------|
| **🚪 Flood Gate** | SG90 Servo Motor | 180° positioning | Manual override, position feedback |
| **🔄 Automation** | Threshold-based | Microsecond timing | Safety interlocks, emergency stop |
| **👤 User Commands** | Web interface | Real-time response | Authentication required, audit logging |
| **📊 Status Display** | Live indicators | Position tracking | Visual feedback, error reporting |

</div>

### 🔒 **Enterprise Security Architecture**

<div align="center">

| 🛡️ **Security Layer** | 🔐 **Implementation** | 🎯 **Protection Level** | ✅ **Compliance** |
|----------------------|---------------------|------------------------|------------------|
| **Authentication** | bcrypt password hashing | Military-grade encryption | Industry standard |
| **Session Management** | JWT-like tokens | Configurable expiry | OWASP compliant |
| **Database Security** | Parameterized queries | SQL injection prevention | Enterprise-grade |
| **Access Control** | Role-based permissions | Multi-level authorization | Professional |
| **Activity Monitoring** | Complete audit trail | IP tracking + timestamps | Forensic-ready |
| **Brute Force Protection** | Rate limiting + lockout | Exponential backoff | Security hardened |

</div>

### 📊 **Modern Web Technologies**

<div align="center">

| 🌐 **Technology Stack** | 💻 **Implementation** | 📱 **Responsive Design** | ⚡ **Performance** |
|------------------------|----------------------|-------------------------|------------------|
| **Frontend Framework** | HTML5 + CSS Grid/Flexbox | Mobile-first approach | Optimized rendering |
| **Styling System** | CSS custom properties | 50+ design variables | Consistent theming |
| **JavaScript Engine** | ES6+ modern features | Touch-friendly controls | Real-time updates |
| **Data Visualization** | SVG animations | Interactive gauges | Smooth transitions |
| **Typography** | Inter font family | Proper hierarchy | Professional appearance |
| **Accessibility** | WCAG 2.1 compliant | Screen reader support | Universal design |

</div>

### 📝 **Advanced Logging & Analytics**

<div align="center">

| 📊 **Logging Feature** | 🔍 **Capability** | 📅 **Data Management** | 📤 **Export Options** |
|------------------------|-------------------|------------------------|---------------------|
| **Real-Time Generation** | Microsecond precision | Automatic timestamps | Live log viewer |
| **Log Categorization** | System/User/Sensor/Control | Organized by component | Filtered exports |
| **Data Retention** | Configurable policies | Automatic rotation | Historical analysis |
| **Export Formats** | TXT + CSV support | Custom formatting | Professional reports |
| **Analytics Dashboard** | Statistics + trends | Visual representations | Data insights |
| **Mobile Viewer** | Touch-optimized | Responsive interface | On-the-go access |

</div>

### 🌐 **Network & Connectivity**

<div align="center">

| 📡 **Network Feature** | 🔧 **Technology** | 🚀 **Performance** | 🛡️ **Reliability** |
|------------------------|-------------------|-------------------|-------------------|
| **WiFi Management** | Auto-connection + fallback | High-speed data transfer | Connection recovery |
| **Web Server** | Asynchronous architecture | Concurrent request handling | Load balancing |
| **API Endpoints** | RESTful design | JSON communication | Structured data |
| **Network Discovery** | mDNS support | floodmonitor.local access | Easy connectivity |
| **Data Compression** | Optimized responses | Reduced bandwidth usage | Faster loading |
| **Timeout Handling** | Graceful error recovery | Request management | Stable connections |

</div>

## 🏗️ **System Architecture Overview**

### 📋 **Component Integration**

<div align="center">

| 🔧 **System Layer** | 📊 **Components** | 🔄 **Data Flow** | ⚡ **Processing** |
|--------------------|--------------------|-------------------|------------------|
| **Sensor Layer** | HC-SR04, DHT22, YL-83, LDR | Continuous monitoring | Real-time acquisition |
| **Processing Core** | ESP32 dual-core controller | Data validation + filtering | High-performance computing |
| **Storage Layer** | SQLite database | Persistent data storage | ACID compliance |
| **Presentation** | Web dashboard | User interface | Interactive visualization |
| **Control Systems** | Servo motor integration | Automated responses | Precision control |

</div>

### 🗂️ **Professional File Architecture**

<div align="center">

| 📄 **File Category** | 🎯 **Purpose** | 📊 **Size** | 🔧 **Technology** |
|---------------------|----------------|-------------|------------------|
| **Main Application** | FloodMonitor_ESP32.ino | Core logic | Arduino C++ |
| **Web Interface** | index_html.h | Dashboard UI | HTML5 + CSS3 |
| **Authentication** | login_html.h + register_html.h | User management | Secure forms |
| **Styling Framework** | style_css.h | Professional design | 15KB+ CSS |
| **Database Engine** | database.h | Data management | SQLite implementation |
| **Logging System** | logging.h | Activity tracking | Professional framework |
| **Security Layer** | security.h | Encryption + auth | Enterprise-grade |

</div>

## 🔧 **Hardware Specifications**

### 📦 **Component Requirements**

<div align="center">

| 🛠️ **Component** | 📏 **Specifications** | 🔌 **Power Requirements** | 💰 **Estimated Cost** |
|------------------|----------------------|---------------------------|---------------------|
| **ESP32 DevKit V1** | 38-pin, dual-core 240MHz | 3.3V @ 240mA | $8-12 USD |
| **HC-SR04 Ultrasonic** | 2-400cm range, ±3mm accuracy | 5V @ 15mA | $2-4 USD |
| **DHT22 Sensor** | -40°C to 80°C, 0-100% RH | 3.3V @ 2.5mA | $3-5 USD |
| **SG90 Servo Motor** | 180° rotation, 1.5kg torque | 5V @ 100-600mA | $2-4 USD |
| **YL-83 Rain Sensor** | Analog + digital output | 3.3V @ 20mA | $1-3 USD |
| **LDR + Resistor** | Light-dependent resistor | 3.3V @ 0.1mA | $1-2 USD |
| **Power Supply** | 5V 2A adapter | AC input | $5-8 USD |

</div>

### 🔌 **Pin Assignment Table**

<div align="center">

| 📍 **ESP32 Pin** | 🎯 **Function** | 📡 **Sensor/Component** | ⚡ **Signal Type** |
|------------------|----------------|------------------------|-------------------|
| **GPIO 2** | PWM Control | Servo Motor Signal | Digital PWM |
| **GPIO 4** | Data Communication | DHT22 Sensor | One-wire Digital |
| **GPIO 5** | Trigger Signal | HC-SR04 Ultrasonic | Digital Output |
| **GPIO 18** | Echo Reception | HC-SR04 Ultrasonic | Digital Input |
| **GPIO 34** | Analog Reading | Rain Sensor (YL-83) | Analog Input |
| **GPIO 35** | Light Detection | LDR Photoresistor | Analog Input |
| **5V Rail** | High Power Supply | HC-SR04 + Servo | Power Distribution |
| **3.3V Rail** | Logic Power | DHT22 + Rain + LDR | Logic Level |

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

## 🚀 **Installation & Setup Guide**

### 📋 **Development Environment Setup**

<div align="center">

| 🛠️ **Requirement** | 📊 **Version** | 🔗 **Download Source** | ✅ **Installation Steps** |
|--------------------|----------------|------------------------|-------------------------|
| **Arduino IDE** | 2.0 or newer | arduino.cc/downloads | Standard installation |
| **ESP32 Board Package** | Latest stable | Espressif Systems | Board Manager installation |
| **USB Drivers** | Platform-specific | Device manufacturer | System-dependent setup |

</div>

### 📚 **Required Libraries Matrix**

<div align="center">

| 📦 **Library Name** | 👨‍💻 **Author** | 🎯 **Purpose** | ⭐ **Priority** |
|--------------------|----------------|----------------|----------------|
| **ESPAsyncWebServer** | me-no-dev | Web server functionality | Critical |
| **AsyncTCP** | me-no-dev | Asynchronous networking | Critical |
| **ArduinoJson** | Benoit Blanchon | JSON data handling | Essential |
| **DHT Sensor Library** | Adafruit | Temperature/humidity | Essential |
| **NewPing** | Tim Eckel | Ultrasonic sensor | Essential |
| **ESP32Servo** | Kevin Harrington | Servo motor control | Essential |
| **SQLite3** | Richard T. Hatch | Database functionality | Optional |

</div>

### 🌐 **Network Configuration Options**

<div align="center">

| 🔧 **Configuration Method** | 🎯 **Use Case** | 🛡️ **Security Level** | 📱 **User Experience** |
|----------------------------|----------------|----------------------|----------------------|
| **WiFi Credentials in Code** | Development/Testing | Basic | Simple setup |
| **WiFiManager Library** | Production Deployment | Enhanced | User-friendly portal |
| **Access Point Fallback** | Network Issues | Secure | Automatic recovery |
| **mDNS Discovery** | Easy Access | Standard | floodmonitor.local |

</div>

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

### 🏢 **Industry Applications**

<div align="center">

| 🏭 **Industry Sector** | 🎯 **Application** | 📊 **Scale** | 🚀 **Implementation** |
|------------------------|-------------------|-------------|----------------------|
| **Municipal Services** | City flood monitoring | Large-scale | Emergency response |
| **Industrial Control** | Process monitoring | Medium-scale | Safety systems |
| **Smart Buildings** | Environmental control | Building-wide | Automation systems |
| **Agriculture** | Irrigation management | Farm-scale | Precision farming |
| **Transportation** | Infrastructure monitoring | Regional | Traffic management |
| **Energy Management** | System monitoring | Grid-scale | Smart grid integration |

</div>

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
