/*
 * Project: Simultaneous Blinking LEDs
 * Lesson: Arduino Uno R4 Wifi LESSON 3: Blink an LED With the Arduino
 * Revision: 1.0 - Initial Release
 * Author: SuperMechatronicEngineer
 * License: CC BY-NC-SA 4.0
 * See README.md for full technical documentation.
 */

const int ledPins[] = {2, 3, 4, 5}; 
const int numLeds = sizeof(ledPins) / sizeof(ledPins[0]);
const int blinkInterval = 500; // Time in ms for ON and OFF states

void setup() {
  for (int i = 0; i < numLeds; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop() {
  // Turn ALL LEDs ON
  for (int i = 0; i < numLeds; i++) {
    digitalWrite(ledPins[i], HIGH);
  }
  delay(blinkInterval);

  // Turn ALL LEDs OFF
  for (int i = 0; i < numLeds; i++) {
    digitalWrite(ledPins[i], LOW);
  }
  delay(blinkInterval);
}