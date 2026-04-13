/*
 * Project: Measuring Distance using an HC-SR04 Ultrasonic Sensor
 * Lesson: Arduino Uno R4 WiFi LESSON 51: Using the HC-SR04 Ultrasonic Sensor for Echolocation
 * Revision: 1.2 - Final Version
 * Date: 2026-04-13
 * Author: SuperMechatronicEngineer
 * License: CC BY-NC-SA 4.0
 * See README.md for full technical documentation.
 */

#include <Arduino.h>

class UltrasonicAsync {
private:
    const uint8_t _trigPin;
    const uint8_t _echoPin;

    // Volatile variables are modified within the ISR
    volatile uint32_t _startTime = 0;
    volatile uint32_t _duration = 0;
    volatile bool _newReading = false;

    static UltrasonicAsync* _instance;

    // Interrupt Service Routine (ISR) to capture Echo pulse duration
    static void isrWrapper() {
        if (!_instance) return;

        bool level = digitalRead(_instance->_echoPin);

        if (level) {
            // Rising edge: pulse started
            _instance->_startTime = micros();
        } else {
            // Falling edge: pulse ended
            uint32_t end = micros();
            if (_instance->_startTime != 0) {
                _instance->_duration = end - _instance->_startTime;
                _instance->_newReading = true;
            }
        }
    }

public:
    // Constructor: sets the pins and binds this specific instance to the global static pointer
    // so that the ISR knows which object to update.
    UltrasonicAsync(uint8_t trig, uint8_t echo)
        : _trigPin(trig), _echoPin(echo) {
        // Bind 'this' specific object instance to the static pointer.
        // This is mandatory for the static isrWrapper to access non-static 
        // members (like _startTime and _duration) during an interrupt.    
        _instance = this;
    }

    void begin() {
        pinMode(_trigPin, OUTPUT);
        pinMode(_echoPin, INPUT);
        digitalWrite(_trigPin, LOW);

        // Enable hardware interrupt on the Echo pin to detect any state change
        attachInterrupt(
            digitalPinToInterrupt(_echoPin),
            isrWrapper,
            CHANGE
        );
    }

    void trigger() {
        // Standard HC-SR04 trigger sequence
        digitalWrite(_trigPin, LOW);
        delayMicroseconds(2);
        digitalWrite(_trigPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(_trigPin, LOW);

        // Reset the start time to monitor hardware timeout
        _startTime = micros();
    }

    /* Returns the distance in cm if within the 3cm - 300cm range.
       Returns -1.0f if the measurement is in progress or out of range.
    */
    float getDistance() {
        // Hardware Timeout: ignore if no echo returns within 30ms (~500cm)
        if (_startTime != 0 && (micros() - _startTime) > 30000) {
            _startTime = 0;
            _newReading = false;
            return -1.0f;
        }

        if (!_newReading) return -1.0f;

        _newReading = false;
        
        // 0.01715 = (Speed of sound in cm/us) / 2
        float distance = _duration * 0.01715f;

        // Apply the conservative project filter (3cm to 300cm)
        if (distance >= 3.0f && distance <= 300.0f) {
            return distance;
        }

        // Out of range readings are treated as invalid
        return -1.0f;
    }
};

UltrasonicAsync* UltrasonicAsync::_instance = nullptr;

// --- Hardware Configuration ---
constexpr uint8_t PIN_TRIG = 2;
constexpr uint8_t PIN_ECHO = 3;

UltrasonicAsync sonar(PIN_TRIG, PIN_ECHO);

void setup() {
    Serial.begin(115200);
    while (!Serial);

    sonar.begin();

    Serial.println(F("--- Optimized Ultrasonic System ---"));
    Serial.println(F("Filtering range: 3cm - 300cm"));
    Serial.println(F("-----------------------------------"));
}

void loop() {
    static uint32_t lastTrigger = 0;
    uint32_t now = millis();

    // Trigger a measurement every 100ms
    if (now - lastTrigger >= 100) {
        lastTrigger = now;
        sonar.trigger();
    }

    float cm = sonar.getDistance();

    // Only print if the distance is valid (within 3cm - 300cm)
    if (cm > 0) {
        Serial.print(F("Distance: "));
        Serial.print(cm, 1);
        Serial.println(F(" cm"));
    }
}