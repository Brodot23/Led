#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <ESP8266WebServer.h>
#include <ArduinoJson.h>
#include "wifi.h"
#include "settings.h"
#include "animations.h"

// Build Information
#define WEBSERVER_VERSION "1.0.0"
#define WEBSERVER_BUILD_DATE "2025-05-11 07:41:45"
#define WEBSERVER_AUTHOR "Brodot23"

// Server Configuration
#define SERVER_PORT 80
#define MAX_ENDPOINTS 20
#define JSON_BUFFER_SIZE 1024
#define MAX_HEADER_LENGTH 128
#define API_VERSION "v1"

// HTTP Response Codes
#define HTTP_OK 200
#define HTTP_CREATED 201
#define HTTP_BAD_REQUEST 400
#define HTTP_UNAUTHORIZED 401
#define HTTP_FORBIDDEN 403
#define HTTP_NOT_FOUND 404
#define HTTP_SERVER_ERROR 500

// Authentication
#define AUTH_ENABLED true
#define AUTH_TOKEN_LENGTH 32
#define MAX_AUTH_ATTEMPTS 3
#define AUTH_TIMEOUT 3600 // 1 hour in seconds

// CORS Configuration
#define CORS_ENABLED true
#define ALLOWED_ORIGINS "*"
#define ALLOWED_METHODS "GET, POST, PUT, DELETE, OPTIONS"
#define ALLOWED_HEADERS "Content-Type, Authorization"

// Server Status
typedef enum {
    SERVER_STATUS_STOPPED,
    SERVER_STATUS_STARTING,
    SERVER_STATUS_RUNNING,
    SERVER_STATUS_ERROR
} ServerStatus;

// Request Handler Type
typedef std::function<void(void)> RequestHandler;

// Server Configuration Structure
typedef struct {
    uint16_t port;
    bool authEnabled;
    bool corsEnabled;
    ServerStatus status;
    char authToken[AUTH_TOKEN_LENGTH + 1];
    uint8_t authAttempts;
    unsigned long lastAuthReset;
} ServerConfig;

// Endpoint Structure
typedef struct {
    const char* path;
    const char* method;
    RequestHandler handler;
    bool requiresAuth;
} Endpoint;

// External Variables
extern ESP8266WebServer server;
extern ServerConfig serverConfig;
extern Endpoint endpoints[MAX_ENDPOINTS];

// Function Declarations

// Server Initialization and Control
void initWebServer();
void startServer();
void stopServer();
void restartServer();
void handleClient();

// Endpoint Management
void registerEndpoint(const char* path, const char* method, RequestHandler handler, bool requiresAuth);
void unregisterEndpoint(const char* path, const char* method);
void setupDefaultEndpoints();
void clearEndpoints();

// Request Handlers
void handleRoot();
void handleNotFound();
void handleOptions();
void handleAPI();

// API Endpoints
void handleGetStatus();
void handleSetMode();
void handleSetBrightness();
void handleSetAnimation();
void handleSetPattern();
void handleGetConfig();
void handleUpdateConfig();
void handleResetConfig();

// Authentication
bool checkAuthentication();
void generateAuthToken();
void resetAuthAttempts();
bool validateAuthToken(String token);

// CORS Handlers
void setupCORS();
void handleCORS();
bool isOriginAllowed(String origin);

// Response Helpers
void sendJsonResponse(int code, JsonDocument& doc);
void sendErrorResponse(int code, const char* message);
void sendSuccessResponse(const char* message);

// Request Parsing
bool parseJsonBody(JsonDocument& doc);
String getRequestHeader(const char* headerName);
bool validateRequestBody(JsonDocument& doc, const char* requiredFields[], size_t numFields);

// Utility Functions
void printServerStatus();
void logRequest(const char* method, const char* path);
void debugRequest(const char* message);
String getContentType(String filename);

// Security Functions
void setupSecurity();
void checkAuthTimeout();
void blockIP(IPAddress ip);
bool isIPBlocked(IPAddress ip);

// Event Handlers
void onServerStart();
void onServerStop();
void onClientConnect(IPAddress ip);
void onClientDisconnect(IPAddress ip);
void onAuthFailure(IPAddress ip);

// API Route Handlers
namespace APIHandlers {
    // Status and Control
    void getSystemStatus();
    void setOperatingMode();
    void getDeviceInfo();
    
    // Animation Control
    void getCurrentAnimation();
    void setAnimationMode();
    void setAnimationSpeed();
    void setAnimationBrightness();
    
    // Pattern Control
    void getCurrentPattern();
    void setPatternMode();
    void uploadCustomPattern();
    
    // Configuration
    void getConfiguration();
    void updateConfiguration();
    void resetToDefaults();
    
    // WiFi Management
    void getWiFiStatus();
    void scanNetworks();
    void updateWiFiSettings();
}

#endif // WEBSERVER_H