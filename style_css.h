#pragma once

const char style_css[] PROGMEM = R"rawliteral(
:root {
  --primary-color: #2563eb;
  --primary-light: #3b82f6;
  --primary-dark: #1d4ed8;
  --secondary-color: #64748b;
  --success-color: #10b981;
  --warning-color: #f59e0b;
  --danger-color: #ef4444;
  --info-color: #06b6d4;
  --bg-primary: #f8fafc;
  --bg-card: #ffffff;
  --bg-secondary: #f1f5f9;
  --text-primary: #0f172a;
  --text-secondary: #64748b;
  --text-muted: #94a3b8;
  --spacing-xs: 0.25rem;
  --spacing-sm: 0.5rem;
  --spacing-md: 1rem;
  --spacing-lg: 1.5rem;
  --spacing-xl: 2rem;
  --spacing-2xl: 3rem;
  --radius-sm: 0.25rem;
  --radius-md: 0.5rem;
  --radius-lg: 0.75rem;
  --radius-xl: 1rem;
  --shadow-sm: 0 1px 2px 0 rgb(0 0 0 / 0.05);
  --shadow-md: 0 4px 6px -1px rgb(0 0 0 / 0.1), 0 2px 4px -2px rgb(0 0 0 / 0.1);
  --shadow-lg: 0 10px 15px -3px rgb(0 0 0 / 0.1), 0 4px 6px -4px rgb(0 0 0 / 0.1);
}

* { margin: 0; padding: 0; box-sizing: border-box; }

body {
  font-family: 'Inter', -apple-system, BlinkMacSystemFont, 'Segoe UI', sans-serif;
  background-color: var(--bg-primary);
  color: var(--text-primary);
  line-height: 1.6;
  font-size: 14px;
}

.navbar {
  background: var(--bg-card);
  padding: var(--spacing-lg) var(--spacing-xl);
  box-shadow: var(--shadow-sm);
  display: flex;
  justify-content: space-between;
  align-items: center;
  border-bottom: 1px solid #e2e8f0;
  position: sticky;
  top: 0;
  z-index: 100;
}

.nav-brand {
  display: flex;
  align-items: center;
  gap: var(--spacing-md);
}

.nav-icon {
  font-size: 2rem;
  animation: float 3s ease-in-out infinite;
}

@keyframes float {
  0%, 100% { transform: translateY(0px); }
  50% { transform: translateY(-5px); }
}

.navbar h1 {
  font-size: 1.5rem;
  font-weight: 600;
  color: var(--primary-color);
  margin: 0;
}

.nav-status {
  display: flex;
  align-items: center;
  gap: var(--spacing-lg);
}

.status-indicator {
  display: flex;
  align-items: center;
  gap: var(--spacing-sm);
}

.status-dot {
  width: 8px;
  height: 8px;
  border-radius: 50%;
  background-color: var(--danger-color);
  animation: pulse 2s infinite;
}

.status-dot.connected {
  background-color: var(--success-color);
}

@keyframes pulse {
  0% { transform: scale(1); opacity: 1; }
  50% { transform: scale(1.2); opacity: 0.7; }
  100% { transform: scale(1); opacity: 1; }
}

.status-text {
  font-weight: 500;
  color: var(--text-secondary);
}

.timestamp {
  font-size: 0.75rem;
  color: var(--text-muted);
}

.dashboard {
  padding: var(--spacing-xl);
  max-width: 1400px;
  margin: 0 auto;
}

.metrics-grid {
  display: grid;
  grid-template-columns: repeat(auto-fit, minmax(320px, 1fr));
  gap: var(--spacing-xl);
  margin-bottom: var(--spacing-2xl);
}

.metric-card {
  background: var(--bg-card);
  border-radius: var(--radius-xl);
  padding: var(--spacing-xl);
  box-shadow: var(--shadow-md);
  border: 1px solid #e2e8f0;
  transition: all 0.3s ease;
  position: relative;
  overflow: hidden;
}

.metric-card::before {
  content: '';
  position: absolute;
  top: 0;
  left: 0;
  right: 0;
  height: 3px;
  background: linear-gradient(90deg, var(--primary-color), var(--info-color));
  opacity: 0;
  transition: opacity 0.3s ease;
}

.metric-card:hover {
  transform: translateY(-4px);
  box-shadow: var(--shadow-lg);
}

.metric-card:hover::before { opacity: 1; }
.metric-card.priority-high { border-left: 4px solid var(--primary-color); }

.card-header {
  display: flex;
  align-items: flex-start;
  gap: var(--spacing-md);
  margin-bottom: var(--spacing-lg);
}

.card-icon {
  font-size: 1.5rem;
  width: 48px;
  height: 48px;
  display: flex;
  align-items: center;
  justify-content: center;
  border-radius: var(--radius-lg);
  background: var(--bg-secondary);
  transition: transform 0.2s ease;
}

.metric-card:hover .card-icon { transform: scale(1.1); }
.water-icon { background: linear-gradient(135deg, #dbeafe, #bfdbfe); }
.env-icon { background: linear-gradient(135deg, #dcfce7, #bbf7d0); }
.gate-icon { background: linear-gradient(135deg, #fef3c7, #fed7aa); }
.rain-icon { background: linear-gradient(135deg, #e0f2fe, #bae6fd); }

.card-title h3 {
  font-size: 1.125rem;
  font-weight: 600;
  color: var(--text-primary);
  margin-bottom: var(--spacing-xs);
}

.card-subtitle {
  font-size: 0.75rem;
  color: var(--text-muted);
  text-transform: uppercase;
  letter-spacing: 0.5px;
}

.gauge-container {
  display: flex;
  justify-content: center;
  margin: var(--spacing-lg) 0;
}

.gauge {
  position: relative;
  width: 160px;
  height: 80px;
}

.gauge-track {
  width: 100%;
  height: 100%;
  border: 8px solid #e2e8f0;
  border-bottom: none;
  border-radius: 80px 80px 0 0;
  position: relative;
  overflow: hidden;
}

.gauge-fill {
  position: absolute;
  top: 0;
  left: 0;
  width: 100%;
  height: 100%;
  background: linear-gradient(90deg, var(--success-color) 0%, var(--warning-color) 50%, var(--danger-color) 100%);
  border-radius: 80px 80px 0 0;
  transform-origin: center bottom;
  transition: transform 0.6s cubic-bezier(0.4, 0, 0.2, 1);
}

.gauge-center {
  position: absolute;
  bottom: -10px;
  left: 50%;
  transform: translateX(-50%);
  text-align: center;
  background: var(--bg-card);
  padding: var(--spacing-sm);
  border-radius: var(--radius-md);
  box-shadow: var(--shadow-sm);
}

.gauge-value {
  font-size: 1.875rem;
  font-weight: 700;
  color: var(--primary-color);
}

.gauge-unit {
  font-size: 0.875rem;
  color: var(--text-secondary);
  margin-left: 2px;
}

.metric-details {
  display: flex;
  justify-content: space-between;
  padding-top: var(--spacing-md);
  border-top: 1px solid #e2e8f0;
  margin-top: var(--spacing-md);
}

.detail-item {
  text-align: center;
  flex: 1;
}

.detail-item .label {
  display: block;
  font-size: 0.75rem;
  color: var(--text-muted);
  margin-bottom: var(--spacing-xs);
  text-transform: uppercase;
  letter-spacing: 0.3px;
}

.detail-item .value {
  font-weight: 600;
  color: var(--text-primary);
  font-size: 0.95rem;
}

.alert-level { color: var(--warning-color); }

.env-metrics {
  display: flex;
  flex-direction: column;
  gap: var(--spacing-md);
}

.env-item {
  display: flex;
  justify-content: space-between;
  align-items: center;
  padding: var(--spacing-md);
  background: var(--bg-secondary);
  border-radius: var(--radius-md);
  transition: all 0.2s ease;
}

.env-item:hover {
  background: #e2e8f0;
  transform: translateX(4px);
}

.env-label {
  font-size: 0.875rem;
  color: var(--text-secondary);
  font-weight: 500;
}

.env-value {
  font-weight: 600;
  font-size: 1.125rem;
  color: var(--text-primary);
}

.env-trend {
  font-size: 0.75rem;
  padding: 2px 8px;
  border-radius: var(--radius-sm);
  font-weight: 500;
}

.env-trend.positive { background: #dcfce7; color: var(--success-color); }
.env-trend.negative { background: #fee2e2; color: var(--danger-color); }
.env-trend.neutral { background: #f1f5f9; color: var(--text-muted); }

.gate-status {
  text-align: center;
  margin-bottom: var(--spacing-md);
}

.status-display {
  display: flex;
  align-items: center;
  justify-content: center;
  gap: var(--spacing-sm);
  margin-bottom: var(--spacing-lg);
  padding: var(--spacing-md);
  background: var(--bg-secondary);
  border-radius: var(--radius-lg);
}

.status-display.open .status-label { color: var(--success-color); }
.status-display.closed .status-label { color: var(--danger-color); }

.status-label {
  font-size: 1.25rem;
  font-weight: 600;
}

.control-btn {
  background: linear-gradient(135deg, var(--primary-color), var(--primary-dark));
  color: white;
  border: none;
  padding: var(--spacing-md) var(--spacing-xl);
  border-radius: var(--radius-lg);
  font-weight: 500;
  cursor: pointer;
  transition: all 0.2s ease;
  box-shadow: var(--shadow-sm);
}

.control-btn:hover {
  transform: translateY(-1px);
  box-shadow: var(--shadow-md);
}

.control-btn:active { transform: translateY(0); }

.gate-info {
  text-align: center;
  margin-top: var(--spacing-md);
}

.gate-info small {
  color: var(--text-muted);
  font-size: 0.75rem;
}

.rain-status { text-align: center; }

.rain-indicator {
  margin-bottom: var(--spacing-lg);
  padding: var(--spacing-lg);
  background: var(--bg-secondary);
  border-radius: var(--radius-lg);
}

.rain-visual {
  width: 40px;
  height: 40px;
  margin: 0 auto var(--spacing-md);
  border-radius: 50%;
  background: #e2e8f0;
}

.rain-indicator.no-rain .rain-visual {
  background: linear-gradient(135deg, #f1f5f9, #e2e8f0);
}

.rain-indicator.raining .rain-visual {
  background: linear-gradient(135deg, var(--info-color), #0891b2);
  animation: rain-pulse 1.5s ease-in-out infinite;
}

@keyframes rain-pulse {
  0%, 100% { transform: scale(1); }
  50% { transform: scale(1.1); }
}

.rain-details {
  display: flex;
  justify-content: space-between;
  margin-top: var(--spacing-md);
}

.alerts-panel {
  background: var(--bg-card);
  border-radius: var(--radius-xl);
  padding: var(--spacing-xl);
  box-shadow: var(--shadow-md);
  border: 1px solid #e2e8f0;
}

.alerts-panel h2 {
  font-size: 1.25rem;
  font-weight: 600;
  color: var(--text-primary);
  margin-bottom: var(--spacing-lg);
}

.alert-item {
  display: flex;
  align-items: center;
  gap: var(--spacing-md);
  padding: var(--spacing-lg);
  background: var(--bg-secondary);
  border-radius: var(--radius-lg);
  border-left: 4px solid var(--info-color);
}

.alert-item.info { border-left-color: var(--info-color); }
.alert-item.warning { border-left-color: var(--warning-color); }
.alert-item.danger { border-left-color: var(--danger-color); }

.alert-icon { font-size: 1.5rem; }
.alert-content { flex: 1; }

.alert-title {
  font-weight: 600;
  color: var(--text-primary);
  margin-bottom: var(--spacing-xs);
}

.alert-message {
  color: var(--text-secondary);
  font-size: 0.875rem;
}

.alert-time {
  font-size: 0.75rem;
  color: var(--text-muted);
}

@media (max-width: 768px) {
  .navbar {
    padding: var(--spacing-md);
    flex-direction: column;
    gap: var(--spacing-md);
  }
  .nav-status {
    flex-direction: column;
    gap: var(--spacing-sm);
  }
  .dashboard { padding: var(--spacing-md); }
  .metrics-grid {
    grid-template-columns: 1fr;
    gap: var(--spacing-lg);
  }
  .metric-card { padding: var(--spacing-lg); }
  .metric-details {
    flex-direction: column;
    gap: var(--spacing-sm);
  }
  .env-item {
    flex-direction: column;
    text-align: center;
    gap: var(--spacing-xs);
  }
  .rain-details {
    flex-direction: column;
    gap: var(--spacing-sm);
  }
}

@media (max-width: 480px) {
  .navbar h1 { font-size: 1.25rem; }
  .card-header {
    flex-direction: column;
    text-align: center;
    gap: var(--spacing-sm);
  }
  .gauge {
    width: 120px;
    height: 60px;
  }
  .gauge-track { border-width: 6px; }
}
)rawliteral";