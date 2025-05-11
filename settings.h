#ifndef SETTINGS_H
#define SETTINGS_H

// Build Information
#define VERSION "STOPLAMP BRODOT v2.0"
#define BUILD_DATE_TIME "2025-05-11 07:08:54"    // Current Date and Time (UTC - YYYY-MM-DD HH:MM:SS)
#define BUILD_DATE "2025-05-11"                  // YYYY-MM-DD
#define BUILD_TIME "07:08:54"                    // HH:MM:SS
#define AUTHOR "Brodot23"                        // Current User's Login
#define BUILD_SIGNATURE "Built by Brodot23 on 2025-05-11 07:08:54 UTC"
#define BUILD_TIMESTAMP 1715396934               // Unix timestamp

// Debug Mode
//#define DEBUG_MODE

// Pin Definitions
#define DIN_PIN 13          // Data in pin for LED matrix
#define CLK_PIN 14          // Clock pin for LED matrix
#define CS_PIN  15          // Chip select pin for LED matrix
#define BRAKE_PIN 4         // Brake input pin
#define SEIN_LEFT_PIN 5     // Left sein input pin
#define SEIN_RIGHT_PIN 16   // Right sein input pin

// Definisi EEPROM addresses
#define EEPROM_BRIGHTNESS_ADDR 0
#define EEPROM_PATTERN_ADDR 1
#define EEPROM_MODE_ADDR 2
#define EEPROM_INITIALIZED_ADDR 10
#define EEPROM_INITIALIZED_KEY 0xAA

// System Constants
#define MAX_TEXT_LENGTH 100
#define ANIMATION_COUNT 60
#define MAX_BRIGHTNESS 15
#define MIN_BRIGHTNESS 0
#define MAX_SPEED 1000
#define MIN_SPEED 50
#define SETTINGS_SIGNATURE 0xBD230205  // BRODOT23 signature

// Timing Constants
#define DEFAULT_SCROLL_SPEED 100
#define DEFAULT_ANIMATION_SPEED 150
#define DEFAULT_SEIN_SPEED 500
#define DEFAULT_BRAKE_SPEED 150
#define BLINK_INTERVAL 150
#define FADE_STEP_TIME 50
#define EMERGENCY_FLASH_TIME 75
#define PROGRESSIVE_STEP_TIME 100

// Display Modes
#define MODE_TEXT 0
#define MODE_ANIMATION 1
#define MODE_COMBINED 2

// Brake Modes
#define BRAKE_MODE_FULL 0
#define BRAKE_MODE_PROGRESSIVE 1
#define BRAKE_MODE_WARNING 2
#define BRAKE_MODE_EMERGENCY 3
#define BRAKE_MODE_SMOOTH 4
#define BRAKE_MODE_STOP_TEXT 5

// Sein Modes
#define SEIN_MODE_BASIC 0
#define SEIN_MODE_EDGE 1
#define SEIN_MODE_PROGRESSIVE 2
#define SEIN_MODE_PULSE 3
#define SEIN_MODE_DOUBLE 4
#define SEIN_MODE_RUNNING 5

// Definisi interval waktu
#define SEIN_INTERVAL 500
#define HAZARD_INTERVAL 500
#define BRAKE_PULSE_INTERVAL 50
#define ANIMATION_INTERVAL 100

// Mode operasi stoplamp
#define MODE_NORMAL 0
#define MODE_HAZARD 1
#define MODE_POLICE 2
#define MODE_STROBE 3
#define MODE_RUNNING 4
#define MODE_NIGHTRIDER 5

// State definitions
#define STATE_OFF 0
#define STATE_ON 1
#define STATE_BLINK 2

// Pattern index definitions
#define PATTERN_DEFAULT 0
#define PATTERN_SEIN_LEFT 1
#define PATTERN_SEIN_RIGHT 2
#define PATTERN_BRAKE 3
#define PATTERN_HAZARD 4
#define PATTERN_POLICE 5

// Priority Levels
#define PRIORITY_IDLE 0
#define PRIORITY_BRAKE 1
#define PRIORITY_SEIN 2

// EEPROM Addresses
#define SETTINGS_BASE_ADDR 0
#define ANIMATION_ADDR 32
#define SEIN_SETTINGS_ADDR 64
#define BRAKE_SETTINGS_ADDR 96
#define CUSTOM_TEXT_ADDR 128

// Matrix Constants
#define MATRIX_COUNT 8
#define MATRIX_ROWS 8
#define MATRIX_COLS 32
#define CHAR_WIDTH 8

// Animation Direction
#define DIRECTION_LEFT 0
#define DIRECTION_RIGHT 1
#define DIRECTION_UP 2
#define DIRECTION_DOWN 3

// Error Codes
#define ERROR_NONE 0
#define ERROR_MATRIX_INIT 1
#define ERROR_EEPROM_READ 2
#define ERROR_EEPROM_WRITE 3
#define ERROR_INVALID_MODE 4
#define ERROR_INVALID_PATTERN 5

// Control Flags
#define FLAG_NONE 0x00
#define FLAG_UPDATE_DISPLAY 0x01
#define FLAG_SAVE_SETTINGS 0x02
#define FLAG_ANIMATION_ACTIVE 0x04

#endif // SETTINGS_H