#pragma once

const char login_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <title>Flood Monitor - Login</title>
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <style>
    body { font-family: -apple-system, sans-serif; background: linear-gradient(135deg, #00c6ff, #0072ff); height: 100vh; display: flex; align-items: center; justify-content: center; margin: 0; }
    .card { background: white; padding: 2rem; border-radius: 12px; box-shadow: 0 10px 25px rgba(0,0,0,0.2); width: 100%; max-width: 350px; text-align: center; }
    h2 { color: #333; margin-top: 0; }
    input { width: 100%; padding: 12px; margin: 10px 0; border: 1px solid #ddd; border-radius: 6px; box-sizing: border-box; }
    button { width: 100%; padding: 12px; background: #0072ff; color: white; border: none; border-radius: 6px; cursor: pointer; font-size: 16px; font-weight: bold; }
    button:hover { background: #005bb5; }
    .toggle { margin-top: 15px; color: #0072ff; cursor: pointer; font-size: 14px; text-decoration: underline; }
    .error { color: red; margin-bottom: 10px; font-size: 14px; display: none; }
    .success { color: green; margin-bottom: 10px; font-size: 14px; display: none; }
    .sys-info { margin-top: 20px; font-size: 12px; color: #aaa; }
  </style>
</head>
<body>
  <div class="card">
    <h2 id="title">Login</h2>
    <div id="error-msg" class="error"></div>
    <div id="success-msg" class="success"></div>
    
    <input type="text" id="username" placeholder="Username" required>
    <input type="email" id="email" placeholder="Email (for registration)" style="display:none">
    <input type="password" id="password" placeholder="Password" required>
    
    <button onclick="handleSubmit()" id="btn-submit">Login</button>
    <div class="toggle" onclick="toggleMode()" id="toggle-txt">No account? Create one</div>
    
    <div class="sys-info">Flood Monitoring System v2.0</div>
  </div>

  <script>
    let isRegistering = false;

    function toggleMode() {
      isRegistering = !isRegistering;
      document.getElementById('email').style.display = isRegistering ? 'block' : 'none';
      document.getElementById('title').innerText = isRegistering ? 'Create Account' : 'Login';
      document.getElementById('btn-submit').innerText = isRegistering ? 'Register' : 'Login';
      document.getElementById('toggle-txt').innerText = isRegistering ? 'Have an account? Login' : 'No account? Create one';
      clearMessages();
    }

    function clearMessages() {
      document.getElementById('error-msg').style.display = 'none';
      document.getElementById('success-msg').style.display = 'none';
    }

    function showMessage(msg, isError) {
      const el = document.getElementById(isError ? 'error-msg' : 'success-msg');
      el.innerText = msg;
      el.style.display = 'block';
    }

    function handleSubmit() {
      clearMessages();
      const user = document.getElementById('username').value;
      const pass = document.getElementById('password').value;
      const email = document.getElementById('email').value;

      if(!user || !pass) {
        showMessage("Please fill in all fields", true);
        return;
      }

      const endpoint = isRegistering ? '/auth/register' : '/auth/login';
      const formData = new FormData();
      formData.append('username', user);
      formData.append('password', pass);
      if(isRegistering) formData.append('email', email);

      const btn = document.getElementById('btn-submit');
      const originalText = btn.innerText;
      btn.innerText = "Processing...";
      btn.disabled = true;

      fetch(endpoint, {
        method: 'POST',
        body: formData
      })
      .then(response => {
        if (response.ok) {
          if(isRegistering) {
            showMessage("Account created! Please login.", false);
            setTimeout(() => toggleMode(), 1500);
          } else {
            // LOGIN SUCCESS -> GO TO DASHBOARD
            window.location.href = "/"; 
          }
        } else if (response.status === 401) {
          showMessage("Incorrect username or password", true);
        } else if (response.status === 409) {
          showMessage("Username already exists!", true);
        } else {
          showMessage("System Error. Try again.", true);
        }
      })
      .catch(err => {
        showMessage("Connection failed. Check WiFi.", true);
      })
      .finally(() => {
        btn.innerText = originalText;
        btn.disabled = false;
      });
    }
  </script>
</body>
</html>
)rawliteral";