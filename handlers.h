#ifndef HANDLERS_H
#define HANDLERS_H

#include <Arduino.h>
#include "settings.h"
#include "animations.h"
#include "display.h"
#include "wifi.h"
#include "webserver.h"

// Build Information
#define HANDLERS_VERSION "1.0.0"
#define HANDLERS_BUILD_DATE "2025-05-11 07:46:45"
#define HANDLERS_AUTHOR "Brodot23"

// Event Types and Constants
#define MAX_EVENT_HANDLERS 20
#define MAX_EVENT_QUEUE 50
#define EVENT_TIMEOUT 5000  // 5 seconds in milliseconds

// Event Priority Levels
typedef enum {
    PRIORITY_LOW = 0,
    PRIORITY_NORMAL = 1,
    PRIORITY_HIGH = 2,
    PRIORITY_CRITICAL = 3
} EventPriority;

// Event Types
typedef enum {
    // System Events
    EVENT_SYSTEM_STARTUP,
    EVENT_SYSTEM_SHUTDOWN,
    EVENT_SYSTEM_RESET,
    EVENT_SYSTEM_ERROR,
    
    // Hardware Events
    EVENT_BUTTON_PRESSED,
    EVENT_BUTTON_RELEASED,
    EVENT_BUTTON_LONG_PRESS,
    EVENT_BUTTON_DOUBLE_PRESS,
    
    // Animation Events
    EVENT_ANIMATION_START,
    EVENT_ANIMATION_STOP,
    EVENT_ANIMATION_COMPLETE,
    EVENT_ANIMATION_ERROR,
    
    // Display Events
    EVENT_DISPLAY_UPDATE,
    EVENT_DISPLAY_CLEAR,
    EVENT_DISPLAY_ERROR,
    
    // Network Events
    EVENT_WIFI_CONNECTED,
    EVENT_WIFI_DISCONNECTED,
    EVENT_WIFI_AP_START,
    EVENT_WIFI_AP_STOP,
    
    // Server Events
    EVENT_SERVER_START,
    EVENT_SERVER_STOP,
    EVENT_CLIENT_CONNECTED,
    EVENT_CLIENT_DISCONNECTED,
    
    // Pattern Events
    EVENT_PATTERN_CHANGE,
    EVENT_PATTERN_COMPLETE,
    EVENT_PATTERN_ERROR,
    
    // Mode Events
    EVENT_MODE_CHANGE,
    EVENT_MODE_UPDATE,
    EVENT_MODE_ERROR,
    
    // Configuration Events
    EVENT_CONFIG_CHANGED,
    EVENT_CONFIG_SAVED,
    EVENT_CONFIG_RESET,
    EVENT_CONFIG_ERROR
} EventType;

// Event Data Structure
typedef struct {
    EventType type;
    EventPriority priority;
    unsigned long timestamp;
    void* data;
    size_t dataSize;
} Event;

// Event Handler Function Type
typedef void (*EventHandler)(const Event* event);

// Event Handler Registration Structure
typedef struct {
    EventType type;
    EventHandler handler;
    EventPriority priority;
    bool enabled;
} HandlerRegistration;

// Event Queue Structure
typedef struct {
    Event events[MAX_EVENT_QUEUE];
    int head;
    int tail;
    int count;
} EventQueue;

// External Variables
extern EventQueue eventQueue;
extern HandlerRegistration handlers[MAX_EVENT_HANDLERS];
extern volatile bool eventProcessingEnabled;

// Function Declarations

// Event Queue Management
void initEventSystem();
bool queueEvent(EventType type, EventPriority priority, void* data, size_t dataSize);
bool dequeueEvent(Event* event);
void clearEventQueue();
bool isEventQueueFull();
bool isEventQueueEmpty();
int getEventQueueSize();

// Event Handler Management
bool registerEventHandler(EventType type, EventHandler handler, EventPriority priority);
bool unregisterEventHandler(EventType type, EventHandler handler);
void enableEventHandler(EventType type, EventHandler handler);
void disableEventHandler(EventType type, EventHandler handler);
void clearEventHandlers();

// Event Processing
void processEvents();
void processEvent(const Event* event);
void stopEventProcessing();
void resumeEventProcessing();
bool isEventProcessingEnabled();

// Default Event Handlers
void handleSystemStartup(const Event* event);
void handleSystemShutdown(const Event* event);
void handleSystemReset(const Event* event);
void handleSystemError(const Event* event);

// Button Event Handlers
void handleButtonPress(const Event* event);
void handleButtonRelease(const Event* event);
void handleButtonLongPress(const Event* event);
void handleButtonDoublePress(const Event* event);

// Animation Event Handlers
void handleAnimationStart(const Event* event);
void handleAnimationStop(const Event* event);
void handleAnimationComplete(const Event* event);
void handleAnimationError(const Event* event);

// Display Event Handlers
void handleDisplayUpdate(const Event* event);
void handleDisplayClear(const Event* event);
void handleDisplayError(const Event* event);

// Network Event Handlers
void handleWiFiConnected(const Event* event);
void handleWiFiDisconnected(const Event* event);
void handleWiFiAPStart(const Event* event);
void handleWiFiAPStop(const Event* event);

// Server Event Handlers
void handleServerStart(const Event* event);
void handleServerStop(const Event* event);
void handleClientConnected(const Event* event);
void handleClientDisconnected(const Event* event);

// Pattern Event Handlers
void handlePatternChange(const Event* event);
void handlePatternComplete(const Event* event);
void handlePatternError(const Event* event);

// Mode Event Handlers
void handleModeChange(const Event* event);
void handleModeUpdate(const Event* event);
void handleModeError(const Event* event);

// Configuration Event Handlers
void handleConfigChanged(const Event* event);
void handleConfigSaved(const Event* event);
void handleConfigReset(const Event* event);
void handleConfigError(const Event* event);

// Utility Functions
void printEventInfo(const Event* event);
const char* getEventTypeName(EventType type);
const char* getPriorityName(EventPriority priority);
unsigned long getEventAge(const Event* event);
bool isEventExpired(const Event* event);

// Debug Functions
void enableEventDebug(bool enable);
void debugEvent(const Event* event);
void printEventQueue();
void printEventHandlers();

#endif // HANDLERS_H