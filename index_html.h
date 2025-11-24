#pragma once

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>IoT Flood Monitoring System</title>
    <link rel="stylesheet" href="/style.css">
    <link href="https://fonts.googleapis.com/css2?family=Inter:wght@300;400;500;600;700&display=swap" rel="stylesheet">
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

    <script src="/script.js"></script>
</body>
</html>
)rawliteral";