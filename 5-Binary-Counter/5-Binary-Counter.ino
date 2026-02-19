/*
 * Project: Binary counter
 * Lesson: Arduino Uno R4 WiFi LESSON 5: Explaining How Computers Work Based On Binary Numbers
 * Revision: 1.0 - Initial Release
 * Date: 2026-02-06
 * Author: SuperMechatronicEngineer
 * License: CC BY-NC-SA 4.0
 * See README.md for full technical documentation.
 */

const int ledPins[] = {2, 3, 4, 5};         // Array of LED pins
const int numLeds = sizeof(ledPins) / sizeof(ledPins[0]); // Automatically determine number of LEDs
const int delayTime = 500;                 // Delay between counts in milliseconds

void setup() {
  // Set all LED pins as OUTPUT
  for (int i = 0; i < numLeds; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop() {
  // Count from 0 to 15 (4-bit binary)
  // (1 << numLeds) means 2 raised to the power of numLeds
  // Example: if numLeds = 4, then (1 << 4) = 16
  for (int count = 0; count < (1 << numLeds); count++) {
    displayBinary(count);
    delay(delayTime);
  }
}

// Display a number in binary using the LEDs
void displayBinary(int number) {
  for (int bit = 0; bit < numLeds; bit++) {
    // (number >> bit) shifts the bits of 'number' to the right by 'bit' positions
    // This moves the target bit to the least significant position (rightmost)
    //
    // '& 1' performs a bitwise AND with 00000001
    // This isolates the least significant bit, effectively extracting the value (0 or 1)
    //
    // Example: if number = 6 (binary 0110) and bit = 1:
    //   number >> 1 = 0011 (3)
    //   0011 & 0001 = 0001 → result is 1 → LED turns ON
    //
    // This line turns the corresponding LED ON or OFF based on the bit value
    digitalWrite(ledPins[bit], (number >> bit) & 1);
  }
}
