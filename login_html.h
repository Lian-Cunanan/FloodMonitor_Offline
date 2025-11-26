#pragma once

const char login_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Flood Monitor - Login</title>
    <link rel="stylesheet" href="/style.css">
</head>
<body class="login-body">
    <div class="login-container">
        <div class="login-card">
            <div class="login-header">
                <div class="login-logo">
                    <span class="logo-icon">🌊</span>
                    <h1>Flood Monitor Pro</h1>
                </div>
                <p class="login-subtitle">Secure access to your monitoring system</p>
            </div>

            <div class="auth-tabs">
                <button class="tab-btn active" id="login-tab">Login</button>
                <button class="tab-btn" id="register-tab">Register</button>
            </div>

            <!-- Login Form -->
            <form class="auth-form" id="login-form">
                <div class="form-group">
                    <label for="login-username">Username</label>
                    <input type="text" id="login-username" name="username" required>
                </div>
                <div class="form-group">
                    <label for="login-password">Password</label>
                    <input type="password" id="login-password" name="password" required>
                </div>
                <button type="submit" class="auth-btn">
                    <span>Sign In</span>
                </button>
            </form>

            <!-- Register Form -->
            <form class="auth-form hidden" id="register-form">
                <div class="form-group">
                    <label for="reg-username">Username</label>
                    <input type="text" id="reg-username" name="username" required minlength="3" 
                           placeholder="Enter username">
                </div>
                <div class="form-group">
                    <label for="reg-email">Email</label>
                    <input type="email" id="reg-email" name="email" required 
                           placeholder="Enter email">
                </div>
                <div class="form-group">
                    <label for="reg-password">Password</label>
                    <input type="password" id="reg-password" name="password" required minlength="6"
                           placeholder="Enter password">
                </div>
                <div class="form-group">
                    <label for="reg-confirm">Confirm Password</label>
                    <input type="password" id="reg-confirm" name="confirm_password" required
                           placeholder="Confirm password">
                </div>
                <button type="submit" class="auth-btn">
                    <span>Create Account</span>
                </button>
            </form>

            <div class="alert-message hidden" id="alert-message">
                <span class="alert-text"></span>
            </div>
        </div>

        <div class="login-info">
            <div class="info-card">
                <h3>🔒 Secure Access</h3>
                <p>Your flood monitoring data is protected with enterprise-level security.</p>
            </div>
            <div class="info-card">
                <h3>📱 Real-time Monitoring</h3>
                <p>Access live sensor data and control systems from anywhere.</p>
            </div>
        </div>
    </div>

    <script>
document.addEventListener('DOMContentLoaded', function() {
    const loginTab = document.getElementById('login-tab');
    const registerTab = document.getElementById('register-tab');
    const loginForm = document.getElementById('login-form');
    const registerForm = document.getElementById('register-form');
    const alertMessage = document.getElementById('alert-message');
    
    // Tab switching
    loginTab.addEventListener('click', function() {
        loginTab.classList.add('active');
        registerTab.classList.remove('active');
        loginForm.classList.remove('hidden');
        registerForm.classList.add('hidden');
        hideAlert();
    });
    
    registerTab.addEventListener('click', function() {
        registerTab.classList.add('active');
        loginTab.classList.remove('active');
        registerForm.classList.remove('hidden');
        loginForm.classList.add('hidden');
        hideAlert();
    });
    
    // Login form
    loginForm.addEventListener('submit', async function(e) {
        e.preventDefault();
        
        const username = document.getElementById('login-username').value;
        const password = document.getElementById('login-password').value;
        
        if (!username || !password) {
            showAlert('Please fill in all fields', 'error');
            return;
        }
        
        showAlert('Signing in...', 'info');
        
        try {
            const response = await fetch('/auth/login', {
                method: 'POST',
                headers: { 'Content-Type': 'application/x-www-form-urlencoded' },
                body: `username=${encodeURIComponent(username)}&password=${encodeURIComponent(password)}`
            });
            
            const result = await response.json();
            
            if (result.success) {
                showAlert('Login successful! Redirecting...', 'success');
                setTimeout(() => window.location.href = '/', 1000);
            } else {
                showAlert(result.message, 'error');
            }
        } catch (error) {
            showAlert('Login failed. Please try again.', 'error');
        }
    });
    
    // Register form
    registerForm.addEventListener('submit', async function(e) {
        e.preventDefault();
        
        const username = document.getElementById('reg-username').value.trim();
        const email = document.getElementById('reg-email').value.trim();
        const password = document.getElementById('reg-password').value;
        const confirmPassword = document.getElementById('reg-confirm').value;
        
        console.log('Form data:', { username, email, password_len: password.length });
        
        if (!username || !email || !password || !confirmPassword) {
            showAlert('Please fill in all fields', 'error');
            return;
        }
        
        if (username.length < 3) {
            showAlert('Username must be at least 3 characters', 'error');
            return;
        }
        
        if (password.length < 6) {
            showAlert('Password must be at least 6 characters', 'error');
            return;
        }
        
        if (password !== confirmPassword) {
            showAlert('Passwords do not match', 'error');
            return;
        }
        
        showAlert('Creating account...', 'info');
        
        try {
            const response = await fetch('/auth/register', {
                method: 'POST',
                headers: { 'Content-Type': 'application/x-www-form-urlencoded' },
                body: `username=${encodeURIComponent(username)}&email=${encodeURIComponent(email)}&password=${encodeURIComponent(password)}`
            });
            
            const result = await response.json();
            console.log('Server response:', result);
            
            if (result.success) {
                showAlert('Account created successfully! Please login.', 'success');
                setTimeout(() => {
                    loginTab.click();
                    document.getElementById('login-username').value = username;
                }, 2000);
            } else {
                showAlert(result.message, 'error');
            }
        } catch (error) {
            console.error('Registration error:', error);
            showAlert('Registration failed. Please try again.', 'error');
        }
    });
    
    function showAlert(message, type) {
        alertMessage.className = `alert-message ${type}`;
        alertMessage.querySelector('.alert-text').textContent = message;
    }
    
    function hideAlert() {
        alertMessage.className = 'alert-message hidden';
    }
});
    </script>
</body>
</html>
)rawliteral";
