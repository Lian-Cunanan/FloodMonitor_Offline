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

  <div class="grid-container">
    <div style="grid-column: 1 / -1; text-align: right;">
        <button class="qr-btn" onclick="toggleQR()">&#128241; WiFi Info</button>
        <button class="qr-btn" onclick="downloadData()">&#128190; Download Data</button>
        <button class="qr-btn" onclick="viewDatabase()">&#128248; System Status</button>
        <button class="qr-btn" onclick="factoryReset()">&#128295; Factory Reset</button>
    </div>

    <div class="card card-water">
      <h2>Water Level</h2>
      <div class="gauge">
        <div class="gauge-body">
          <div class="gauge-fill" id="water-fill"></div>
          <div class="gauge-cover" id="water-value">0%</div>
        </div>
      </div>
      <p>Raw: <span id="water-raw">0</span></p>
    </div>

    <div class="card card-gate">
      <h2>Gate Status</h2>
      <h3 id="gate-status">CLOSED</h3>
      <div class="maintenance-controls">
        <button onclick="toggleGate('OPEN')">Open (Maint)</button>
        <button onclick="toggleGate('CLOSE')">Close (Maint)</button>
      </div>
    </div>

    <div class="card card-env">
      <h2>Environment</h2>
      <p>Temp: <span id="temp-value">0</span>&deg;C</p>
      <p>Hum: <span id="humidity-value">0</span>%</p>
      <p>Rain: <span id="rain-status">--</span></p>
      <p>Light: <span id="light-value">0</span></p>
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
    let currentUser = 'admin'; // Simplified for ESP32
    
    // Simplified logging for ESP32
    function logActivity(action, details = {}) {
      fetch('/log', {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({
          action: action,
          details: JSON.stringify(details),
          user: currentUser,
          timestamp: Date.now()
        })
      }).catch(() => {}); // Fail silently
    }

    // Simplified authentication check
    fetch('/auth-check')
      .then(response => {
        if (!response.ok) {
          window.location.href = '/login.html';
        } else {
          return response.text();
        }
      })
      .then(data => {
        if (data && data.includes('authenticated')) {
          document.getElementById('current-user').textContent = currentUser;
          logActivity('DASHBOARD_ACCESS');
        }
      })
      .catch(() => {
        // If auth check fails, assume we're in development mode
        document.getElementById('current-user').textContent = 'Development Mode';
      });

    function logout() {
      logActivity('LOGOUT');
      fetch('/logout', { method: 'POST' })
        .then(() => {
          window.location.href = '/login.html';
        });
    }

    function downloadData() {
      logActivity('DATA_DOWNLOAD');
      
      fetch('/sensor-data')
        .then(response => response.blob())
        .then(blob => {
          const url = window.URL.createObjectURL(blob);
          const a = document.createElement('a');
          a.href = url;
          a.download = 'flood_data_' + new Date().toISOString().slice(0,10) + '.json';
          document.body.appendChild(a);
          a.click();
          document.body.removeChild(a);
          window.URL.revokeObjectURL(url);
        })
        .catch(error => {
          alert('Download failed: ' + error.message);
        });
    }
    
    function viewDatabase() {
      logActivity('DATABASE_VIEW');
      
      fetch('/storage-status')
        .then(response => response.json())
        .then(data => {
          const content = document.getElementById('db-status-content');
          content.innerHTML = `
            <h4>ESP32 Storage Status</h4>
            <ul>
              <li><strong>Storage Type:</strong> ${data.storage_type || 'LittleFS'}</li>
              <li><strong>Total Space:</strong> ${(data.total_bytes/1024).toFixed(1)} KB</li>
              <li><strong>Used Space:</strong> ${(data.used_bytes/1024).toFixed(1)} KB</li>
              <li><strong>Free Space:</strong> ${(data.free_bytes/1024).toFixed(1)} KB</li>
              <li><strong>Usage:</strong> ${data.usage_percent.toFixed(1)}%</li>
            </ul>
            
            <h4>Database Records</h4>
            <ul>
              <li><strong>Users:</strong> ${data.user_count || 0}</li>
              <li><strong>Sensor Data:</strong> ${data.sensor_count || 0}</li>
              <li><strong>Activities:</strong> ${data.activity_count || 0}</li>
            </ul>
            
            <h4>ESP32 System Info</h4>
            <ul>
              <li><strong>Chip:</strong> ${data.chip_model || 'ESP32'}</li>
              <li><strong>CPU Frequency:</strong> ${data.cpu_freq || 240} MHz</li>
              <li><strong>Free Heap:</strong> ${(data.free_heap/1024).toFixed(1)} KB</li>
              <li><strong>Uptime:</strong> ${(data.uptime/60000).toFixed(1)} minutes</li>
            </ul>
          `;
          
          document.getElementById('db-modal').style.display = 'block';
        })
        .catch(error => {
          alert('Failed to get system status');
        });
    }
    
    function factoryReset() {
      if (confirm('⚠️ This will delete all data and reset to defaults. Continue?')) {
        logActivity('FACTORY_RESET_INITIATED');
        
        fetch('/factory-reset', { method: 'POST' })
          .then(response => {
            if (response.ok) {
              alert('✅ Factory reset completed! Device will restart.');
              setTimeout(() => {
                window.location.href = '/login.html';
              }, 2000);
            } else {
              alert('❌ Factory reset failed');
            }
          })
          .catch(error => {
            alert('❌ Factory reset error: ' + error.message);
          });
      }
    }
    
    function toggleDatabase() {
      const modal = document.getElementById('db-modal');
      modal.style.display = modal.style.display === 'block' ? 'none' : 'block';
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
      const ws = new WebSocket('ws://' + window.location.host + '/ws');
      
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
  </script>

</body>
</html>
)rawliteral";
