#pragma once

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <title>Flood Monitoring System</title>
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <link rel="stylesheet" href="/style.css">
  <link rel="preconnect" href="https://fonts.googleapis.com">
  <link href="https://fonts.googleapis.com/css2?family=Inter:wght@400;500;600;700&display=swap" rel="stylesheet">
</head>
<body>
  <div class="alert-banner" id="alert-banner" style="display: none;">
    <span id="alert-message">System Alert</span>
    <button onclick="dismissAlert()" class="alert-dismiss">✕</button>
  </div>

  <header class="header">
    <div class="header-left">
      <h1>Flood Monitor</h1>
      <div class="header-info">
        <div class="status-badge" id="system-status">
          <span id="sys-mode">LOADING...</span>
        </div>
        <small>User: <strong id="current-user">Loading...</strong></small>
        
        <div class="nav-buttons">
          <button class="nav-btn" onclick="toggleQR()">
            <span class="icon">📱</span>
            <span class="text">WiFi Access</span>
          </button>
          <button class="nav-btn" onclick="downloadData()">
            <span class="icon">📊</span>
            <span class="text">Download Data</span>
          </button>
          <button class="nav-btn" onclick="downloadLogs()">
            <span class="icon">📋</span>
            <span class="text">Activity Logs</span>
          </button>
          <button class="nav-btn" onclick="viewDatabase()">
            <span class="icon">💾</span>
            <span class="text">System Status</span>
          </button>
        </div>
      </div>
    </div>

    <div class="header-controls">
      <button class="logout-btn" onclick="logout()">Logout</button>
      <div class="status-dot" id="ws-status"></div>
    </div>
  </header>

  <div class="container">
    <div class="grid-container">
      <!-- Water Level Card -->
      <div class="card card-water">
        <h2>Water Level Monitor</h2>
        <div class="gauge">
          <div class="gauge-body">
            <div class="gauge-fill" id="water-fill">
              <div class="gauge-cover" id="water-value">0%</div>
            </div>
          </div>
        </div>
        <div class="status-item">
          <span>Raw Reading:</span>
          <span class="status-value" id="water-raw">0</span>
        </div>
        <p class="threshold-info">Alert: ≥70% | Critical: ≥85%</p>
      </div>

      <!-- Gate Control Card -->
      <div class="card card-gate">
        <h2>Gate Control</h2>
        <div class="gate-status">
          <h3 class="gate-closed" id="gate-status">CLOSED</h3>
        </div>
        <div class="maintenance-controls">
          <button class="control-btn btn-open" onclick="toggleGate('OPEN')">
            Open Gate
          </button>
          <button class="control-btn btn-close" onclick="toggleGate('CLOSE')">
            Close Gate
          </button>
        </div>
      </div>

      <!-- Environmental Sensors Card -->
      <div class="card card-env">
        <h2>Environmental Data</h2>
        <div class="status-grid">
          <div class="status-item">
            <span>Temperature</span>
            <span class="status-value"><span id="temp-value">0</span>°C <span id="temp-alert" class="inline-alert">🔥</span></span>
          </div>
          <div class="status-item">
            <span>Humidity</span>
            <span class="status-value"><span id="humidity-value">0</span>% <span id="humidity-alert" class="inline-alert">💧</span></span>
          </div>
          <div class="status-item">
            <span>Weather</span>
            <span class="status-value" id="rain-status">-- <span id="rain-alert" class="inline-alert">🌧️</span></span>
          </div>
          <div class="status-item">
            <span>Light Level</span>
            <span class="status-value" id="light-value">0 <span id="light-alert" class="inline-alert">💡</span></span>
          </div>
        </div>
        <div class="threshold-info">
          <small>Temp Alert: >35°C | Humidity Alert: >90% | Rain Alert: Active | Light Alert: <100</small>
        </div>
      </div>

      <!-- System Database Card -->
      <div class="card card-database">
        <h2>Database Status</h2>
        <div class="db-stats">
          <div class="db-stat">
            <div class="db-stat-value" id="db-records">--</div>
            <div class="db-stat-label">Records</div>
          </div>
          <div class="db-stat">
            <div class="db-stat-value" id="db-size">--</div>
            <div class="db-stat-label">Storage</div>
          </div>
          <div class="db-stat">
            <div class="db-stat-value" id="db-uptime">--</div>
            <div class="db-stat-label">Uptime</div>
          </div>
        </div>
        <button class="view-details-btn" onclick="viewDatabase()">
          View Details
        </button>
      </div>
    </div>
  </div>

  <!-- WiFi Info Modal -->
  <div id="qr-modal" class="modal">
    <div class="modal-content">
      <span class="close-btn" onclick="toggleQR()">&times;</span>
      <h3>🌐 WiFi Network Information</h3>
      <div class="status-grid" style="margin: 1rem 0;">
        <div class="status-item">
          <span>Network Name:</span>
          <strong>FloodMonitor_Network</strong>
        </div>
        <div class="status-item">
          <span>Password:</span>
          <strong>12345678</strong>
        </div>
        <div class="status-item">
          <span>IP Address:</span>
          <strong>192.168.4.1</strong>
        </div>
        <div class="status-item">
          <span>Status:</span>
          <strong class="status-value">Active</strong>
        </div>
      </div>
    </div>
  </div>

  <!-- Database Status Modal -->
  <div id="db-modal" class="modal">
    <div class="modal-content">
      <span class="close-btn" onclick="toggleDatabase()">&times;</span>
      <h3>💾 System Status & Database</h3>
      <div id="db-status-content">
        <div class="loading">Loading system information...</div>
      </div>
    </div>
  </div>

  <script src="/script.js?v=6"></script>
  <script>
    let currentUser = 'admin';
    let alertAudio = null;
    let activeAlerts = new Set();

    // Sensor thresholds
    const THRESHOLDS = {
      water: { warning: 70, critical: 85 },
      temperature: { warning: 35, critical: 40 },
      humidity: { warning: 85, critical: 95 },
      light: { warning: 100, critical: 50 }
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
      document.getElementById('water-raw').textContent = data.water_raw || 0;
      
      document.getElementById('temp-value').textContent = data.temperature || data.temp || 0;
      document.getElementById('humidity-value').textContent = data.humidity || 0;
      document.getElementById('rain-status').textContent = data.rainStatus || data.rain_status || '--';
      document.getElementById('light-value').textContent = data.lightValue || data.light_raw || 0;
      document.getElementById('gate-status').textContent = data.gateStatus || data.gate_status || 'UNKNOWN';
      
      // Update system mode
      document.getElementById('sys-mode').textContent = data.mode || 'ONLINE';
      
      // Check for alerts and apply enhanced styling
      checkSensorAlerts({
        waterLevel: data.waterLevel || data.water_percent || 0,
        temperature: data.temperature || data.temp || 0,
        humidity: data.humidity || 0,
        rainStatus: data.rainStatus || data.rain_status || '',
        lightValue: data.lightValue || data.light_raw || 0,
        gateStatus: data.gateStatus || data.gate_status || 'UNKNOWN'
      });
    }

    // Gate control with ESP32 endpoints
    function toggleGate(action) {
      logActivity('GATE_CONTROL', { action: action });
      
      fetch('/gate-control', {
        method: 'POST',
        headers: { 'Content-Type': 'application/x-www-form-urlencoded' },
        body: `action=${action}`
      })
      .then(response => response.text())
      .then(data => {
        if (data.includes('success')) {
          document.getElementById('gate-status').textContent = action;
          logActivity('GATE_CONTROL_SUCCESS', { action: action });
        } else {
          alert('Gate control failed');
        }
      })
      .catch(error => {
        alert('Gate control error: ' + error.message);
      });
    }
    
    // Real-time sensor updates via WebSocket or polling
    function updateSensorData() {
      fetch('/sensor-current')
        .then(response => response.json())
        .then(data => {
          document.getElementById('water-value').textContent = data.waterLevel + '%';
          document.getElementById('water-fill').style.height = data.waterLevel + '%';
          document.getElementById('temp-value').textContent = data.temperature;
          document.getElementById('humidity-value').textContent = data.humidity;
          document.getElementById('rain-status').textContent = data.rainStatus;
          document.getElementById('light-value').textContent = data.lightValue;
          document.getElementById('gate-status').textContent = data.gateStatus;
          
          // Update system mode
          document.getElementById('sys-mode').textContent = 'ONLINE';
        })
        .catch(error => {
          document.getElementById('sys-mode').textContent = 'ERROR';
        });
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
