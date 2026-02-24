/*
 * Project: Interactive Potentiometer-Driven Servo System
 * Lesson: Arduino Uno R4 WiFi LESSON 22: Control a Servo With Your Arduino
 * Revision: 1.2 - Final Version
 * Date: 2026-02-24
 * Author: SuperMechatronicEngineer
 * License: CC BY-NC-SA 4.0
 * See README.md for full technical documentation.
 */

#include <Servo.h>

// --- PIN CONFIGURATION ---
const byte POT_PIN   = A0;
const byte SERVO_PIN = 11;

// --- CALIBRATION CONSTANTS ---
const float MAX_ANGLE   = 160.0;
const float MAX_ADC     = 1023.0;
const float REF_VOLTAGE = 5.0;

Servo myServo;

void setup() {
  Serial.begin(115200);
  myServo.attach(SERVO_PIN);

  Serial.println("========================================");
  Serial.println("   SERVO TELEMETRY SYSTEM ACTIVE        ");
  Serial.println("========================================");
}

void loop() {
  // 1. Raw Data Acquisition
  int adcValue = analogRead(POT_PIN);

  // 2. Linear Transfer Functions (y = mx)
  float voltage     = (REF_VOLTAGE / MAX_ADC) * adcValue;
  float targetAngle = (MAX_ANGLE / MAX_ADC) * adcValue;

  // 3. Data Type Optimization
  // Casting to byte (0-255) as the angle never exceeds 160
  byte currentAngle = (byte)targetAngle;

  // 4. Output to Hardware
  myServo.write(currentAngle);

  // 5. Intelligent Telemetry
  // Using a static byte initialized to an "out-of-range" value (255)
  // to ensure the first reading is always printed.
  static byte lastAngle = 255; 
  
  if (currentAngle != lastAngle) {
    Serial.print("Input: ");
    Serial.print(voltage, 2);
    Serial.print("V | Position: ");
    Serial.print(currentAngle);
    Serial.println(" deg");
    
    lastAngle = currentAngle;
  }

  delay(20); 
}