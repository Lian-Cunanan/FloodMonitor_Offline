#pragma once

const char login_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <title>Flood Monitor - Login</title>
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <style>
    body {
      font-family: 'Inter', -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, sans-serif;
      background: #87ceeb;
      background-attachment: fixed;
      margin: 0;
      padding: 20px;
      display: flex;
      justify-content: center;
      align-items: center;
      min-height: 100vh;
    }
    
    .login-container {
      background: white;
      padding: 3rem 2.5rem;
      border-radius: 20px;
      box-shadow: 0 20px 60px rgba(0, 0, 0, 0.3);
      width: 100%;
      max-width: 500px;
      backdrop-filter: blur(10px);
      border: 2px solid rgba(255, 255, 255, 0.2);
      position: relative;
      overflow: hidden;
    }

    .login-container::before {
      content: '';
      position: absolute;
      top: 0;
      left: 0;
      right: 0;
      height: 6px;
      background: linear-gradient(90deg, #2563eb, #0891b2, #059669);
    }
    
    .form-group {
      margin-bottom: 1.5rem;
    }
    
    label {
      display: block;
      margin-bottom: 0.75rem;
      font-weight: 700;
      color: #374151;
      font-size: 1rem;
    }
    
    input {
      width: 100%;
      padding: 1rem 1.25rem;
      border: 2px solid #e5e7eb;
      border-radius: 12px;
      box-sizing: border-box;
      font-size: 1rem;
      transition: all 0.3s ease;
      background: #f9fafb;
    }
    
    input:focus {
      outline: none;
      border-color: #2563eb;
      background: white;
      box-shadow: 0 0 0 3px rgba(37, 99, 235, 0.1);
    }
    
    button {
      width: 100%;
      padding: 1rem 1.5rem;
      background: linear-gradient(135deg, #2563eb, #1d4ed8);
      color: white;
      border: none;
      border-radius: 12px;
      cursor: pointer;
      font-size: 1.1rem;
      font-weight: 700;
      margin-bottom: 1.5rem;
      transition: all 0.3s ease;
      box-shadow: 0 4px 15px rgba(37, 99, 235, 0.3);
    }
    
    button:hover {
      background: linear-gradient(135deg, #1d4ed8, #1e40af);
      transform: translateY(-2px);
      box-shadow: 0 8px 25px rgba(37, 99, 235, 0.4);
    }
    
    button:active {
      transform: translateY(0);
    }
    
    .toggle-link {
      text-align: center;
      color: #2563eb;
      cursor: pointer;
      text-decoration: underline;
      font-weight: 600;
      font-size: 1rem;
      padding: 0.5rem;
      border-radius: 8px;
      transition: all 0.2s ease;
    }
    
    .toggle-link:hover {
      color: #1d4ed8;
      background: rgba(37, 99, 235, 0.05);
    }
    
    .error {
      color: #dc2626;
      text-align: center;
      margin-bottom: 1.5rem;
      padding: 1rem;
      background: #fef2f2;
      border-radius: 10px;
      border-left: 4px solid #dc2626;
      font-weight: 500;
    }
    
    .success {
      color: #059669;
      text-align: center;
      margin-bottom: 1.5rem;
      padding: 1rem;
      background: #dcfce7;
      border-radius: 10px;
      border-left: 4px solid #059669;
      font-weight: 500;
    }

    h2 {
      text-align: center;
      color: #1f2937;
      margin-bottom: 2rem;
      font-size: 2rem;
      font-weight: 800;
      position: relative;
    }

    h2::before {
      content: "🌊";
      font-size: 2rem;
      margin-right: 0.5rem;
    }

    h2::after {
      content: '';
      position: absolute;
      bottom: -10px;
      left: 50%;
      transform: translateX(-50%);
      width: 60px;
      height: 4px;
      background: linear-gradient(90deg, #2563eb, #0891b2);
      border-radius: 2px;
    }

    .loading {
      opacity: 0.6;
      pointer-events: none;
    }

    .demo-info {
      margin-top: 2rem;
      padding: 1.5rem;
      background: linear-gradient(135deg, #f0f9ff, #e0f2fe);
      border-radius: 12px;
      border: 1px solid #0891b2;
      text-align: center;
    }

    .demo-info small {
      font-size: 0.9rem;
      font-weight: 600;
    }

    @media (max-width: 600px) {
      .login-container {
        padding: 2rem 1.5rem;
        max-width: 400px;
        margin: 10px;
      }

      h2 {
        font-size: 1.75rem;
      }
    }
  </style>
</head>
<body>
  <div class="login-container">
    <h2 id="form-title">Flood Monitor Login</h2>
    <div id="message"></div>
    
    <form id="auth-form">
      <div class="form-group" id="username-group">
        <label for="username">Username:</label>
        <input type="text" id="username" name="username" required autocomplete="username" placeholder="Enter your username">
      </div>
      
      <div class="form-group" id="email-group" style="display: none;">
        <label for="email">Email:</label>
        <input type="email" id="email" name="email" autocomplete="email" placeholder="Enter your email address">
      </div>
      
      <div class="form-group">
        <label for="password">Password:</label>
        <input type="password" id="password" name="password" required autocomplete="current-password" placeholder="Enter your password">
      </div>
      
      <button type="submit" id="submit-btn">Login</button>
    </form>
    
    <div class="toggle-link" onclick="toggleForm()">
      <span id="toggle-text">Don't have an account? Register</span>
    </div>
    
    <div class="demo-info">
      <small><strong>🚀 Demo Access:</strong><br>
      Use any username/password combination</small>
    </div>
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
        title.textContent = 'Flood Monitor Login';
        emailGroup.style.display = 'none';
        passwordReq.style.display = 'none';
        submitBtn.textContent = 'Login';
        toggleText.textContent = "Don't have an account? Register";
        usernameLabel.textContent = 'Username:';
        document.getElementById('email').required = false;
        document.getElementById('password').setAttribute('autocomplete', 'current-password');
      } else {
        title.textContent = 'Register New Account';
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
    
    // Show ESP32 ready status
    console.log('ESP32 Flood Monitor Login System Ready');
  </script>
</body>
</html>
)rawliteral";