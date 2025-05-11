#include "animations.h"
#include "settings.h"
#include <Arduino.h>

// Build Information
#define ANIMATIONS_CPP_VERSION "1.0.0"
#define ANIMATIONS_CPP_BUILD_DATE "2025-05-11 07:29:50"
#define ANIMATIONS_CPP_AUTHOR "Brodot23"

// ===== IMPLEMENTASI FUNGSI INISIALISASI =====

void initializeAnimation(AnimationState* state) {
    state->type = ANIM_NONE;
    state->direction = DIR_NONE;
    state->effect = EFFECT_NONE;
    state->currentFrame = 0;
    state->totalFrames = 0;
    state->delay = 0;
    state->brightness = MAX_BRIGHTNESS;
    state->isActive = false;
    state->isReverse = false;
    state->isLooping = false;
    state->lastUpdate = 0;
}

void resetAnimation(AnimationState* state) {
    state->currentFrame = 0;
    state->lastUpdate = millis();
}

// ===== IMPLEMENTASI FUNGSI KONTROL ANIMASI =====

void startAnimation(AnimationState* state, AnimationType type) {
    state->type = type;
    state->currentFrame = 0;
    state->totalFrames = getFrameCountForType(type);
    state->delay = getDelayForType(type);
    state->isActive = true;
    state->lastUpdate = millis();
    
    // Set default direction based on type
    switch(type) {
        case ANIM_SEIN_LEFT_BASIC:
            state->direction = DIR_LEFT;
            break;
        case ANIM_SEIN_RIGHT_BASIC:
            state->direction = DIR_RIGHT;
            break;
        case ANIM_HAZARD_BASIC:
        case ANIM_HAZARD_WARNING:
            state->direction = DIR_BOTH;
            break;
        default:
            state->direction = DIR_NONE;
    }
}

void stopAnimation(AnimationState* state) {
    state->isActive = false;
    state->currentFrame = 0;
}

void pauseAnimation(AnimationState* state) {
    state->isActive = false;
}

void resumeAnimation(AnimationState* state) {
    state->isActive = true;
    state->lastUpdate = millis();
}

// ===== IMPLEMENTASI FUNGSI ANIMATION PROPERTIES =====

void setAnimationSpeed(AnimationState* state, uint16_t delay) {
    state->delay = delay;
}

void setAnimationDirection(AnimationState* state, AnimationDirection direction) {
    state->direction = direction;
    // Reset frame jika arah berubah
    state->currentFrame = 0;
}

void setAnimationEffect(AnimationState* state, AnimationEffect effect) {
    state->effect = effect;
    // Reset frame jika efek berubah
    state->currentFrame = 0;
}

void setAnimationBrightness(AnimationState* state, uint8_t brightness) {
    state->brightness = constrain(brightness, MIN_BRIGHTNESS, MAX_BRIGHTNESS);
}

void setAnimationLooping(AnimationState* state, bool looping) {
    state->isLooping = looping;
}

// ===== IMPLEMENTASI FUNGSI UPDATE ANIMASI =====

void updateAnimation(AnimationState* state) {
    if (!state->isActive) return;
    
    unsigned long currentTime = millis();
    
    if (currentTime - state->lastUpdate >= state->delay) {
        state->lastUpdate = currentTime;
        
        // Update frame berdasarkan tipe animasi
        switch(state->type) {
            case ANIM_BRAKE_FULL:
                // Brake tetap menyala
                state->currentFrame = 0;
                break;
                
            case ANIM_BRAKE_PROGRESSIVE:
                updateProgressiveFrame(state);
                break;
                
            case ANIM_SEIN_LEFT_BASIC:
            case ANIM_SEIN_RIGHT_BASIC:
                updateSeinFrame(state);
                break;
                
            case ANIM_HAZARD_BASIC:
            case ANIM_HAZARD_WARNING:
                updateHazardFrame(state);
                break;
                
            default:
                updateDefaultFrame(state);
        }
    }
}

// ===== IMPLEMENTASI FUNGSI UPDATE FRAME SPESIFIK =====

void updateProgressiveFrame(AnimationState* state) {
    state->currentFrame++;
    if (state->currentFrame >= BRAKE_PROGRESSIVE_FRAMES) {
        if (state->isLooping) {
            state->currentFrame = 0;
        } else {
            state->isActive = false;
            state->currentFrame = BRAKE_PROGRESSIVE_FRAMES - 1;
        }
    }
}

void updateSeinFrame(AnimationState* state) {
    state->currentFrame++;
    if (state->currentFrame >= SEIN_LEFT_FRAMES) {
        state->currentFrame = 0; // Sein selalu looping
    }
}

void updateHazardFrame(AnimationState* state) {
    state->currentFrame++;
    if (state->currentFrame >= HAZARD_FRAMES) {
        state->currentFrame = 0; // Hazard selalu looping
    }
}

void updateDefaultFrame(AnimationState* state) {
    state->currentFrame++;
    if (state->currentFrame >= state->totalFrames) {
        if (state->isLooping) {
            state->currentFrame = 0;
        } else {
            state->isActive = false;
            state->currentFrame = state->totalFrames - 1;
        }
    }
}

// ===== IMPLEMENTASI FUNGSI GETTER PATTERN =====

const uint8_t* getPatternForType(AnimationType type) {
    switch (type) {
        // Brake Patterns
        case ANIM_BRAKE_FULL:
            return BRAKE_FULL_PATTERN;
        case ANIM_BRAKE_PROGRESSIVE:
            return BRAKE_PROGRESSIVE_PATTERN;
        case ANIM_BRAKE_WARNING:
            return BRAKE_WARNING_PATTERN;
            
        // Sein Patterns
        case ANIM_SEIN_LEFT_BASIC:
            return SEIN_LEFT_BASIC_PATTERN;
        case ANIM_SEIN_RIGHT_BASIC:
            return SEIN_RIGHT_BASIC_PATTERN;
        case ANIM_SEIN_PROGRESSIVE:
            return SEIN_PROGRESSIVE_PATTERN;
            
        // Hazard Patterns
        case ANIM_HAZARD_BASIC:
            return HAZARD_BASIC_PATTERN;
        case ANIM_HAZARD_WARNING:
            return HAZARD_WARNING_PATTERN;
        case ANIM_HAZARD_PROGRESSIVE:
            return HAZARD_PROGRESSIVE_PATTERN;
            
        default:
            return nullptr;
    }
}

uint8_t getFrameCountForType(AnimationType type) {
    switch (type) {
        case ANIM_BRAKE_FULL:
            return BRAKE_FRAMES;
        case ANIM_BRAKE_PROGRESSIVE:
            return BRAKE_PROGRESSIVE_FRAMES;
        case ANIM_BRAKE_WARNING:
            return BRAKE_WARNING_FRAMES;
        case ANIM_SEIN_LEFT_BASIC:
        case ANIM_SEIN_RIGHT_BASIC:
            return SEIN_LEFT_FRAMES;
        case ANIM_SEIN_PROGRESSIVE:
            return SEIN_PROGRESSIVE_FRAMES;
        case ANIM_HAZARD_BASIC:
        case ANIM_HAZARD_WARNING:
        case ANIM_HAZARD_PROGRESSIVE:
            return HAZARD_FRAMES;
        default:
            return 0;
    }
}

uint16_t getDelayForType(AnimationType type) {
    switch (type) {
        case ANIM_BRAKE_FULL:
            return BRAKE_DELAY;
        case ANIM_BRAKE_PROGRESSIVE:
            return BRAKE_PROGRESSIVE_DELAY;
        case ANIM_BRAKE_WARNING:
            return BRAKE_WARNING_DELAY;
        case ANIM_SEIN_LEFT_BASIC:
        case ANIM_SEIN_RIGHT_BASIC:
            return SEIN_DELAY;
        case ANIM_SEIN_PROGRESSIVE:
            return SEIN_PROGRESSIVE_DELAY;
        case ANIM_HAZARD_BASIC:
            return HAZARD_DELAY;
        case ANIM_HAZARD_WARNING:
            return HAZARD_WARNING_DELAY;
        case ANIM_HAZARD_PROGRESSIVE:
            return HAZARD_PROGRESSIVE_DELAY;
        default:
            return 0;
    }
}

// ===== IMPLEMENTASI FUNGSI STATUS CHECK =====

bool isAnimationComplete(AnimationState* state) {
    return !state->isActive && state->currentFrame >= state->totalFrames - 1;
}

bool isAnimationActive(AnimationState* state) {
    return state->isActive;
}

bool isAnimationPaused(AnimationState* state) {
    return !state->isActive && state->currentFrame > 0;
}