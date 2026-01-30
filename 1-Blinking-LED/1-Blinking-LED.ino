/*
 * Project: Fast LED blinking
 * Lesson:  Getting Started for Absolute Beginners - Lesson 1
 * Revision: 1.0 - Initial Release
 * Date: 2026-01-28
 * License: CC BY-NC-SA 4.0
 * See README.md for full technical documentation.
 */

const int BLINK_DELAY = 20; 

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(BLINK_DELAY); 
  digitalWrite(LED_BUILTIN, LOW);
  delay(BLINK_DELAY);
}