#pragma once

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <title>Flood Monitoring</title>
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <link rel="stylesheet" href="/style.css">
</head>
<body>
  <div class="header">
    <div>
      <h1>Flood Monitor</h1>
      <small>Mode: <span id="sys-mode" style="font-weight:bold; color:#0056b3;">LOADING...</span></small>
      <small>User: <span id="current-user" style="font-weight:bold; color:#0056b3;">Loading...</span></small>
    </div>

    <div style="display: flex; align-items: center; gap: 12px;">
      <button class="logout-btn" onclick="logout()">Logout</button>
      <div class="status-dot" id="ws-status"></div>
    </div>
  </div>

  <!-- Alert Banner -->
  <div id="alert-banner" class="alert-banner hidden">
    <span id="alert-message">System Alert</span>
    <button onclick="dismissAlert()" class="alert-dismiss">✕</button>
  </div>

  <div class="grid-container">
    <div style="grid-column: 1 / -1; text-align: right;">
        <button class="qr-btn" onclick="toggleQR()">&#128241; WiFi Info</button>
        <button class="qr-btn" onclick="downloadData()">&#128190; Download Data</button>
        <button class="qr-btn" onclick="viewDatabase()">&#128248; System Status</button>
        <button class="qr-btn" onclick="factoryReset()">&#128295; Factory Reset</button>
    </div>

    <div class="card card-water" id="water-card">
      <h2>Water Level <span id="water-alert" class="sensor-alert">⚠️</span></h2>
      <div class="gauge">
        <div class="gauge-body">
          <div class="gauge-fill" id="water-fill"></div>
          <div class="gauge-cover" id="water-value">0%</div>
        </div>
      </div>
      <p>Raw: <span id="water-raw">0</span></p>
      <p class="threshold-info">Alert: ≥70% | Critical: ≥85%</p>
    </div>

    <div class="card card-gate" id="gate-card">
      <h2>Gate Status <span id="gate-alert" class="sensor-alert">⚠️</span></h2>
      <h3 id="gate-status">CLOSED</h3>
      <div class="maintenance-controls">
        <button onclick="toggleGate('OPEN')">Open (Maint)</button>
        <button onclick="toggleGate('CLOSE')">Close (Maint)</button>
      </div>
    </div>

    <div class="card card-env" id="env-card">
      <h2>Environment <span id="env-alert" class="sensor-alert">⚠️</span></h2>
      <p>Temp: <span id="temp-value">0</span>&deg;C <span id="temp-alert" class="inline-alert">🔥</span></p>
      <p>Hum: <span id="humidity-value">0</span>% <span id="humidity-alert" class="inline-alert">💧</span></p>
      <p>Rain: <span id="rain-status">--</span> <span id="rain-alert" class="inline-alert">🌧️</span></p>
      <p>Light: <span id="light-value">0</span> <span id="light-alert" class="inline-alert">💡</span></p>
      <div class="threshold-info">
        <small>Temp Alert: >35°C | Humidity Alert: >90% | Rain Alert: Active | Light Alert: <100</small>
      </div>
    </div>
  </div>

  <div id="qr-modal" class="modal">
    <div class="modal-content">
      <span class="close-btn" onclick="toggleQR()">&times;</span>
      <h3>Connect to Network</h3>
      <p><strong>SSID:</strong> FloodMonitor_Network</p>
      <p><strong>Password:</strong> 12345678</p>
    </div>
  </div>

  <div id="db-modal" class="modal">
    <div class="modal-content">
      <span class="close-btn" onclick="toggleDatabase()">&times;</span>
      <h3>Database Status</h3>
      <div id="db-status-content">Loading...</div>
    </div>
  </div>

  <script src="/script.js?v=4"></script>

  <script>
    let currentUser = 'admin';
    let alertAudio = null;
    let activeAlerts = new Set();

    // Sensor thresholds
    const THRESHOLDS = {
      water: {
        warning: 70,   // Warning at 70%
        critical: 85   // Critical at 85%
      },
      temperature: {
        warning: 35,   // Warning above 35°C
        critical: 40   // Critical above 40°C
      },
      humidity: {
        warning: 85,   // Warning above 85%
        critical: 95   // Critical above 95%
      },
      light: {
        warning: 100,  // Warning below 100 (too dark)
        critical: 50   // Critical below 50 (very dark)
      }
    };

    // Initialize audio for alerts
    function initAlertAudio() {
      if (!alertAudio) {
        alertAudio = new Audio('data:audio/wav;base64,UklGRnoGAABXQVZFZm10IBAAAAABAAEAQB8AAEAfAAABAAgAZGF0YQoGAACBhYqFbF1fdJivrJBhNjVgodDbq2EcBj+a2/LDciUFLIHO8tiJNwgZaLvt559NEAxQp+PwtmMcBjiR1/LMeSwFJHfH8N2QQAoUXrTp66hVFApGn+DyvmwhBjWc4PzHdSEFLIzM8diJOQceab3n3pVQEQt6yOnLdCkHL4/N8OORTgwJktTp3aJdEg=='');
      }
    }

    // Check all sensor thresholds and trigger alerts
    function checkSensorAlerts(data) {
      const newAlerts = new Set();

      // Water Level Alerts
      if (data.waterLevel >= THRESHOLDS.water.critical) {
        newAlerts.add('water_critical');
        showAlert(`🚨 CRITICAL: Water level at ${data.waterLevel}%! Gate should be OPEN!`, 'critical');
        highlightSensorCard('water-card', 'critical');
        showSensorAlert('water-alert');
      } else if (data.waterLevel >= THRESHOLDS.water.warning) {
        newAlerts.add('water_warning');
        showAlert(`⚠️ WARNING: Water level at ${data.waterLevel}%`, 'warning');
        highlightSensorCard('water-card', 'warning');
        showSensorAlert('water-alert');
      } else {
        clearSensorAlert('water-card', 'water-alert');
      }

      // Temperature Alerts
      if (data.temperature >= THRESHOLDS.temperature.critical) {
        newAlerts.add('temp_critical');
        showAlert(`🔥 CRITICAL: Temperature ${data.temperature}°C is dangerously high!`, 'critical');
        showInlineAlert('temp-alert');
      } else if (data.temperature >= THRESHOLDS.temperature.warning) {
        newAlerts.add('temp_warning');
        showAlert(`🌡️ WARNING: High temperature ${data.temperature}°C`, 'warning');
        showInlineAlert('temp-alert');
      } else {
        clearInlineAlert('temp-alert');
      }

      // Humidity Alerts
      if (data.humidity >= THRESHOLDS.humidity.critical) {
        newAlerts.add('humidity_critical');
        showAlert(`💧 CRITICAL: Humidity ${data.humidity}% is extremely high!`, 'critical');
        showInlineAlert('humidity-alert');
      } else if (data.humidity >= THRESHOLDS.humidity.warning) {
        newAlerts.add('humidity_warning');
        showAlert(`💨 WARNING: High humidity ${data.humidity}%`, 'warning');
        showInlineAlert('humidity-alert');
      } else {
        clearInlineAlert('humidity-alert');
      }

      // Rain Alerts
      if (data.rainStatus && data.rainStatus.toLowerCase().includes('rain')) {
        newAlerts.add('rain_active');
        showAlert(`🌧️ ALERT: Rain detected! Water levels may rise.`, 'warning');
        showInlineAlert('rain-alert');
      } else {
        clearInlineAlert('rain-alert');
      }

      // Light Alerts (too dark conditions)
      if (data.lightValue <= THRESHOLDS.light.critical) {
        newAlerts.add('light_critical');
        showAlert(`🌙 CRITICAL: Very low light detected (${data.lightValue})`, 'warning');
        showInlineAlert('light-alert');
      } else if (data.lightValue <= THRESHOLDS.light.warning) {
        newAlerts.add('light_warning');
        showAlert(`💡 WARNING: Low light conditions (${data.lightValue})`, 'info');
        showInlineAlert('light-alert');
      } else {
        clearInlineAlert('light-alert');
      }

      // Gate Status Alert (if water is high but gate is closed)
      if (data.waterLevel >= THRESHOLDS.water.warning && data.gateStatus === 'CLOSED') {
        newAlerts.add('gate_mismatch');
        showAlert(`🚪 ALERT: Water level ${data.waterLevel}% but gate is CLOSED!`, 'critical');
        highlightSensorCard('gate-card', 'warning');
        showSensorAlert('gate-alert');
      } else {
        clearSensorAlert('gate-card', 'gate-alert');
      }

      // Play alert sound for new critical alerts
      const hasNewCritical = Array.from(newAlerts).some(alert => 
        alert.includes('critical') && !activeAlerts.has(alert)
      );
      
      if (hasNewCritical) {
        playAlertSound();
        logActivity('CRITICAL_ALERT_TRIGGERED', { alerts: Array.from(newAlerts) });
      }

      // Update active alerts
      activeAlerts = newAlerts;
    }

    // Show alert banner
    function showAlert(message, type = 'warning') {
      const banner = document.getElementById('alert-banner');
      const messageElement = document.getElementById('alert-message');
      
      banner.className = `alert-banner ${type}`;
      messageElement.textContent = message;
      banner.classList.remove('hidden');

      // Auto-hide info alerts after 5 seconds
      if (type === 'info') {
        setTimeout(() => {
          dismissAlert();
        }, 5000);
      }

      // Log alert
      logActivity('SENSOR_ALERT', { message: message, type: type });
    }

    // Dismiss alert banner
    function dismissAlert() {
      document.getElementById('alert-banner').classList.add('hidden');
    }

    // Highlight sensor card
    function highlightSensorCard(cardId, alertType) {
      const card = document.getElementById(cardId);
      card.classList.remove('card-warning', 'card-critical');
      card.classList.add(`card-${alertType}`);
    }

    // Clear sensor card highlighting
    function clearSensorAlert(cardId, alertId) {
      const card = document.getElementById(cardId);
      const alert = document.getElementById(alertId);
      card.classList.remove('card-warning', 'card-critical');
      if (alert) alert.style.display = 'none';
    }

    // Show sensor alert icon
    function showSensorAlert(alertId) {
      const alert = document.getElementById(alertId);
      if (alert) {
        alert.style.display = 'inline';
        alert.style.color = '#ff4444';
        alert.style.animation = 'pulse 1s infinite';
      }
    }

    // Show inline alert icon
    function showInlineAlert(alertId) {
      const alert = document.getElementById(alertId);
      if (alert) {
        alert.style.display = 'inline';
        alert.style.animation = 'pulse 1s infinite';
      }
    }

    // Clear inline alert icon
    function clearInlineAlert(alertId) {
      const alert = document.getElementById(alertId);
      if (alert) alert.style.display = 'none';
    }

    // Play alert sound
    function playAlertSound() {
      initAlertAudio();
      if (alertAudio) {
        alertAudio.play().catch(() => {
          // Browser may block autoplay, fail silently
        });
      }
    }

    // Enhanced sensor data update with alert checking
    function updateSensorData(data) {
      if (!data) return;

      // Update display values
      document.getElementById('water-value').textContent = (data.waterLevel || data.water_percent || 0) + '%';
      document.getElementById('water-fill').style.height = (data.waterLevel || data.water_percent || 0) + '%';
      document.getElementById('water-raw').textContent = data.water_raw || 0;
      
      document.getElementById('temp-value').textContent = data.temperature || data.temp || 0;
      document.getElementById('humidity-value').textContent = data.humidity || 0;
      document.getElementById('rain-status').textContent = data.rainStatus || data.rain_status || '--';
      document.getElementById('light-value').textContent = data.lightValue || data.light_raw || 0;
      document.getElementById('gate-status').textContent = data.gateStatus || data.gate_status || 'UNKNOWN';
      
      // Update system mode
      document.getElementById('sys-mode').textContent = data.mode || 'ONLINE';
      
      // Check for alerts
      const alertData = {
        waterLevel: data.waterLevel || data.water_percent || 0,
        temperature: data.temperature || data.temp || 0,
        humidity: data.humidity || 0,
        rainStatus: data.rainStatus || data.rain_status || '',
        lightValue: data.lightValue || data.light_raw || 0,
        gateStatus: data.gateStatus || data.gate_status || 'UNKNOWN'
      };
      
      checkSensorAlerts(alertData);
    }

    // Poll sensor data every 5 seconds
    setInterval(updateSensorData, 5000);
    updateSensorData(); // Initial load
    
    // WebSocket connection logging
    if (typeof WebSocket !== 'undefined') {
      const ws = new WebSocket('ws://' + window.location.host + ':81');
      
      ws.onopen = function() {
        logActivity('WEBSOCKET_CONNECTED');
        document.getElementById('ws-status').style.backgroundColor = 'green';
      };
      
      ws.onclose = function() {
        logActivity('WEBSOCKET_DISCONNECTED');
        document.getElementById('ws-status').style.backgroundColor = 'red';
      };
      
      ws.onmessage = function(event) {
        try {
          const data = JSON.parse(event.data);
          updateSensorData(data);
        } catch (error) {
          logActivity('WEBSOCKET_DATA_ERROR', { error: error.toString() });
        }
      };
    }

    // Initialize alerts
    initAlertAudio();
    
  </script>

  <style>
    .alert-banner {
      position: fixed;
      top: 0;
      left: 0;
      right: 0;
      padding: 15px;
      text-align: center;
      font-weight: bold;
      z-index: 1000;
      animation: slideDown 0.5s ease;
    }
    
    .alert-banner.warning {
      background: linear-gradient(135deg, #ff9800, #f57c00);
      color: white;
    }
    
    .alert-banner.critical {
      background: linear-gradient(135deg, #f44336, #d32f2f);
      color: white;
      animation: pulse 1s infinite;
    }
    
    .alert-banner.info {
      background: linear-gradient(135deg, #2196f3, #1976d2);
      color: white;
    }
    
    .alert-banner.hidden {
      display: none;
    }
    
    .alert-dismiss {
      background: none;
      border: none;
      color: white;
      font-size: 18px;
      font-weight: bold;
      margin-left: 20px;
      cursor: pointer;
    }
    
    .sensor-alert {
      display: none;
      color: #ff4444;
      font-size: 18px;
    }
    
    .inline-alert {
      display: none;
      font-size: 16px;
    }
    
    .card-warning {
      border-left: 5px solid #ff9800 !important;
      box-shadow: 0 0 10px rgba(255, 152, 0, 0.3) !important;
    }
    
    .card-critical {
      border-left: 5px solid #f44336 !important;
      box-shadow: 0 0 15px rgba(244, 67, 54, 0.5) !important;
      animation: pulse 2s infinite;
    }
    
    .threshold-info {
      font-size: 11px;
      color: #666;
      margin-top: 8px;
    }
    
    @keyframes pulse {
      0% { opacity: 1; }
      50% { opacity: 0.7; }
      100% { opacity: 1; }
    }
    
    @keyframes slideDown {
      from { transform: translateY(-100%); }
      to { transform: translateY(0); }
    }
  </style>

</body>
</html>
)rawliteral";
