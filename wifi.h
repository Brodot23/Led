#ifndef WIFI_H
#define WIFI_H

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DNSServer.h>
#include <WiFiManager.h>
#include "settings.h"

// Build Information
#define WIFI_VERSION "1.0.0"
#define WIFI_BUILD_DATE "2025-05-11 07:38:25"
#define WIFI_AUTHOR "Brodot23"

// WiFi Configuration
#define DEFAULT_AP_SSID "StopLamp-Config"     // Default Access Point SSID
#define DEFAULT_AP_PASSWORD "12345678"         // Default Access Point Password
#define CONFIG_PORTAL_TIMEOUT 180              // Timeout for configuration portal (in seconds)
#define CONNECTION_RETRY_DELAY 5000            // Delay between connection attempts (in milliseconds)
#define MAX_CONNECTION_ATTEMPTS 10             // Maximum number of connection attempts

// WiFi Manager Custom Parameters
#define CUSTOM_PARAM_COUNT 5                   // Number of custom parameters
#define PARAM_LENGTH 32                        // Maximum length of parameter values

// WiFi Status
typedef enum {
    WIFI_STATUS_DISCONNECTED,
    WIFI_STATUS_CONNECTING,
    WIFI_STATUS_CONNECTED,
    WIFI_STATUS_AP_MODE,
    WIFI_STATUS_CONFIG_MODE,
    WIFI_STATUS_ERROR
} WifiStatus;

// WiFi Configuration Structure
typedef struct {
    char ssid[PARAM_LENGTH];
    char password[PARAM_LENGTH];
    char deviceName[PARAM_LENGTH];
    bool apMode;
    bool configMode;
    uint8_t connectionAttempts;
    WifiStatus status;
    unsigned long lastConnectionAttempt;
} WifiConfig;

// Custom Parameters Structure
typedef struct {
    char deviceId[PARAM_LENGTH];
    char mqttServer[PARAM_LENGTH];
    char mqttPort[6];
    char mqttUser[PARAM_LENGTH];
    char mqttPassword[PARAM_LENGTH];
} CustomParams;

// External Variables
extern WifiConfig wifiConfig;
extern CustomParams customParams;
extern WiFiManager wifiManager;

// Function Declarations

// Initialization Functions
void initWiFi();
void resetWiFi();
void configModeCallback(WiFiManager *myWiFiManager);
void saveConfigCallback();

// Connection Management
bool connectWiFi();
void startAP();
void stopAP();
void handleConnection();
void checkConnection();

// Configuration Functions
void setupConfigPortal();
void configureDevice();
void saveConfiguration();
void loadConfiguration();
void resetConfiguration();

// Status Functions
WifiStatus getWiFiStatus();
bool isConnected();
bool isAPMode();
bool isConfigMode();
int32_t getSignalStrength();
uint8_t getConnectionQuality();

// Parameter Management
void addCustomParameters();
void updateCustomParameters();
bool validateParameters();
void clearParameters();

// Network Information
IPAddress getLocalIP();
IPAddress getGatewayIP();
String getMACAddress();
String getSSID();
int32_t getRSSI();

// Utility Functions
void printWiFiStatus();
void printNetworkInfo();
bool testConnection();
void scanNetworks();
void handleDNS();

// Event Handlers
void onStationConnected(const WiFiEventStationModeConnected& evt);
void onStationDisconnected(const WiFiEventStationModeDisconnected& evt);
void onStationGotIP(const WiFiEventStationModeGotIP& evt);
void onAPModeStationConnected(const WiFiEventSoftAPModeStationConnected& evt);
void onAPModeStationDisconnected(const WiFiEventSoftAPModeStationDisconnected& evt);

// Debug Functions
void enableDebug(bool enable);
void debugMessage(const char* message);
void logWiFiEvent(const char* event);

#endif // WIFI_H