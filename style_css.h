#pragma once

const char style_css[] PROGMEM = R"rawliteral(
/* === GLOBAL BACKGROUND & LAYOUT (Sea Theme) === */
body { 
  font-family: -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, sans-serif; 
  background: linear-gradient(135deg, #00c6ff 0%, #0072ff 100%);
  margin: 0; padding: 20px; color: #333; min-height: 100vh;
}

/* === HEADER === */
.header { 
  background: rgba(255, 255, 255, 0.85); backdrop-filter: blur(10px);
  padding: 18px 22px; border-radius: 12px; 
  box-shadow: 0 10px 30px rgba(0,0,0,0.15); 
  display: flex; justify-content: space-between; align-items: center; 
  margin-bottom: 25px; 
}
h1 { color: #0072ff; margin: 0; font-size: 1.8em; font-weight: bold; }

/* === GRID SYSTEM === */
.grid-container { 
  display: grid; grid-template-columns: repeat(auto-fit, minmax(300px, 1fr)); gap: 25px; 
}

/* === CARDS === */
.card { 
  background-color: rgba(255,255,255,0.9); backdrop-filter: blur(8px);
  border-radius: 15px; box-shadow: 0 8px 25px rgba(0,0,0,0.15); 
  padding: 25px; text-align: center; transition: transform 0.2s;
}
.card:hover { transform: translateY(-4px); }
.card h2 { margin-top: 0; color: #0072ff; font-weight: 600; }
.card-gate h3 { font-size: 2.8em; margin: 15px 0; font-weight: bold; color: #00c6ff; }

/* === GAUGE === */
.gauge { width: 100%; max-width: 220px; margin: 15px auto; }
.gauge-body { 
  width: 100%; height: 0; padding-bottom: 50%; background: #e0e0e0; 
  position: relative; border-top-left-radius: 120px 200px; border-top-right-radius: 120px 200px; 
  overflow: hidden; box-shadow: inset 0 3px 6px rgba(0,0,0,0.2);
}
.gauge-fill { 
  position: absolute; top: 100%; left: 0; width: inherit; height: 100%; 
  background: linear-gradient(135deg, #00c6ff, #0072ff); 
  transform-origin: center top; transform: rotate(0deg); transition: transform 0.4s ease-out; 
}
.gauge-cover { 
  width: 70%; height: 0; padding-bottom: 35%; background: rgba(255,255,255,0.9); 
  backdrop-filter: blur(6px); position: absolute; top: 100%; left: 50%; 
  transform: translate(-50%, -50%); border-radius: 50% 50% 0 0; 
  font-size: 1.6em; font-weight: bold; color: #333; line-height: 70px; 
}

/* === BUTTONS === */
.qr-btn { 
  background: linear-gradient(135deg, #00c6ff, #0072ff);
  color: white; border: none; padding: 12px 20px; border-radius: 8px; 
  cursor: pointer; font-size: 14px; font-weight: 600; transition: all 0.3s;
  margin-left: 5px; margin-bottom: 5px;
}
.qr-btn:hover { box-shadow: 0 5px 18px rgba(0,198,255,0.4); transform: translateY(-2px); }

.logout-btn {
  background-color: #f0f2f5; color: #0072ff; border: none; padding: 10px 18px;
  border-radius: 8px; font-size: 14px; font-weight: 600; cursor: pointer; transition: all 0.3s;
}
.logout-btn:hover { background-color: #e0e2e5; transform: translateY(-2px); }

/* === MODAL === */
.modal { 
  display: none; position: fixed; z-index: 100; left: 0; top: 0; 
  width: 100%; height: 100%; overflow: auto; background-color: rgba(0,0,0,0.5); 
}
.modal-content { 
  background: white; margin: 10% auto; padding: 25px; 
  width: 90%; max-width: 600px; border-radius: 12px; 
  box-shadow: 0 10px 35px rgba(0,0,0,0.3); position: relative;
}
.close-btn { 
  position: absolute; right: 20px; top: 15px;
  color: #888; font-size: 28px; font-weight: bold; cursor: pointer; 
}
.close-btn:hover { color: #444; }

/* === HISTORY TABLE === */
.table-responsive {
  max-height: 400px; overflow-y: auto; margin-top: 15px;
  border: 1px solid #eee; border-radius: 8px;
}
.history-table { width: 100%; border-collapse: collapse; font-size: 14px; }
.history-table th {
  background-color: #f8f9fa; color: #0072ff; position: sticky;
  top: 0; padding: 12px; text-align: left; border-bottom: 2px solid #e9ecef;
}
.history-table td { padding: 10px 12px; border-bottom: 1px solid #eee; color: #444; }
.history-table tr:nth-child(even) { background-color: #f8f9fa; }
.status-badge { padding: 4px 8px; border-radius: 4px; font-size: 11px; font-weight: bold; }
.badge-open { background-color: #e7f5ff; color: #0072ff; }
.badge-closed { background-color: #fff5f5; color: #ff6b6b; }

/* === NEW: FLOOD ALERT STYLES === */
.alert-modal-content {
  background: #fff;
  border-left: 10px solid #ff4444;
  text-align: center;
  margin: 15% auto;
  padding: 30px;
  width: 85%;
  max-width: 400px;
  border-radius: 8px;
  box-shadow: 0 0 50px rgba(255, 0, 0, 0.5);
  animation: pulse-red 2s infinite;
}

@keyframes pulse-red {
  0% { box-shadow: 0 0 0 0 rgba(255, 68, 68, 0.7); }
  70% { box-shadow: 0 0 0 20px rgba(255, 68, 68, 0); }
  100% { box-shadow: 0 0 0 0 rgba(255, 68, 68, 0); }
}

.alert-title {
  color: #ff4444;
  font-size: 2em;
  font-weight: bold;
  margin-bottom: 10px;
  text-transform: uppercase;
}

.alert-value {
  font-size: 3em;
  font-weight: bold;
  color: #333;
}

.alert-desc {
  font-size: 1.2em;
  color: #555;
  margin: 15px 0;
}

.alert-dismiss-btn {
  background: #ff4444;
  color: white;
  border: none;
  padding: 12px 30px;
  border-radius: 25px;
  font-size: 1.1em;
  font-weight: bold;
  cursor: pointer;
  transition: background 0.2s;
}

.alert-dismiss-btn:hover {
  background: #cc0000;
}
)rawliteral";