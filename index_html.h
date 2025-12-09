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
    </div>

    <div style="display: flex; align-items: center; gap: 12px;">
      <button class="logout-btn" onclick="logout()">Logout</button>
      <div class="status-dot" id="ws-status"></div>
    </div>
  </div>

  <div class="grid-container">
    <div style="grid-column: 1 / -1; text-align: right;">
        <button class="qr-btn" onclick="toggleQR()">&#128241; WiFi Info</button>
        <button class="qr-btn" onclick="viewHistory()">&#128195; View History</button>
        <button class="qr-btn" onclick="generatePDF()">&#128196; Download PDF Report</button>
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
    <div class="modal-content" style="max-width:300px;">
      <span class="close-btn" onclick="closeAllModals()">&times;</span>
      <h3>Connect to Network</h3>
      <p><strong>SSID:</strong> FloodMonitor_Network</p>
      <p><strong>Password:</strong> 12345678</p>
    </div>
  </div>

  <div id="db-modal" class="modal">
    <div class="modal-content" style="max-width:300px;">
      <span class="close-btn" onclick="closeAllModals()">&times;</span>
      <h3>System Status</h3>
      <div id="db-status-content">Loading...</div>
    </div>
  </div>

  <div id="history-modal" class="modal">
    <div class="modal-content">
      <span class="close-btn" onclick="closeAllModals()">&times;</span>
      <div style="display:flex; justify-content:space-between; align-items:center;">
        <h3>Recorded Data</h3>
        <button onclick="generatePDF()" class="qr-btn" style="font-size:12px; padding:8px;">Download PDF</button>
      </div>
      <div class="table-responsive">
        <table class="history-table">
          <thead>
            <tr><th>Time</th><th>Water Lvl</th><th>Gate</th><th>Temp</th><th>Rain</th></tr>
          </thead>
          <tbody id="history-table-body"></tbody>
        </table>
      </div>
      <p style="font-size:12px; color:#777; margin-top:10px;">Showing last 500 records.</p>
    </div>
  </div>

  <div id="alert-modal" class="modal" style="background-color: rgba(50,0,0,0.8); z-index: 200;">
    <div class="alert-modal-content">
      <div class="alert-title">⚠️ FLOOD ALERT</div>
      <div class="alert-desc">Water Level is Critical!</div>
      <div class="alert-value" id="alert-lvl">0%</div>
      <p>The Flood Gate has been automatically opened.</p>
      <button class="alert-dismiss-btn" onclick="dismissAlert()">ACKNOWLEDGE</button>
    </div>
  </div>

  <script src="/script.js"></script>
  <script>
    if (document.cookie.indexOf('ESPSESSIONID=1') === -1) {
      window.location.href = '/login';
    }

    // --- ALERT LOGIC ---
    let alertDismissed = false;
    const CRITICAL_LEVEL = 70; 
    const SAFE_LEVEL = 65;     

    function checkFloodAlert(waterPercent) {
      const modal = document.getElementById('alert-modal');
      if (waterPercent >= CRITICAL_LEVEL && !alertDismissed) {
        document.getElementById('alert-lvl').innerText = waterPercent.toFixed(1) + '%';
        modal.style.display = 'block';
      }
      if (waterPercent < SAFE_LEVEL) {
        alertDismissed = false;
        modal.style.display = 'none'; 
      }
    }

    function dismissAlert() {
      document.getElementById('alert-modal').style.display = 'none';
      alertDismissed = true; 
    }

    function formatUptime(ms) {
      const seconds = Math.floor((ms / 1000) % 60);
      const minutes = Math.floor((ms / (1000 * 60)) % 60);
      const hours = Math.floor((ms / (1000 * 60 * 60)) % 24);
      const days = Math.floor(ms / (1000 * 60 * 60 * 24));
      let str = "";
      if (days > 0) str += days + "d ";
      if (hours > 0 || days > 0) str += hours + "h ";
      str += minutes + "m " + seconds + "s";
      return str;
    }

    function closeAllModals() {
      document.getElementById('qr-modal').style.display = 'none';
      document.getElementById('db-modal').style.display = 'none';
      document.getElementById('history-modal').style.display = 'none';
    }
    
    window.onclick = function(event) {
      if (event.target.classList.contains('modal')) { closeAllModals(); }
    }

    function toggleGate(action) {
      fetch('/gate?state=' + action)
      .then(res => {
         if(res.status == 403) alert("Enable Maintenance Mode first!");
         else if(res.status != 200) alert("Error controlling gate");
      });
    }

    // --- VIEW HISTORY (UPDATED FOR REAL TIME) ---
    async function viewHistory() {
        const modal = document.getElementById('history-modal');
        const tbody = document.getElementById('history-table-body');
        
        tbody.innerHTML = '<tr><td colspan="5" style="text-align:center;">Loading Data...</td></tr>';
        modal.style.display = 'block';

        try {
            const dataRes = await fetch('/sensor-data');
            const records = await dataRes.json();
            
            tbody.innerHTML = '';
            if (records.length === 0) {
              tbody.innerHTML = '<tr><td colspan="5" style="text-align:center;">No records found</td></tr>';
              return;
            }

            records.reverse().forEach(rec => {
                // FIXED: Use Unix Timestamp directly
                const recordDate = new Date(rec.timestamp * 1000);
                const timeStr = recordDate.toLocaleTimeString([], {hour: '2-digit', minute:'2-digit'});
                const dateStr = recordDate.toLocaleDateString();
                const gateClass = rec.gateStatus === 'OPEN' ? 'badge-open' : 'badge-closed';
                const rainText = rec.rainStatus.replace('_', ' ');
                const rainStyle = rec.rainStatus.includes('NO') ? 'color:#555;' : 'color:#0072ff; font-weight:bold;';

                const row = `<tr><td><div style="font-weight:bold;">${timeStr}</div><div style="font-size:11px; color:#888;">${dateStr}</div></td>
                        <td>${rec.waterLevel.toFixed(1)}%</td><td><span class="status-badge ${gateClass}">${rec.gateStatus}</span></td>
                        <td>${rec.temperature.toFixed(1)}&deg;C</td><td style="${rainStyle}">${rainText}</td></tr>`;
                tbody.insertAdjacentHTML('beforeend', row);
            });
        } catch (err) { tbody.innerHTML = `<tr><td colspan="5" style="color:red; text-align:center;">Error: ${err.message}</td></tr>`; }
    }

    // --- GENERATE PDF REPORT (UPDATED FOR REAL TIME) ---
    async function generatePDF() {
        const btn = document.querySelector('button[onclick="generatePDF()"]');
        const originalText = btn ? btn.innerHTML : "Download PDF";
        if(btn) btn.innerHTML = "Generating...";

        try {
            const [dataRes, statusRes] = await Promise.all([ fetch('/sensor-data'), fetch('/storage-status') ]);
            const records = await dataRes.json();
            const status = await statusRes.json();

            const printWin = window.open('', '_blank');
            if(!printWin) { alert("Please allow popups to download the PDF."); return; }

            printWin.document.write(`
              <html>
              <head>
                <title>Flood Monitoring Report</title>
                <style>
                  body { font-family: 'Helvetica', 'Arial', sans-serif; padding: 40px; color: #333; }
                  .header { text-align: center; margin-bottom: 30px; border-bottom: 2px solid #0072ff; padding-bottom: 20px; }
                  h1 { color: #0072ff; margin: 0; font-size: 24px; }
                  .meta { font-size: 12px; color: #666; margin-top: 5px; }
                  .summary { background: #f4f6f9; padding: 15px; border-radius: 8px; margin-bottom: 20px; display: flex; justify-content: space-between; }
                  table { width: 100%; border-collapse: collapse; font-size: 12px; }
                  th { background: #0072ff; color: white; padding: 8px; text-align: left; }
                  td { padding: 8px; border-bottom: 1px solid #ddd; }
                  tr:nth-child(even) { background: #f9f9f9; }
                  .footer { margin-top: 30px; font-size: 10px; text-align: center; color: #888; border-top: 1px solid #eee; padding-top: 10px; }
                </style>
              </head>
              <body>
                <div class="header">
                  <h1>Flood Monitoring System Report</h1>
                  <div class="meta">Generated on: ${new Date().toLocaleString()}</div>
                </div>

                <div class="summary">
                  <div><strong>Total Records:</strong> ${records.length}</div>
                  <div><strong>Device Uptime:</strong> ${formatUptime(status.uptime)}</div>
                  <div><strong>Storage Used:</strong> ${(status.used_bytes/1024).toFixed(1)} KB</div>
                </div>

                <table>
                  <thead>
                    <tr><th>Date</th><th>Time</th><th>Water Level</th><th>Gate Status</th><th>Temp</th><th>Rain</th></tr>
                  </thead>
                  <tbody>
            `);

            records.reverse().forEach(rec => {
                // FIXED: Use Unix Timestamp directly
                const d = new Date(rec.timestamp * 1000);
                const rainText = rec.rainStatus.replace('_', ' ');
                printWin.document.write(`
                  <tr>
                    <td>${d.toLocaleDateString()}</td>
                    <td>${d.toLocaleTimeString()}</td>
                    <td>${rec.waterLevel.toFixed(1)}%</td>
                    <td>${rec.gateStatus}</td>
                    <td>${rec.temperature.toFixed(1)}&deg;C</td>
                    <td>${rainText}</td>
                  </tr>
                `);
            });

            printWin.document.write(`
                  </tbody>
                </table>
                <div class="footer">FloodMonitor_Offline v2.0 | Auto-Generated Report</div>
                <script>
                  window.onload = function() { window.print(); };
                <\/script>
              </body>
              </html>
            `);
            printWin.document.close();

        } catch (err) {
            alert("Error generating report: " + err.message);
        } finally {
            if(btn) btn.innerHTML = originalText;
        }
    }
    
    function viewDatabase() {
      fetch('/storage-status').then(res => res.json()).then(data => {
          document.getElementById('db-status-content').innerHTML = `
            <div style="text-align:left; font-size:0.9em;">
            <p><strong>Storage:</strong> ${data.storage_type}</p>
            <p><strong>Used:</strong> ${(data.used_bytes/1024).toFixed(1)} KB / ${(data.total_bytes/1024).toFixed(1)} KB</p>
            <hr>
            <p><strong>Users Registered:</strong> ${data.user_count}</p>
            <p><strong>Records Stored:</strong> ${data.sensor_count}</p>
            <p><strong>System Uptime:</strong> <span style="color:#0072ff; font-weight:bold;">${formatUptime(data.uptime)}</span></p>
            </div>`;
          document.getElementById('db-modal').style.display = 'block';
      });
    }

    function factoryReset() {
      if (confirm('Delete ALL data? (Recommended for Time Sync Fix)')) {
        fetch('/factory-reset', { method: 'POST' }).then(res => { if(res.ok) window.location.href='/login'; });
      }
    }
    function toggleQR() { document.getElementById('qr-modal').style.display = 'block'; }
    function logout() { fetch('/auth/logout', { method: 'POST' }).then(() => { window.location.href = '/login'; }); }

    // --- NEW: AUTO-SYNC TIME ON LOAD ---
    window.addEventListener('load', function() {
        // Send current Browser Time (Seconds) to ESP32
        const nowSec = Math.floor(Date.now() / 1000);
        fetch('/sync-time?t=' + nowSec);
    });

  </script>
</body>
</html>
)rawliteral";