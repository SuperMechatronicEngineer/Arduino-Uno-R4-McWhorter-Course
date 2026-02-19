/*
 * Project: Dual-Speed Sequential LED Blinker
 * Lesson: Arduino Uno R4 WiFi LESSON 8: Using Variables in Arduino
 * Revision: 1.1 - Optimized Version
 * Author: SuperMechatronicEngineer
 * License: CC BY-NC-SA 4.0
 * See README.md for full technical documentation.
 */

// Hardware Mapping
const int ledPins[] = {2, 3}; 
const int RED_LED = 0;   // Index for Red LED
const int GREEN_LED = 1; // Index for Green LED

// Timing & Count Variables
const int redBlinkInterval = 600; 
const int greenBlinkInterval = 200;
const int redRepeatCount = 10;
const int greenRepeatCount = 5;

void setup() {
  for (int i = 0; i < 2; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop() {
  // Execute sequence for Red LED (Slow)
  blinkSpecificLed(RED_LED, redRepeatCount, redBlinkInterval);

  // Execute sequence for Green LED (Fast)
  blinkSpecificLed(GREEN_LED, greenRepeatCount, greenBlinkInterval);
}

// Function to handle the blinking logic for any LED.
void blinkSpecificLed(int ledIndex, int times, int interval) {
  for (int i = 0; i < times; i++) {
    digitalWrite(ledPins[ledIndex], HIGH);
    delay(interval);
    digitalWrite(ledPins[ledIndex], LOW);
    delay(interval);
  }
}