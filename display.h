#ifndef DISPLAY_H
#define DISPLAY_H

#include "settings.h"
#include "animations.h"
#include <MaxMatrix.h>

// Build Information
#define DISPLAY_VERSION "1.0.0"
#define DISPLAY_BUILD_DATE "2025-05-11 07:33:40"
#define DISPLAY_AUTHOR "Brodot23"

// Display Matrix Configuration
#define MATRIX_COUNT 4      // Jumlah modul LED matrix yang digunakan
#define MATRIX_INTENSITY 8  // Intensitas brightness LED (0-15)

// Pin Definitions for LED Matrix
#define MATRIX_DIN_PIN 10   // Data input pin
#define MATRIX_CS_PIN  11   // Chip select pin
#define MATRIX_CLK_PIN 12   // Clock pin

// Matrix Dimensions
#define MATRIX_WIDTH  32    // Total lebar display (8 x MATRIX_COUNT)
#define MATRIX_HEIGHT 8     // Tinggi display

// Display Buffer
extern uint8_t displayBuffer[MATRIX_WIDTH];

// Display State
typedef struct {
    uint8_t brightness;     // Current brightness level (0-15)
    bool isInverted;        // Display inversion state
    bool isEnabled;         // Display enable/disable state
    uint8_t scrollSpeed;    // Scroll speed for text/pattern
    uint8_t currentEffect;  // Current visual effect being applied
} DisplayState;

// Display Effects
typedef enum {
    EFFECT_NONE,
    EFFECT_FADE_IN,
    EFFECT_FADE_OUT,
    EFFECT_SCROLL_LEFT,
    EFFECT_SCROLL_RIGHT,
    EFFECT_BLINK,
    EFFECT_PULSE,
    EFFECT_WAVE,
    EFFECT_SPARKLE
} DisplayEffect;

// Function Declarations

// Initialization Functions
void initDisplay();
void resetDisplay();
void clearDisplay();

// Basic Display Control
void setPixel(uint8_t x, uint8_t y, bool state);
void setColumn(uint8_t col, uint8_t value);
void setRow(uint8_t row, uint8_t value);
void invertDisplay(bool invert);
void enableDisplay(bool enable);

// Pattern Display Functions
void displayPattern(const uint8_t* pattern, uint8_t width, uint8_t height);
void displayScrollingPattern(const uint8_t* pattern, uint8_t width, uint8_t height, uint8_t speed);
void displayAnimationFrame(const AnimationState* state);

// Brightness Control
void setBrightness(uint8_t level);
void fadeTo(uint8_t targetLevel, uint16_t duration);
uint8_t getBrightness();

// Effect Control
void startEffect(DisplayEffect effect);
void stopEffect();
void updateEffect();
bool isEffectActive();

// Buffer Management
void clearBuffer();
void updateBuffer();
void commitBuffer();
void scrollBufferLeft(uint8_t positions);
void scrollBufferRight(uint8_t positions);

// Status Functions
bool isDisplayEnabled();
bool isDisplayInverted();
DisplayEffect getCurrentEffect();

// Utility Functions
void rotateDisplay(uint8_t angle);
void mirrorDisplay(bool horizontal, bool vertical);
void shiftDisplay(int8_t x, int8_t y);

// Test Patterns
void displayTestPattern();
void runDisplayDiagnostic();

#endif // DISPLAY_H