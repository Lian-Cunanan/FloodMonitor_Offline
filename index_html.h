#pragma once

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>IoT Flood Monitoring System</title>
    <link rel="stylesheet" href="/style.css">
</head>
<body>
    <nav class="navbar">
        <div class="nav-brand">
            <span class="nav-icon">🌊</span>
            <h1>Flood Monitor Pro</h1>
        </div>
        <div class="nav-status">
            <span class="status-indicator">
                <div class="status-dot" id="ws-status"></div>
                <span class="status-text" id="status-text">Connecting...</span>
            </span>
            <div class="timestamp" id="last-update">Last update: --</div>
            <div class="nav-actions">
                <span class="user-greeting">Welcome, <span id="user-name">User</span></span>
                <button class="logout-btn" id="logout-btn" title="Logout">
                    <span class="logout-icon">🚪</span>
                    <span class="logout-text">Logout</span>
                </button>
            </div>
        </div>
    </nav>

    <main class="dashboard">
        <section class="metrics-grid">
            <!-- Water Level Monitoring -->
            <article class="metric-card priority-high">
                <header class="card-header">
                    <div class="card-icon water-icon">💧</div>
                    <div class="card-title">
                        <h3>Water Level</h3>
                        <span class="card-subtitle">Primary Sensor</span>
                    </div>
                </header>
                <div class="gauge-container">
                    <div class="gauge">
                        <div class="gauge-track">
                            <div class="gauge-fill" id="water-fill"></div>
                        </div>
                        <div class="gauge-center">
                            <span class="gauge-value" id="water-percent">0</span>
                            <span class="gauge-unit">%</span>
                        </div>
                    </div>
                </div>
                <div class="metric-details">
                    <div class="detail-item">
                        <span class="label">Current</span>
                        <span class="value" id="water-raw">0</span>
                    </div>
                    <div class="detail-item">
                        <span class="label">Alert Level</span>
                        <span class="value alert-level">3.0m</span>
                    </div>
                </div>
            </article>

            <!-- Environmental Data -->
            <article class="metric-card">
                <header class="card-header">
                    <div class="card-icon env-icon">🌡️</div>
                    <div class="card-title">
                        <h3>Environment</h3>
                        <span class="card-subtitle">Sensor Data</span>
                    </div>
                </header>
                <div class="env-metrics">
                    <div class="env-item">
                        <div class="env-label">Temperature</div>
                        <div class="env-value"><span id="temp-value">0</span>°C</div>
                        <div class="env-trend neutral" id="temp-trend">--</div>
                    </div>
                    <div class="env-item">
                        <div class="env-label">Humidity</div>
                        <div class="env-value"><span id="humidity-value">0</span>%</div>
                        <div class="env-trend neutral" id="humidity-trend">--</div>
                    </div>
                    <div class="env-item">
                        <div class="env-label">Light Level</div>
                        <div class="env-value"><span id="light-value">0</span> lux</div>
                        <div class="env-trend neutral" id="light-trend">--</div>
                    </div>
                </div>
            </article>

            <!-- Gate Control -->
            <article class="metric-card control-card">
                <header class="card-header">
                    <div class="card-icon gate-icon">🚪</div>
                    <div class="card-title">
                        <h3>Flood Gate</h3>
                        <span class="card-subtitle">Control System</span>
                    </div>
                </header>
                <div class="gate-status">
                    <div class="status-display" id="gate-display">
                        <div class="status-icon" id="gate-icon">🔴</div>
                        <span class="status-label" id="gate-status">CLOSED</span>
                    </div>
                    <button class="control-btn primary" id="gate-toggle">
                        <span>Toggle Gate</span>
                    </button>
                </div>
                <div class="gate-info">
                    <small>Auto-mode: Enabled</small>
                </div>
            </article>

            <!-- Rain Detection -->
            <article class="metric-card">
                <header class="card-header">
                    <div class="card-icon rain-icon">🌧️</div>
                    <div class="card-title">
                        <h3>Rain Sensor</h3>
                        <span class="card-subtitle">Weather Monitor</span>
                    </div>
                </header>
                <div class="rain-status">
                    <div class="rain-indicator" id="rain-indicator">
                        <div class="rain-visual"></div>
                        <span id="rain-status">No Rain Detected</span>
                    </div>
                    <div class="rain-details">
                        <div class="detail-item">
                            <span class="label">Intensity</span>
                            <span class="value"><span id="rain-value">0</span> mm/h</span>
                        </div>
                        <div class="detail-item">
                            <span class="label">Raw Value</span>
                            <span class="value" id="rain-raw">0</span>
                        </div>
                    </div>
                </div>
            </article>
        </section>

        <!-- Alert Panel -->
        <section class="alerts-panel">
            <h2>System Alerts</h2>
            <div class="alert-item info" id="system-alert">
                <div class="alert-icon">ℹ️</div>
                <div class="alert-content">
                    <div class="alert-title">System Status</div>
                    <div class="alert-message" id="alert-message">Initializing system...</div>
                </div>
                <div class="alert-time" id="alert-time">--</div>
            </div>
        </section>
    </main>

    <script>
// Dashboard functionality
let currentGateStatus = 'CLOSED';

document.addEventListener('DOMContentLoaded', function() {
    console.log('🔧 Dashboard loaded');
    
    // Initialize dashboard
    initDashboard();
    setupLogout();
    setupGateToggle();
    
    // Start data updates
    startDataFetching();
});

function initDashboard() {
    updateConnectionStatus(true);
    loadUserInfo();
}

async function loadUserInfo() {
    try {
        // For now, just set a default user name
        document.getElementById('user-name').textContent = 'Admin';
    } catch (error) {
        console.error('Error loading user info:', error);
    }
}

function setupLogout() {
    const logoutBtn = document.getElementById('logout-btn');
    if (logoutBtn) {
        logoutBtn.addEventListener('click', async function() {
            if (confirm('Are you sure you want to logout?')) {
                try {
                    window.location.href = '/login';
                } catch (error) {
                    console.log('Logout failed, redirecting anyway...');
                    window.location.href = '/login';
                }
            }
        });
    }
}

function setupGateToggle() {
    const gateToggle = document.getElementById('gate-toggle');
    if (gateToggle) {
        gateToggle.addEventListener('click', function() {
            toggleGate();
        });
    }
}

function toggleGate() {
    // Toggle the gate status
    currentGateStatus = currentGateStatus === 'OPEN' ? 'CLOSED' : 'OPEN';
    
    // Update UI immediately
    updateGateDisplay(currentGateStatus);
    
    console.log(`🚪 Gate toggled to: ${currentGateStatus}`);
    
    // You can add server communication here later
    // fetch('/gate/toggle', { method: 'POST' });
}

function updateGateDisplay(status) {
    const gateDisplay = document.getElementById('gate-display');
    const gateIcon = document.getElementById('gate-icon');
    const gateStatusEl = document.getElementById('gate-status');
    
    if (gateDisplay && gateIcon && gateStatusEl) {
        if (status === 'OPEN') {
            gateDisplay.classList.add('open');
            gateDisplay.classList.remove('closed');
            gateIcon.textContent = '🟢';
            gateStatusEl.textContent = 'OPEN';
        } else {
            gateDisplay.classList.add('closed');
            gateDisplay.classList.remove('open');
            gateIcon.textContent = '🔴';
            gateStatusEl.textContent = 'CLOSED';
        }
    }
}

function updateConnectionStatus(connected) {
    const statusDot = document.getElementById('ws-status');
    const statusText = document.getElementById('status-text');
    
    if (statusDot && statusText) {
        if (connected) {
            statusDot.classList.add('connected');
            statusText.textContent = 'Online';
        } else {
            statusDot.classList.remove('connected');
            statusText.textContent = 'Offline';
        }
    }
}

function startDataFetching() {
    // Generate mock data every 2 seconds
    setInterval(updateMockData, 2000);
    updateMockData(); // Initial update
}

function updateMockData() {
    // Update water level
    const waterPercent = Math.floor(Math.random() * 60) + 30; // 30-90%
    const rotation = (waterPercent / 100) * 180;
    
    const waterFill = document.getElementById('water-fill');
    const waterPercentEl = document.getElementById('water-percent');
    const waterRaw = document.getElementById('water-raw');
    
    if (waterFill) waterFill.style.transform = `rotate(${rotation}deg)`;
    if (waterPercentEl) waterPercentEl.textContent = waterPercent;
    if (waterRaw) waterRaw.textContent = `${(Math.random() * 1.5 + 1.5).toFixed(1)}m`;
    
    // Update environmental data
    const temp = document.getElementById('temp-value');
    const humidity = document.getElementById('humidity-value');
    const light = document.getElementById('light-value');
    
    if (temp) temp.textContent = Math.floor(Math.random() * 8) + 25; // 25-32°C
    if (humidity) humidity.textContent = Math.floor(Math.random() * 30) + 50; // 50-80%
    if (light) light.textContent = Math.floor(Math.random() * 600) + 200; // 200-800 lux
    
    // Update rain sensor
    const rainStatus = document.getElementById('rain-status');
    const rainValue = document.getElementById('rain-value');
    const rainRaw = document.getElementById('rain-raw');
    const rainIndicator = document.getElementById('rain-indicator');
    
    const isRaining = Math.random() > 0.7;
    
    if (rainStatus) rainStatus.textContent = isRaining ? 'Rain Detected' : 'No Rain Detected';
    if (rainValue) rainValue.textContent = isRaining ? Math.floor(Math.random() * 10) + 1 : 0;
    if (rainRaw) rainRaw.textContent = Math.floor(Math.random() * 1024);
    
    if (rainIndicator) {
        if (isRaining) {
            rainIndicator.classList.add('raining');
            rainIndicator.classList.remove('no-rain');
        } else {
            rainIndicator.classList.add('no-rain');
            rainIndicator.classList.remove('raining');
        }
    }
    
    // Update timestamp
    const lastUpdate = document.getElementById('last-update');
    if (lastUpdate) {
        lastUpdate.textContent = `Last update: ${new Date().toLocaleTimeString()}`;
    }
    
    // Update alert message
    const alertMessage = document.getElementById('alert-message');
    const alertTime = document.getElementById('alert-time');
    
    if (alertMessage) alertMessage.textContent = 'All sensors operating normally';
    if (alertTime) alertTime.textContent = 'Just now';
}
    </script>
</body>
</html>
)rawliteral";