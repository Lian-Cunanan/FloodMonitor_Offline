#pragma once

const char login_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <title>Flood Monitor - Login</title>
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <style>
    body {
      font-family: Arial, sans-serif;
      background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
      margin: 0;
      padding: 0;
      display: flex;
      justify-content: center;
      align-items: center;
      min-height: 100vh;
    }
    
    .login-container {
      background: white;
      padding: 2rem;
      border-radius: 10px;
      box-shadow: 0 4px 6px rgba(0, 0, 0, 0.1);
      width: 100%;
      max-width: 400px;
    }
    
    .form-group {
      margin-bottom: 1rem;
    }
    
    label {
      display: block;
      margin-bottom: 0.5rem;
      font-weight: bold;
    }
    
    input {
      width: 100%;
      padding: 0.75rem;
      border: 1px solid #ddd;
      border-radius: 5px;
      box-sizing: border-box;
    }
    
    button {
      width: 100%;
      padding: 0.75rem;
      background: #0056b3;
      color: white;
      border: none;
      border-radius: 5px;
      cursor: pointer;
      margin-bottom: 1rem;
    }
    
    button:hover {
      background: #004494;
    }
    
    .toggle-link {
      text-align: center;
      color: #0056b3;
      cursor: pointer;
      text-decoration: underline;
    }
    
    .error {
      color: red;
      text-align: center;
      margin-bottom: 1rem;
    }
    
    .success {
      color: green;
      text-align: center;
      margin-bottom: 1rem;
    }
    
    .loading {
      opacity: 0.6;
      pointer-events: none;
    }
    
    .info {
      color: #0056b3;
      text-align: center;
      margin-bottom: 1rem;
      font-size: 0.9rem;
    }
    
    .password-requirements {
      font-size: 0.8rem;
      color: #666;
      margin-top: 0.5rem;
    }
    
    .activity-log {
      position: fixed;
      bottom: 10px;
      right: 10px;
      background: rgba(0,0,0,0.8);
      color: white;
      padding: 5px 10px;
      border-radius: 5px;
      font-size: 0.8rem;
      display: none;
    }
    
    .system-info {
      position: fixed;
      bottom: 10px;
      left: 10px;
      background: rgba(0,0,0,0.7);
      color: white;
      padding: 5px 10px;
      border-radius: 5px;
      font-size: 0.7rem;
    }
  </style>
</head>
<body>
  <div class="login-container">
    <h2 id="form-title">🌊 Flood Monitor Login</h2>
    <div id="message"></div>
    
    <form id="auth-form">
      <div class="form-group" id="username-group">
        <label for="username">Username/Email:</label>
        <input type="text" id="username" name="username" required autocomplete="username">
      </div>
      
      <div class="form-group" id="email-group" style="display: none;">
        <label for="email">Email:</label>
        <input type="email" id="email" name="email" autocomplete="email">
        <div class="info">Use a valid email for password recovery</div>
      </div>
      
      <div class="form-group">
        <label for="password">Password:</label>
        <input type="password" id="password" name="password" required autocomplete="current-password">
        <div class="password-requirements" id="password-req" style="display: none;">
          Password must be at least 6 characters long
        </div>
      </div>
      
      <button type="submit" id="submit-btn">Login</button>
    </form>
    
    <div class="toggle-link" onclick="toggleForm()">
      <span id="toggle-text">Don't have an account? Register</span>
    </div>
    
    <div class="info" style="margin-top: 1rem;">
      <small>Default: admin/admin123 or operator/operator123</small>
    </div>
  </div>

  <div class="system-info" id="system-info">
    ESP32 Ready
  </div>

  <script>
    let isLoginMode = true;
    let loginAttempts = 0;
    const maxAttempts = 5;
    
    // Simplified logging for ESP32
    function logActivity(action, details = {}) {
      fetch('/log', {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({
          action: action,
          details: JSON.stringify(details),
          timestamp: Date.now()
        })
      }).catch(() => {}); // Fail silently if logging fails
    }
    
    function validatePassword(password) {
      if (!isLoginMode) {
        return password.length >= 6;
      }
      return password.length > 0;
    }
    
    function toggleForm() {
      isLoginMode = !isLoginMode;
      const title = document.getElementById('form-title');
      const emailGroup = document.getElementById('email-group');
      const submitBtn = document.getElementById('submit-btn');
      const toggleText = document.getElementById('toggle-text');
      const usernameLabel = document.querySelector('label[for="username"]');
      const passwordReq = document.getElementById('password-req');
      
      if (isLoginMode) {
        title.textContent = '🌊 Flood Monitor Login';
        emailGroup.style.display = 'none';
        passwordReq.style.display = 'none';
        submitBtn.textContent = 'Login';
        toggleText.textContent = "Don't have an account? Register";
        usernameLabel.textContent = 'Username/Email:';
        document.getElementById('email').required = false;
        document.getElementById('password').setAttribute('autocomplete', 'current-password');
      } else {
        title.textContent = '🌊 Register New Account';
        emailGroup.style.display = 'block';
        passwordReq.style.display = 'block';
        submitBtn.textContent = 'Create Account';
        toggleText.textContent = 'Already have an account? Login';
        usernameLabel.textContent = 'Username:';
        document.getElementById('email').required = true;
        document.getElementById('password').setAttribute('autocomplete', 'new-password');
      }
      
      document.getElementById('message').innerHTML = '';
      loginAttempts = 0;
    }
    
    document.getElementById('auth-form').addEventListener('submit', function(e) {
      e.preventDefault();
      
      const username = document.getElementById('username').value.trim();
      const email = document.getElementById('email').value.trim();
      const password = document.getElementById('password').value;
      const messageDiv = document.getElementById('message');
      const submitBtn = document.getElementById('submit-btn');
      
      // Validate inputs
      if (!username) {
        messageDiv.innerHTML = '<div class="error">Username is required</div>';
        return;
      }
      
      if (!validatePassword(password)) {
        messageDiv.innerHTML = '<div class="error">Password must be at least 6 characters</div>';
        return;
      }
      
      if (!isLoginMode && (!email || !email.includes('@'))) {
        messageDiv.innerHTML = '<div class="error">Valid email is required</div>';
        return;
      }
      
      // Check login attempts
      if (isLoginMode && loginAttempts >= maxAttempts) {
        messageDiv.innerHTML = '<div class="error">Too many attempts. Please refresh and try again.</div>';
        logActivity('LOGIN_BLOCKED', { username: username, attempts: loginAttempts });
        return;
      }
      
      // Show loading state
      submitBtn.classList.add('loading');
      submitBtn.disabled = true;
      submitBtn.textContent = isLoginMode ? 'Logging in...' : 'Creating account...';
      
      if (isLoginMode) {
        // Login attempt - simplified for ESP32
        submitBtn.disabled = true;
        submitBtn.textContent = 'Logging in...';
        
        fetch('/login', {
          method: 'POST',
          headers: { 'Content-Type': 'application/x-www-form-urlencoded' },
          body: `username=${encodeURIComponent(username)}&password=${encodeURIComponent(password)}`
        })
        .then(response => {
          if (response.ok) {
            return response.text();
          }
          throw new Error('Login failed');
        })
        .then(data => {
          if (data.includes('success') || data.includes('dashboard')) {
            messageDiv.innerHTML = '<div class="success">Login successful!</div>';
            logActivity('LOGIN_SUCCESS', { username: username });
            setTimeout(() => {
              window.location.href = '/dashboard';
            }, 1000);
          } else {
            throw new Error('Invalid credentials');
          }
        })
        .catch(error => {
          loginAttempts++;
          messageDiv.innerHTML = '<div class="error">Invalid credentials</div>';
          logActivity('LOGIN_FAILED', { username: username, attempts: loginAttempts });
        })
        .finally(() => {
          submitBtn.disabled = false;
          submitBtn.textContent = 'Login';
        });
        
      } else {
        // Registration - simplified for ESP32
        submitBtn.disabled = true;
        submitBtn.textContent = 'Creating account...';
        
        fetch('/register', {
          method: 'POST',
          headers: { 'Content-Type': 'application/x-www-form-urlencoded' },
          body: `username=${encodeURIComponent(username)}&email=${encodeURIComponent(email)}&password=${encodeURIComponent(password)}`
        })
        .then(response => {
          if (response.ok) {
            return response.text();
          }
          throw new Error('Registration failed');
        })
        .then(data => {
          if (data.includes('success')) {
            messageDiv.innerHTML = '<div class="success">Registration successful! Please login.</div>';
            logActivity('REGISTER_SUCCESS', { username: username, email: email });
            setTimeout(() => {
              toggleForm();
              document.getElementById('username').value = username;
            }, 2000);
          } else {
            throw new Error(data);
          }
        })
        .catch(error => {
          messageDiv.innerHTML = '<div class="error">Registration failed</div>';
          logActivity('REGISTER_FAILED', { username: username, email: email });
        })
        .finally(() => {
          submitBtn.disabled = false;
          submitBtn.textContent = 'Create Account';
        });
      }
    });
    
    // Show ESP32 system info
    fetch('/system-info')
      .then(response => response.json())
      .then(data => {
        document.getElementById('system-info').textContent = 
          `ESP32 ${data.chip_model || 'Ready'} | ${data.free_heap || 0}KB Free`;
      })
      .catch(() => {
        document.getElementById('system-info').textContent = 'ESP32 System';
      });
  </script>
</body>
</html>
)rawliteral";