// WebSocket Configuration
let ws;
const serverUrl = `ws://${window.location.hostname}:81`;
let reconnectAttempts = 0;
const maxReconnectAttempts = 5;
let reconnectTimeout;

// Constants
const TOAST_DURATION = 3000;
const RECONNECT_DELAY = 2000;
const API_ENDPOINTS = {
    GENERAL: '/api/general-settings',
    TEXT: '/api/text-settings',
    IDLE: '/api/idle-settings',
    SEIN_REM: '/api/sein-rem-settings',
    BRIGHTNESS: '/api/brightness',
    WIFI: '/api/wifi-settings'
};

// WebSocket Connection Management
function initializeWebSocket() {
    ws = new WebSocket(serverUrl);
    
    ws.onopen = () => {
        console.log('WebSocket Connected');
        updateConnectionStatus(true);
        reconnectAttempts = 0;
        requestInitialState();
    };
    
    ws.onclose = () => {
        console.log('WebSocket Disconnected');
        updateConnectionStatus(false);
        handleReconnection();
    };
    
    ws.onerror = (error) => {
        console.error('WebSocket Error:', error);
        showToast('Koneksi error. Mencoba menghubungkan ulang...', 'error');
    };
    
    ws.onmessage = handleWebSocketMessage;
}

function handleReconnection() {
    if (reconnectAttempts < maxReconnectAttempts) {
        reconnectAttempts++;
        showToast(`Mencoba menghubungkan ulang... (${reconnectAttempts}/${maxReconnectAttempts})`, 'warning');
        reconnectTimeout = setTimeout(initializeWebSocket, RECONNECT_DELAY);
    } else {
        showToast('Gagal terhubung ke perangkat. Silakan refresh halaman.', 'error');
    }
}

function updateConnectionStatus(isConnected) {
    const statusElement = document.getElementById('connectionStatus');
    const statusIndicator = document.querySelector('.status-indicator');
    
    if (statusElement && statusIndicator) {
        statusElement.textContent = isConnected ? 'Terhubung' : 'Terputus';
        statusIndicator.className = `status-indicator status-${isConnected ? 'online' : 'offline'}`;
    }
}

// WebSocket Message Handler
function handleWebSocketMessage(event) {
    try {
        const data = JSON.parse(event.data);
        
        switch (data.type) {
            case 'state':
                updateUIState(data.payload);
                break;
            case 'error':
                showToast(data.message, 'error');
                break;
            case 'success':
                showToast(data.message, 'success');
                break;
            default:
                console.log('Received:', data);
        }
    } catch (error) {
        console.error('Error parsing message:', error);
    }
}

// Settings Management
function saveGeneralSettings() {
    const displayMode = document.getElementById('displayMode').value;
    const gapDuration = parseInt(document.getElementById('gapDuration').value);
    
    const data = {
        displayMode,
        gapDuration
    };
    
    sendWebSocketMessage('setGeneralSettings', data);
    saveToAPI(API_ENDPOINTS.GENERAL, data);
}

function saveTextSettings() {
    const text = document.getElementById('textInput').value;
    const isBold = document.getElementById('boldText').checked;
    const speed = parseInt(document.getElementById('textSpeed').value);
    
    const data = {
        text,
        bold: isBold,
        speed
    };
    
    sendWebSocketMessage('setTextSettings', data);
    saveToAPI(API_ENDPOINTS.TEXT, data);
}

function saveIdleSettings() {
    const selectedEffects = Array.from(
        document.querySelectorAll('#idleEffectForm input[type="checkbox"]:checked')
    ).map(checkbox => parseInt(checkbox.value));
    
    const duration = parseInt(document.getElementById('idleDuration').value);
    
    const data = {
        selectedEffects,
        duration
    };
    
    sendWebSocketMessage('setIdleSettings', data);
    saveToAPI(API_ENDPOINTS.IDLE, data);
}

function saveSeinRemSettings() {
    const data = {
        seinMode: parseInt(document.getElementById('seinMode').value),
        remMode: parseInt(document.getElementById('remMode').value),
        seinSpeed: parseInt(document.getElementById('seinSpeed').value),
        remSpeed: parseInt(document.getElementById('remSpeed').value)
    };
    
    sendWebSocketMessage('setSeinRemSettings', data);
    saveToAPI(API_ENDPOINTS.SEIN_REM, data);
}

function saveBrightness() {
    const brightness = parseInt(document.getElementById('brightness').value);
    sendWebSocketMessage('setBrightness', { brightness });
    saveToAPI(API_ENDPOINTS.BRIGHTNESS, { brightness });
}

function saveWiFi() {
    const ssid = document.getElementById('ssid').value;
    const password = document.getElementById('password').value;
    
    if (!ssid) {
        showToast('SSID tidak boleh kosong!', 'error');
        return;
    }
    
    const data = { ssid, password };
    sendWebSocketMessage('setWiFi', data);
    saveToAPI(API_ENDPOINTS.WIFI, data);
}

// API Communication
async function saveToAPI(endpoint, data) {
    try {
        const response = await fetch(endpoint, {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify(data)
        });
        
        if (!response.ok) {
            throw new Error('Network response was not ok');
        }
        
        const result = await response.json();
        showToast(result.message || 'Pengaturan berhasil disimpan!', 'success');
    } catch (error) {
        console.error('Error saving settings:', error);
        showToast('Gagal menyimpan pengaturan!', 'error');
    }
}

async function loadSavedSettings() {
    try {
        const responses = await Promise.all([
            fetch(API_ENDPOINTS.GENERAL),
            fetch(API_ENDPOINTS.TEXT),
            fetch(API_ENDPOINTS.IDLE),
            fetch(API_ENDPOINTS.SEIN_REM),
            fetch(API_ENDPOINTS.BRIGHTNESS)
        ]);
        
        const [general, text, idle, seinRem, brightness] = await Promise.all(
            responses.map(response => response.json())
        );
        
        updateUIState({
            general,
            text,
            idle,
            seinRem,
            brightness
        });
    } catch (error) {
        console.error('Error loading settings:', error);
        showToast('Gagal memuat pengaturan!', 'error');
    }
}

// UI Update Functions
function updateUIState(state) {
    if (state.general) {
        document.getElementById('displayMode').value = state.general.displayMode;
        document.getElementById('gapDuration').value = state.general.gapDuration;
    }
    
    if (state.text) {
        document.getElementById('textInput').value = state.text.text;
        document.getElementById('boldText').checked = state.text.bold;
        document.getElementById('textSpeed').value = state.text.speed;
    }
    
    if (state.idle) {
        const checkboxes = document.querySelectorAll('#idleEffectForm input[type="checkbox"]');
        checkboxes.forEach(checkbox => {
            checkbox.checked = state.idle.selectedEffects.includes(parseInt(checkbox.value));
        });
        document.getElementById('idleDuration').value = state.idle.duration;
    }
    
    if (state.seinRem) {
        document.getElementById('seinMode').value = state.seinRem.seinMode;
        document.getElementById('remMode').value = state.seinRem.remMode;
        document.getElementById('seinSpeed').value = state.seinRem.seinSpeed;
        document.getElementById('remSpeed').value = state.seinRem.remSpeed;
    }
    
    if (state.brightness) {
        document.getElementById('brightness').value = state.brightness.brightness;
    }
}

// Utility Functions
function sendWebSocketMessage(command, data) {
    if (ws && ws.readyState === WebSocket.OPEN) {
        ws.send(JSON.stringify({
            command,
            data
        }));
    } else {
        showToast('Tidak ada koneksi ke perangkat!', 'error');
    }
}

function showToast(message, type = 'info') {
    const toast = document.createElement('div');
    toast.className = `toast ${type}`;
    toast.textContent = message;
    
    document.body.appendChild(toast);
    
    setTimeout(() => {
        toast.style.opacity = '0';
        setTimeout(() => {
            document.body.removeChild(toast);
        }, 300);
    }, TOAST_DURATION);
}

// Event Listeners
document.addEventListener('DOMContentLoaded', () => {
    initializeWebSocket();
    loadSavedSettings();
    
    // Add input validation and real-time updates
    document.getElementById('brightness').addEventListener('input', function() {
        this.value = Math.max(0, Math.min(15, this.value));
    });
    
    document.getElementById('textSpeed').addEventListener('input', function() {
        this.value = Math.max(1, Math.min(1000, this.value));
    });
});

// Export functions for use in HTML
window.saveGeneralSettings = saveGeneralSettings;
window.saveTextSettings = saveTextSettings;
window.saveIdleSettings = saveIdleSettings;
window.saveSeinRemSettings = saveSeinRemSettings;
window.saveBrightness = saveBrightness;
window.saveWiFi = saveWiFi;