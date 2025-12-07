#pragma once

const char style_css[] PROGMEM = R"rawliteral(
<<<<<<< HEAD
/* Modern Professional Flood Monitor UI */

:root {
  --primary-color: #2563eb;
  --secondary-color: #0f172a;
  --success-color: #059669;
  --warning-color: #d97706;
  --danger-color: #dc2626;
  --info-color: #0891b2;
  --light-bg: #f8fafc;
  --card-bg: #ffffff;
  --text-primary: #1e293b;
  --text-secondary: #64748b;
  --border-color: #e2e8f0;
  --shadow: 0 4px 6px -1px rgba(0, 0, 0, 0.1), 0 2px 4px -1px rgba(0, 0, 0, 0.06);
  --shadow-lg: 0 10px 15px -3px rgba(0, 0, 0, 0.1), 0 4px 6px -2px rgba(0, 0, 0, 0.05);
  --radius: 8px;
  --radius-lg: 12px;
}

* {
  box-sizing: border-box;
  margin: 0;
  padding: 0;
}

body {
  font-family: 'Inter', -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, sans-serif;
  background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
  min-height: 100vh;
  line-height: 1.5;
  color: var(--text-primary);
  padding: 0;
  margin: 0;
}

.header {
  background: var(--card-bg);
  padding: 1rem 1.5rem;
  display: flex;
  justify-content: space-between;
  align-items: center;
  box-shadow: var(--shadow);
  border-bottom: 3px solid var(--primary-color);
  position: sticky;
  top: 0;
  z-index: 100;
}

.header h1 {
  font-size: 1.75rem;
  font-weight: 700;
  color: var(--primary-color);
  display: flex;
  align-items: center;
  gap: 0.5rem;
}

.header h1::before {
  content: "🌊";
  font-size: 2rem;
}

.header-info {
  display: flex;
  flex-direction: column;
  gap: 0.25rem;
}

.header-controls {
  display: flex;
  align-items: center;
  gap: 1rem;
}

.status-badge {
  padding: 0.375rem 0.75rem;
  border-radius: var(--radius);
  font-size: 0.875rem;
  font-weight: 600;
  text-transform: uppercase;
  letter-spacing: 0.05em;
}

.status-badge.online { 
  background: #dcfce7; 
  color: var(--success-color); 
}

.status-badge.offline { 
  background: #fef2f2; 
  color: var(--danger-color); 
}

.logout-btn {
  background: var(--danger-color);
  color: white;
  border: none;
  padding: 0.5rem 1rem;
  border-radius: var(--radius);
  font-weight: 500;
  cursor: pointer;
  transition: all 0.2s;
}

.logout-btn:hover {
  background: #b91c1c;
  transform: translateY(-1px);
}

.status-dot {
  width: 12px;
  height: 12px;
  border-radius: 50%;
  background: var(--success-color);
  box-shadow: 0 0 0 2px var(--card-bg), 0 0 8px rgba(5, 150, 105, 0.5);
  animation: pulse 2s infinite;
}

@keyframes pulse {
  0%, 100% { opacity: 1; }
  50% { opacity: 0.5; }
}

.container {
  max-width: 1200px;
  margin: 0 auto;
  padding: 2rem 1rem;
}

.action-bar {
  display: flex;
  flex-wrap: wrap;
  gap: 0.75rem;
  margin-bottom: 2rem;
  justify-content: flex-end;
}

.action-btn {
  background: var(--card-bg);
  border: 2px solid var(--border-color);
  padding: 0.625rem 1rem;
  border-radius: var(--radius);
  font-size: 0.875rem;
  font-weight: 500;
  cursor: pointer;
  transition: all 0.2s;
  display: flex;
  align-items: center;
  gap: 0.5rem;
  color: var(--text-primary);
  text-decoration: none;
}

.action-btn:hover {
  border-color: var(--primary-color);
  color: var(--primary-color);
  transform: translateY(-2px);
  box-shadow: var(--shadow);
}

.grid-container {
  display: grid;
  grid-template-columns: repeat(auto-fit, minmax(320px, 1fr));
  gap: 1.5rem;
  margin-bottom: 2rem;
}

.card {
  background: var(--card-bg);
  border-radius: var(--radius-lg);
  padding: 1.5rem;
  box-shadow: var(--shadow);
  border: 1px solid var(--border-color);
  transition: all 0.3s ease;
  position: relative;
  overflow: hidden;
}

.card::before {
  content: '';
  position: absolute;
  top: 0;
  left: 0;
  right: 0;
  height: 4px;
  background: linear-gradient(90deg, var(--primary-color), var(--info-color));
}

.card:hover {
  transform: translateY(-4px);
  box-shadow: var(--shadow-lg);
}

.card h2 {
  font-size: 1.25rem;
  font-weight: 600;
  margin-bottom: 1rem;
  color: var(--text-primary);
  display: flex;
  align-items: center;
  gap: 0.5rem;
}

.card-water::before { background: linear-gradient(90deg, #3b82f6, #06b6d4); }
.card-water h2::before { content: "💧"; }

.card-gate::before { background: linear-gradient(90deg, #8b5cf6, #a855f7); }
.card-gate h2::before { content: "🚪"; }

.card-env::before { background: linear-gradient(90deg, #10b981, #059669); }
.card-env h2::before { content: "🌡️"; }

.card-database::before { background: linear-gradient(90deg, #f59e0b, #d97706); }
.card-database h2::before { content: "💾"; }

.gauge {
  position: relative;
  width: 120px;
  height: 120px;
  margin: 1rem auto;
}

.gauge-body {
  width: 100%;
  height: 100%;
  border-radius: 50%;
  background: conic-gradient(
    from 0deg,
    var(--success-color) 0deg 108deg,
    var(--warning-color) 108deg 252deg,
    var(--danger-color) 252deg 360deg
  );
  padding: 8px;
  display: flex;
  align-items: center;
  justify-content: center;
}

.gauge-fill {
  width: 100%;
  height: 100%;
  border-radius: 50%;
  background: var(--light-bg);
  display: flex;
  align-items: center;
  justify-content: center;
  font-size: 1.5rem;
  font-weight: 700;
  color: var(--text-primary);
  position: relative;
  overflow: hidden;
}

.gauge-cover {
  position: absolute;
  top: 50%;
  left: 50%;
  transform: translate(-50%, -50%);
  font-size: 1.25rem;
  font-weight: 700;
  z-index: 10;
}

.status-grid {
  display: grid;
  grid-template-columns: 1fr 1fr;
  gap: 1rem;
}

.status-item {
  display: flex;
  justify-content: space-between;
  align-items: center;
  padding: 0.75rem;
  background: var(--light-bg);
  border-radius: var(--radius);
  border-left: 4px solid var(--info-color);
}

.status-value {
  font-weight: 600;
  font-size: 1.125rem;
}

.status-critical { border-left-color: var(--danger-color); }
.status-warning { border-left-color: var(--warning-color); }
.status-normal { border-left-color: var(--success-color); }

.gate-status {
  text-align: center;
  margin: 1rem 0;
}

.gate-status h3 {
  font-size: 2rem;
  font-weight: 700;
  padding: 1rem;
  border-radius: var(--radius-lg);
  margin-bottom: 1rem;
}

.gate-open {
  background: linear-gradient(135deg, #fef3c7, #fde68a);
  color: #92400e;
}

.gate-closed {
  background: linear-gradient(135deg, #dcfce7, #bbf7d0);
  color: #166534;
}

.maintenance-controls {
  display: flex;
  gap: 0.75rem;
  margin-top: 1rem;
}

.control-btn {
  flex: 1;
  padding: 0.75rem;
  border: none;
  border-radius: var(--radius);
  font-weight: 500;
  cursor: pointer;
  transition: all 0.2s;
  font-size: 0.875rem;
}

.btn-open {
  background: var(--warning-color);
  color: white;
}

.btn-open:hover {
  background: #c2410c;
}

.btn-close {
  background: var(--success-color);
  color: white;
}

.btn-close:hover {
  background: #047857;
}

.modal {
  display: none;
  position: fixed;
  z-index: 1000;
  left: 0;
  top: 0;
  width: 100%;
  height: 100%;
  background: rgba(0, 0, 0, 0.6);
  backdrop-filter: blur(4px);
}

.modal-content {
  background: var(--card-bg);
  margin: 5% auto;
  padding: 2rem;
  border-radius: var(--radius-lg);
  width: 90%;
  max-width: 500px;
  box-shadow: var(--shadow-lg);
  position: relative;
  max-height: 80vh;
  overflow-y: auto;
}

.close-btn {
  position: absolute;
  right: 1rem;
  top: 1rem;
  font-size: 1.5rem;
  font-weight: bold;
  cursor: pointer;
  color: var(--text-secondary);
  width: 2rem;
  height: 2rem;
  display: flex;
  align-items: center;
  justify-content: center;
  border-radius: 50%;
  transition: all 0.2s;
}

.close-btn:hover {
  background: var(--light-bg);
  color: var(--text-primary);
}

.db-stats {
  display: grid;
  grid-template-columns: repeat(auto-fit, minmax(150px, 1fr));
  gap: 1rem;
  margin: 1rem 0;
}

.db-stat {
  text-align: center;
  padding: 1rem;
  background: var(--light-bg);
  border-radius: var(--radius);
}

.db-stat-value {
  font-size: 1.5rem;
  font-weight: 700;
  color: var(--primary-color);
}

.db-stat-label {
  font-size: 0.875rem;
  color: var(--text-secondary);
  margin-top: 0.25rem;
}

.activity-list {
  max-height: 200px;
  overflow-y: auto;
  border: 1px solid var(--border-color);
  border-radius: var(--radius);
}

.activity-item {
  padding: 0.75rem;
  border-bottom: 1px solid var(--border-color);
  display: flex;
  justify-content: space-between;
  align-items: center;
}

.activity-item:last-child {
  border-bottom: none;
}

.activity-action {
  font-weight: 500;
}

.activity-time {
  font-size: 0.75rem;
  color: var(--text-secondary);
}

@media (max-width: 768px) {
  .container {
    padding: 1rem;
  }
  
  .header {
    padding: 1rem;
    flex-direction: column;
    gap: 1rem;
    text-align: center;
  }
  
  .header-controls {
    justify-content: center;
  }
  
  .grid-container {
    grid-template-columns: 1fr;
    gap: 1rem;
  }
  
  .action-bar {
    justify-content: center;
  }
  
  .modal-content {
    margin: 10% auto;
    width: 95%;
    padding: 1.5rem;
  }
}

@keyframes slideIn {
  from {
    opacity: 0;
    transform: translateY(20px);
  }
  to {
    opacity: 1;
    transform: translateY(0);
  }
}

.card {
  animation: slideIn 0.5s ease-out;
}

.loading {
  opacity: 0.6;
  pointer-events: none;
  position: relative;
}

.loading::after {
  content: '';
  position: absolute;
  top: 50%;
  left: 50%;
  width: 20px;
  height: 20px;
  margin: -10px 0 0 -10px;
  border: 2px solid var(--primary-color);
  border-top-color: transparent;
  border-radius: 50%;
  animation: spin 1s linear infinite;
}

@keyframes spin {
  to {
    transform: rotate(360deg);
  }
}

.alert {
  padding: 1rem;
  border-radius: var(--radius);
  margin: 1rem 0;
  font-weight: 500;
}

.alert-success {
  background: #dcfce7;
  color: var(--success-color);
  border-left: 4px solid var(--success-color);
}

.alert-error {
  background: #fef2f2;
  color: var(--danger-color);
  border-left: 4px solid var(--danger-color);
}

.alert-warning {
  background: #fffbeb;
  color: var(--warning-color);
  border-left: 4px solid var(--warning-color);
}

@media print {
  body {
    background: white;
  }
  
  .header-controls,
  .action-bar,
  .maintenance-controls {
    display: none;
  }
}
=======
/* === GLOBAL BACKGROUND & LAYOUT (Sea Theme) === */
body { 
  font-family: -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, sans-serif; 
  background: linear-gradient(135deg, #00c6ff 0%, #0072ff 100%);
  margin: 0; 
  padding: 20px; 
  color: #333;
  min-height: 100vh;
}

/* === HEADER (from B, with A's spacing preserved) === */
.header { 
  background: rgba(255, 255, 255, 0.85);
  backdrop-filter: blur(10px);
  padding: 18px 22px; 
  border-radius: 12px; 
  box-shadow: 0 10px 30px rgba(0,0,0,0.15); 
  display: flex; 
  justify-content: space-between; 
  align-items: center; 
  margin-bottom: 25px; 
}

h1 { 
  color: #0072ff; 
  margin: 0; 
  font-size: 1.8em; 
  font-weight: bold;
}

/* === GRID (B version) === */
.grid-container { 
  display: grid; 
  grid-template-columns: repeat(auto-fit, minmax(300px, 1fr)); 
  gap: 25px; 
}

/* === CARDS (B version enhanced) === */
.card { 
  background-color: rgba(255,255,255,0.9); 
  backdrop-filter: blur(8px);
  border-radius: 15px; 
  box-shadow: 0 8px 25px rgba(0,0,0,0.15); 
  padding: 25px; 
  text-align: center; 
  transition: transform 0.2s;
}

.card:hover { transform: translateY(-4px); }

.card h2 { 
  margin-top: 0; 
  color: #0072ff; 
  font-weight: 600;
}

/* === GATE STATUS (from B) === */
.card-gate h3 { 
  font-size: 2.8em; 
  margin: 15px 0; 
  font-weight: bold; 
  color: #00c6ff;
}

/* === GAUGE COMBINED (Mostly B but compatible with A) === */
.gauge { 
  width: 100%; 
  max-width: 220px; 
  margin: 15px auto; 
}

.gauge-body { 
  width: 100%; 
  height: 0; 
  padding-bottom: 50%; 
  background: #e0e0e0; 
  position: relative; 
  border-top-left-radius: 120px 200px; 
  border-top-right-radius: 120px 200px; 
  overflow: hidden; 
  box-shadow: inset 0 3px 6px rgba(0,0,0,0.2);
}

.gauge-fill { 
  position: absolute; 
  top: 100%; 
  left: 0; 
  width: inherit; 
  height: 100%; 
  background: linear-gradient(135deg, #00c6ff, #0072ff); 
  transform-origin: center top; 
  transform: rotate(0deg); 
  transition: transform 0.4s ease-out; 
}

.gauge-cover { 
  width: 70%; 
  height: 0; 
  padding-bottom: 35%; 
  background: rgba(255,255,255,0.9); 
  backdrop-filter: blur(6px);
  position: absolute; 
  top: 100%; 
  left: 50%; 
  transform: translate(-50%, -50%); 
  border-radius: 50% 50% 0 0; 
  font-size: 1.6em; 
  font-weight: bold; 
  color: #333; 
  line-height: 70px; 
}

/* === STATUS DOT (B version) === */
.status-dot { 
  width: 16px; 
  height: 16px; 
  border-radius: 50%; 
  background-color: #e74c3c; 
  box-shadow: 0 0 8px rgba(0,0,0,0.3);
}

.status-dot.connected { 
  background-color: #2ecc71; 
  box-shadow: 0 0 10px rgba(46, 204, 113, 0.7);
}

/* === QR BUTTON (B style) === */
.qr-btn { 
  background: linear-gradient(135deg, #00c6ff, #0072ff);
  color: white; 
  border: none; 
  padding: 12px 20px; 
  border-radius: 8px; 
  cursor: pointer; 
  font-size: 14px; 
  font-weight: 600;
  transition: all 0.3s;
}

.qr-btn:hover {
  box-shadow: 0 5px 18px rgba(0,198,255,0.4);
  transform: translateY(-2px);
}

/* === LOGOUT BUTTON (B version) === */
.logout-btn {
  background-color: #f0f2f5;
  color: #0072ff;
  border: none;
  padding: 10px 18px;
  border-radius: 8px;
  font-size: 14px;
  font-weight: 600;
  cursor: pointer;
  transition: all 0.3s;
}

.logout-btn:hover {
  background-color: #e0e2e5;
  transform: translateY(-2px);
}

/* === MODAL (B version with A compatibility) === */
.modal { 
  display: none; 
  position: fixed; 
  z-index: 100; 
  left: 0; 
  top: 0; 
  width: 100%; 
  height: 100%; 
  overflow: auto; 
  background-color: rgba(0,0,0,0.45); 
}

.modal-content { 
  background: rgba(255,255,255,0.95);
  backdrop-filter: blur(8px);
  margin: 18% auto; 
  padding: 25px; 
  width: 85%; 
  max-width: 330px; 
  text-align: center; 
  border-radius: 12px; 
  box-shadow: 0 10px 35px rgba(0,0,0,0.25);
}

.close-btn { 
  color: #888; 
  float: right; 
  font-size: 28px; 
  font-weight: bold; 
  cursor: pointer; 
}

.close-btn:hover { color: #444; }
>>>>>>> d5a1704f3b13828ef3fbae00aa481f41e2ef0706
)rawliteral";
