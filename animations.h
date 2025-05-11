#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#include "settings.h"
#include <stdint.h>

// Build Information
#define ANIMATIONS_VERSION "1.0.0"
#define ANIMATIONS_BUILD_DATE "2025-05-11 07:17:43"
#define ANIMATIONS_AUTHOR "Brodot23"

// Animation Buffer Size
#define MAX_ANIMATION_FRAMES 32
#define MAX_ANIMATION_PATTERNS 16

// ===== ANIMASI LAMPU REM =====
// Pattern: Full Brake (Rem Penuh)
const uint8_t BRAKE_FULL_PATTERN[] = {
    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B11111111
};

// Pattern: Progressive Brake (Rem Bertahap)
const uint8_t BRAKE_PROGRESSIVE_PATTERN[] = {
    B00000000, // Frame 1
    B11111111,
    B00000000,
    B11111111,
    B00000000,
    B11111111,
    B00000000,
    B11111111  // Frame 8
};

// Pattern: Brake Warning (Peringatan Rem)
const uint8_t BRAKE_WARNING_PATTERN[] = {
    B10101010,
    B01010101,
    B10101010,
    B01010101,
    B10101010,
    B01010101,
    B10101010,
    B01010101
};

// ===== ANIMASI LAMPU SEIN =====
// Pattern: Left Sein Basic (Sein Kiri Dasar)
const uint8_t SEIN_LEFT_BASIC_PATTERN[] = {
    B10000000, // Frame 1
    B11000000,
    B11100000,
    B11110000,
    B11100000,
    B11000000,
    B10000000,
    B00000000  // Frame 8
};

// Pattern: Right Sein Basic (Sein Kanan Dasar)
const uint8_t SEIN_RIGHT_BASIC_PATTERN[] = {
    B00000001, // Frame 1
    B00000011,
    B00000111,
    B00001111,
    B00000111,
    B00000011,
    B00000001,
    B00000000  // Frame 8
};

// Pattern: Sein Progressive (Sein Bertahap)
const uint8_t SEIN_PROGRESSIVE_PATTERN[] = {
    B10000001, // Frame 1
    B11000011,
    B11100111,
    B11111111,
    B11100111,
    B11000011,
    B10000001,
    B00000000  // Frame 8
};

// ===== ANIMASI LAMPU HAZARD =====
// Pattern: Hazard Basic (Hazard Dasar)
const uint8_t HAZARD_BASIC_PATTERN[] = {
    B11111111, // Frame 1
    B01111110,
    B00111100,
    B00011000,
    B00011000,
    B00111100,
    B01111110,
    B11111111  // Frame 8
};

// Pattern: Hazard Warning (Peringatan Hazard)
const uint8_t HAZARD_WARNING_PATTERN[] = {
    B10101010, // Frame 1
    B01010101,
    B10101010,
    B01010101,
    B10101010,
    B01010101,
    B10101010,
    B01010101  // Frame 8
};

// Pattern: Hazard Progressive (Hazard Bertahap)
const uint8_t HAZARD_PROGRESSIVE_PATTERN[] = {
    B11111111, // Frame 1
    B00000000,
    B11111111,
    B00000000,
    B11111111,
    B00000000,
    B11111111,
    B00000000  // Frame 8
};

// Animation Frame Counts
#define BRAKE_FRAMES 1
#define BRAKE_PROGRESSIVE_FRAMES 8
#define BRAKE_WARNING_FRAMES 8
#define SEIN_LEFT_FRAMES 8
#define SEIN_RIGHT_FRAMES 8
#define SEIN_PROGRESSIVE_FRAMES 8
#define HAZARD_FRAMES 8
#define HAZARD_WARNING_FRAMES 8
#define HAZARD_PROGRESSIVE_FRAMES 8

// Animation Timing (in milliseconds)
#define BRAKE_DELAY 100
#define BRAKE_PROGRESSIVE_DELAY 50
#define BRAKE_WARNING_DELAY 75
#define SEIN_DELAY 500
#define SEIN_PROGRESSIVE_DELAY 100
#define HAZARD_DELAY 500
#define HAZARD_WARNING_DELAY 75
#define HAZARD_PROGRESSIVE_DELAY 100

// Animation Types
typedef enum {
    ANIM_NONE,
    // Brake Animations
    ANIM_BRAKE_FULL,
    ANIM_BRAKE_PROGRESSIVE,
    ANIM_BRAKE_WARNING,
    // Sein Animations
    ANIM_SEIN_LEFT_BASIC,
    ANIM_SEIN_RIGHT_BASIC,
    ANIM_SEIN_PROGRESSIVE,
    // Hazard Animations
    ANIM_HAZARD_BASIC,
    ANIM_HAZARD_WARNING,
    ANIM_HAZARD_PROGRESSIVE
} AnimationType;

// Animation Direction
typedef enum {
    DIR_NONE,
    DIR_LEFT,
    DIR_RIGHT,
    DIR_BOTH,
    DIR_CENTER,
    DIR_ALTERNATE
} AnimationDirection;

// Animation Effects
typedef enum {
    EFFECT_NONE,
    EFFECT_FADE,
    EFFECT_BLINK,
    EFFECT_SLIDE,
    EFFECT_PULSE
} AnimationEffect;

// Animation State Structure
typedef struct {
    AnimationType type;
    AnimationDirection direction;
    AnimationEffect effect;
    uint8_t currentFrame;
    uint8_t totalFrames;
    uint16_t delay;
    uint8_t brightness;
    bool isActive;
    bool isReverse;
    bool isLooping;
    unsigned long lastUpdate;
} AnimationState;

// Function Prototypes
// Initialization
void initializeAnimation(AnimationState* state);
void resetAnimation(AnimationState* state);

// Animation Control
void startAnimation(AnimationState* state, AnimationType type);
void stopAnimation(AnimationState* state);
void pauseAnimation(AnimationState* state);
void resumeAnimation(AnimationState* state);
void updateAnimation(AnimationState* state);

// Animation Properties
void setAnimationSpeed(AnimationState* state, uint16_t delay);
void setAnimationDirection(AnimationState* state, AnimationDirection direction);
void setAnimationEffect(AnimationState* state, AnimationEffect effect);
void setAnimationBrightness(AnimationState* state, uint8_t brightness);
void setAnimationLooping(AnimationState* state, bool looping);

// Status Checks
bool isAnimationComplete(AnimationState* state);
bool isAnimationActive(AnimationState* state);
bool isAnimationPaused(AnimationState* state);

// Pattern Management
const uint8_t* getPatternForType(AnimationType type);
uint8_t getFrameCountForType(AnimationType type);
uint16_t getDelayForType(AnimationType type);

#endif // ANIMATIONS_H