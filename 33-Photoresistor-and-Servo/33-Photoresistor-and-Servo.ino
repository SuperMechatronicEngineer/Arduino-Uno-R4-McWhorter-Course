/*
 * Project: Photoresistor Controlled Servo Actuator
 * Lesson: Arduino Uno R4 WiFi LESSON 33: Using a Photoresistor in a Project
 * Revision: 1.2 - Final Version
 * Date: 2026-03-05
 * Author: SuperMechatronicEngineer
 * License: CC BY-NC-SA 4.0
 * See README.md for full technical documentation.
 */

#include <Servo.h>

// HARDWARE PIN DEFINITIONS
const uint8_t LDR_PIN   = A0;
const uint8_t SERVO_PIN = 3;

// CALIBRATION CONSTANTS (Updated to 0.7V - 4.9V range)
const int16_t LIGHT_MIN = 143;   // ADC value for 0.7V (Min Angle)
const int16_t LIGHT_MAX = 1002;  // ADC value for 4.9V (Max Angle)
const int16_t ANGLE_MIN = 0;
const int16_t ANGLE_MAX = 160;

// TIMING CONFIGURATION (ms)
const uint32_t UPDATE_INTERVAL = 20;   // 50Hz sensing/actuation
const uint32_t SERIAL_INTERVAL = 500;  // 2Hz telemetry update

// GLOBAL STATE
uint32_t lastUpdateTime = 0;
uint32_t lastSerialTime = 0;
Servo myServo;

// Linear mapping with 32-bit math safety and clamping.
int16_t scaleValue(int16_t x, int16_t in_min, int16_t in_max, int16_t out_min, int16_t out_max) {
  if (x <= in_min) return out_min;
  if (x >= in_max) return out_max;
  return (int16_t)((int32_t)(x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min);
}

void setup() {
  Serial.begin(115200);
  while (!Serial) {}
  myServo.attach(SERVO_PIN);
  Serial.println(F("================================================"));
  Serial.println(F("SYSTEM READY: Light Tracking & Actuation Active."));
  Serial.println(F("================================================"));
}

void loop() {
  uint32_t currentMillis = millis();
  static int16_t rawADC = 0;

  // 1. DIRECT MOTION CONTROL
  if (currentMillis - lastUpdateTime >= UPDATE_INTERVAL) {
    rawADC = (int16_t)analogRead(LDR_PIN);
    myServo.write(scaleValue(rawADC, LIGHT_MIN, LIGHT_MAX, ANGLE_MIN, ANGLE_MAX));
    lastUpdateTime = currentMillis;
  }

  // 2. FORMATTED TELEMETRY
  if (currentMillis - lastSerialTime >= SERIAL_INTERVAL) {
    float voltage = (rawADC * 5.0f) / 1023.0f;

    Serial.print(F("V: ")); 
    Serial.print(voltage, 1); // Formatted to 1 decimal
    Serial.print(F(" | ADC: ")); 
    Serial.print(rawADC);
    Serial.print(F(" | Deg: ")); 
    Serial.println(scaleValue(rawADC, LIGHT_MIN, LIGHT_MAX, ANGLE_MIN, ANGLE_MAX));
    
    lastSerialTime = currentMillis;
  }
}