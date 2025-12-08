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
    
    // Optimized logging for ESP32 - reduced payload
    function logActivity(action, details = {}) {
      fetch('/log', {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({ action, details, t: Date.now() })
      }).catch(() => {}); // Fail silently
    }
    
    // Simplified validation
    const validatePassword = (password) => isLoginMode ? password.length > 0 : password.length >= 6;
    
    function toggleForm() {
      isLoginMode = !isLoginMode;
      const elements = {
        title: document.getElementById('form-title'),
        emailGroup: document.getElementById('email-group'),
        submitBtn: document.getElementById('submit-btn'),
        toggleText: document.getElementById('toggle-text'),
        usernameLabel: document.querySelector('label[for="username"]'),
        email: document.getElementById('email'),
        password: document.getElementById('password')
      };
      
      if (isLoginMode) {
        elements.title.textContent = 'Flood Monitor Login';
        elements.emailGroup.style.display = 'none';
        elements.submitBtn.textContent = 'Login';
        elements.toggleText.textContent = "Don't have an account? Register";
        elements.usernameLabel.textContent = 'Username:';
        elements.email.required = false;
        elements.password.setAttribute('autocomplete', 'current-password');
      } else {
        elements.title.textContent = 'Register New Account';
        elements.emailGroup.style.display = 'block';
        elements.submitBtn.textContent = 'Create Account';
        elements.toggleText.textContent = 'Already have an account? Login';
        elements.usernameLabel.textContent = 'Username:';
        elements.email.required = true;
        elements.password.setAttribute('autocomplete', 'new-password');
      }
      
      document.getElementById('message').innerHTML = '';
      loginAttempts = 0;
    }
    
    document.getElementById('auth-form').addEventListener('submit', function(e) {
      e.preventDefault();
      
      const formData = {
        username: document.getElementById('username').value.trim(),
        email: document.getElementById('email').value.trim(),
        password: document.getElementById('password').value
      };
      
      const messageDiv = document.getElementById('message');
      const submitBtn = document.getElementById('submit-btn');
      
      // Validation checks
      if (!formData.username) return messageDiv.innerHTML = '<div class="error">Username is required</div>';
      if (!validatePassword(formData.password)) return messageDiv.innerHTML = '<div class="error">Password must be at least 6 characters</div>';
      if (!isLoginMode && (!formData.email || !formData.email.includes('@'))) return messageDiv.innerHTML = '<div class="error">Valid email is required</div>';
      
      // Rate limiting
      if (isLoginMode && loginAttempts >= maxAttempts) {
        logActivity('LOGIN_BLOCKED', { username: formData.username, attempts: loginAttempts });
        return messageDiv.innerHTML = '<div class="error">Too many attempts. Please refresh and try again.</div>';
      }
      
      // Loading state
      submitBtn.classList.add('loading');
      submitBtn.disabled = true;
      submitBtn.textContent = isLoginMode ? 'Logging in...' : 'Creating account...';
      
      const endpoint = isLoginMode ? '/login' : '/register';
      const bodyData = isLoginMode 
        ? `username=${encodeURIComponent(formData.username)}&password=${encodeURIComponent(formData.password)}`
        : `username=${encodeURIComponent(formData.username)}&email=${encodeURIComponent(formData.email)}&password=${encodeURIComponent(formData.password)}`;
      
      fetch(endpoint, {
        method: 'POST',
        headers: { 'Content-Type': 'application/x-www-form-urlencoded' },
        body: bodyData
      })
      .then(response => response.ok ? response.text() : Promise.reject('Request failed'))
      .then(data => {
        if (data.includes('success') || (isLoginMode && data.includes('dashboard'))) {
          messageDiv.innerHTML = `<div class="success">${isLoginMode ? 'Login' : 'Registration'} successful!</div>`;
          logActivity(isLoginMode ? 'LOGIN_SUCCESS' : 'REGISTER_SUCCESS', { username: formData.username });
          
          setTimeout(() => {
            if (isLoginMode) {
              window.location.href = '/dashboard';
            } else {
              toggleForm();
              document.getElementById('username').value = formData.username;
            }
          }, isLoginMode ? 1000 : 2000);
        } else {
          throw new Error('Invalid response');
        }
      })
      .catch(error => {
        if (isLoginMode) loginAttempts++;
        messageDiv.innerHTML = `<div class="error">${isLoginMode ? 'Invalid credentials' : 'Registration failed'}</div>`;
        logActivity(isLoginMode ? 'LOGIN_FAILED' : 'REGISTER_FAILED', { username: formData.username });
      })
      .finally(() => {
        if (!data || !data.includes('success')) {
          submitBtn.disabled = false;
          submitBtn.textContent = isLoginMode ? 'Login' : 'Create Account';
          submitBtn.classList.remove('loading');
        }
      });
    });
    
    // ESP32 system ready
    console.log('ESP32 Flood Monitor Login System Ready');
  </script>
</body>
</html>
)rawliteral";