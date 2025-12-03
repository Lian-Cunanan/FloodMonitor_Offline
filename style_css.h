#pragma once

const char style_css[] PROGMEM = R"rawliteral(
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
)rawliteral";
