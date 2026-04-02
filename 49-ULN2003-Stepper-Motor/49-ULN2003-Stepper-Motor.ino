/*
 * Project: 4-Button Incremental Stepper Motor Control
 * Lesson: Arduino Uno R4 WiFi LESSON 49: Arduino Stepper Motor Control
 * Revision: 1.2 - Final Version
 * Note: We use the 28BYJ-48 stepper motor, and the ULN2003 Stepper Motor Driver.
 * Date: 2026-04-02
 * Author: SuperMechatronicEngineer
 * License: CC BY-NC-SA 4.0
 * See README.md for full technical documentation.
 */

#include <Arduino.h>

/* ============================================================
   StepperDriver Class
   Handles the 8-step half-step sequence for the 28BYJ-48 motor
   driven through the ULN2003 board.
   ============================================================ */
class StepperDriver {
private:
    const uint8_t motorPins[4];

    static constexpr uint8_t HALF_STEP_TABLE[8][4] = {
        {1, 0, 0, 0}, {1, 1, 0, 0},
        {0, 1, 0, 0}, {0, 1, 1, 0},
        {0, 0, 1, 0}, {0, 0, 1, 1},
        {0, 0, 0, 1}, {1, 0, 0, 1}
    };

    int8_t currentStepIndex = 0;
    uint32_t lastStepTimestamp = 0;
    uint32_t stepInterval = 2; // ms per step

public:
    StepperDriver(uint8_t p1, uint8_t p2, uint8_t p3, uint8_t p4)
        : motorPins{p1, p2, p3, p4} {}

    void begin() {
        for (auto pin : motorPins) {
            pinMode(pin, OUTPUT);
            digitalWrite(pin, LOW);
        }
    }

    void setSpeed(uint32_t intervalMs) {
        stepInterval = intervalMs;
    }

    bool update(bool clockwise) {
        uint32_t now = millis();
        if (now - lastStepTimestamp >= stepInterval) {
            lastStepTimestamp = now;

            currentStepIndex = clockwise ?
                (currentStepIndex + 1) % 8 :
                (currentStepIndex - 1 + 8) % 8;

            for (uint8_t i = 0; i < 4; i++) {
                digitalWrite(motorPins[i], HALF_STEP_TABLE[currentStepIndex][i]);
            }
            return true;
        }
        return false;
    }

    void release() {
        for (uint8_t i = 0; i < 4; i++) {
            digitalWrite(motorPins[i], LOW);
        }
    }
};

/* ============================================================
   ButtonManager Class
   Handles debouncing and rising-edge detection for all buttons.
   Each button has:
     - pin number
     - step count
     - direction
   ============================================================ */
class ButtonManager {
private:
    struct Button {
        uint8_t pin;
        uint32_t targetSteps;
        bool direction;
        bool lastState;
        bool debouncedState;
        uint32_t lastTime;
    };

    static constexpr uint32_t DEBOUNCE_DELAY = 50;

    Button buttons[4] = {
        {2, 114, true,  HIGH, HIGH, 0},  // CW 10°
        {3, 11,  true,  HIGH, HIGH, 0},  // CW 1°
        {4, 11,  false, HIGH, HIGH, 0},  // CCW 1°
        {5, 114, false, HIGH, HIGH, 0}   // CCW 10°
    };

public:
    void begin() {
        for (auto &btn : buttons) {
            pinMode(btn.pin, INPUT_PULLUP);
        }
    }

    // Returns true when a button is released (rising edge)
    bool check(uint32_t &steps, bool &dir) {
        uint32_t now = millis();

        for (auto &btn : buttons) {
            bool currentRead = digitalRead(btn.pin);

            if (currentRead != btn.lastState)
                btn.lastTime = now;

            if ((now - btn.lastTime) > DEBOUNCE_DELAY) {
                if (currentRead == HIGH && btn.debouncedState == LOW) {
                    steps = btn.targetSteps;
                    dir = btn.direction;
                    btn.debouncedState = currentRead;
                    btn.lastState = currentRead;
                    return true;
                }
                btn.debouncedState = currentRead;
            }

            btn.lastState = currentRead;
        }
        return false;
    }
};

/* ============================================================
   Hardware Pinout
   ============================================================ */
constexpr uint8_t PIN_MOTOR_IN1 = 8;
constexpr uint8_t PIN_MOTOR_IN2 = 9;
constexpr uint8_t PIN_MOTOR_IN3 = 10;
constexpr uint8_t PIN_MOTOR_IN4 = 11;

/* ============================================================
   System State
   ============================================================ */
StepperDriver motor(PIN_MOTOR_IN1, PIN_MOTOR_IN2, PIN_MOTOR_IN3, PIN_MOTOR_IN4);
ButtonManager buttonManager;

enum SystemState { IDLE, ROTATING };
SystemState currentState = IDLE;

uint32_t stepsRemaining = 0;
bool moveClockwise = true;

/* ============================================================
   Setup
   ============================================================ */
void setup() {
    motor.begin();
    motor.setSpeed(2); // ms per step
    buttonManager.begin();
}

/* ============================================================
   Main Loop
   ============================================================ */
void loop() {
    uint32_t steps;
    bool dir;

    // Check for button events
    if (buttonManager.check(steps, dir) && currentState == IDLE) {
        stepsRemaining = steps;
        moveClockwise = dir;
        currentState = ROTATING;
    }

    // Motor state machine
    switch (currentState) {
        case ROTATING:
            if (motor.update(moveClockwise)) {
                stepsRemaining--;
            }
            if (stepsRemaining == 0) {
                motor.release();
                currentState = IDLE;
            }
            break;

        case IDLE:
            break;
    }
}
