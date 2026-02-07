/*
 * Project: Binary counter
 * Lesson:  Arduino Uno R4 WiFi LESSON 6: Create a Binary Counter With Arduino
 * Revision: 1.0 - Initial Release
 * Date: 2026-02-07
 * License: CC BY-NC-SA 4.0
 * See README.md for full technical documentation.
 */

const int ledPins[] = {2, 3, 4, 5, 6};         // Array of LED pins
const int numLeds = sizeof(ledPins) / sizeof(ledPins[0]); // Automatically determine number of LEDs
const int delayTime = 500;                 // Delay between counts in milliseconds

void setup() {
  // Set all LED pins as OUTPUT
  for (int i = 0; i < numLeds; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop() {
  for (int count = 0; count < (1 << numLeds); count++) {
    displayBinary(count);
    delay(delayTime);
  }
}

// Display a number in binary using the LEDs
void displayBinary(int number) {
  for (int bit = 0; bit < numLeds; bit++) {
    digitalWrite(ledPins[bit], (number >> bit) & 1);
  }
}