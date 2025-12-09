#pragma once

const char script_js[] PROGMEM = R"rawliteral(
var gateway = `ws://${window.location.hostname}:81/`;
var websocket;

function initWebSocket() {
  websocket = new WebSocket(gateway);
  websocket.onopen  = function() { document.getElementById('ws-status').classList.add('connected'); };
  websocket.onclose = function() { document.getElementById('ws-status').classList.remove('connected'); setTimeout(initWebSocket, 2000); };
  websocket.onmessage = onMessage;
}

function onMessage(event) {
  var data = JSON.parse(event.data);
  
  // Update elements
  document.getElementById('sys-mode').innerHTML = data.mode;
  document.getElementById('water-value').innerHTML = data.water_percent + '%';
  document.getElementById('water-raw').innerHTML = data.water_raw;
  
  // --- TRIGGER ALERT LOGIC ---
  if (typeof checkFloodAlert === "function") {
    checkFloodAlert(data.water_percent);
  }

  var waterAngle = (data.water_percent / 100) * 180; 
  document.getElementById('water-fill').style.transform = `rotate(${waterAngle}deg)`;
  
  var gateStatus = document.getElementById('gate-status');
  if (data.gate_status == "OPEN") {
    gateStatus.innerHTML = "OPEN";
    gateStatus.style.color = "#2ecc71";
  } else {
    gateStatus.innerHTML = "CLOSED";
    gateStatus.style.color = "#e74c3c";
  }
  
  if(document.getElementById('rain-value')) document.getElementById('rain-value').innerHTML = data.rain_raw;
  if(document.getElementById('rain-status')) document.getElementById('rain-status').innerHTML = data.rain_status.replace('_', ' ');
  if(document.getElementById('temp-value')) document.getElementById('temp-value').innerHTML = data.temp;
  if(document.getElementById('humidity-value')) document.getElementById('humidity-value').innerHTML = data.humidity;
  
  if(document.getElementById('light-value')) {
    var lightRaw = parseInt(data.light_raw);
    var lightText = (lightRaw > 2000) ? "Darkness" : "Bright Light";
    document.getElementById('light-value').innerHTML = lightText;
  }
}

window.addEventListener('load', initWebSocket);
)rawliteral";