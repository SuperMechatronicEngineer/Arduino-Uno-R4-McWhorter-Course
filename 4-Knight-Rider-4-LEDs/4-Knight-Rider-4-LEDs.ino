/*
 * Project: Knight Rider LED effect
 * Lesson:  Arduino Uno R4 Wifi LESSON 4: Building Clean and Neat Circuits on a Breadboard
 * Revision: 1.0 - Initial Release
 * Date: 2026-02-06
 * License: CC BY-NC-SA 4.0
 * See README.md for full technical documentation.
 */

const int ledPins[] = {2, 3, 4, 5}; // Array of LED pins
const int numLeds = sizeof(ledPins) / sizeof(ledPins[0]); // Total number of LEDs
const int delayTime = 200; // Delay between LED transitions (in milliseconds)

void setup() {
  // Set all LED pins as OUTPUT
  for (int i = 0; i < numLeds; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop() {
  // Move light from left to right
  for (int i = 0; i < numLeds; i++) {
    turnOnLed(i);
    delay(delayTime);
    turnOffLed(i);
  }

  // Move light from right to left
  for (int i = numLeds - 2; i >= 1; i--) {
    turnOnLed(i);
    delay(delayTime);
    turnOffLed(i);
  }
}

// Turn on a specific LED
void turnOnLed(int index) {
  digitalWrite(ledPins[index], HIGH);
}

// Turn off a specific LED
void turnOffLed(int index) {
  digitalWrite(ledPins[index], LOW);
}