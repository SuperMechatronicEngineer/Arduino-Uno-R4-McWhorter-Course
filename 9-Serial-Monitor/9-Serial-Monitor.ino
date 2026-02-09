/*
 * Project: Serial Monitor LED Status
 * Lesson:  Arduino Uno R4 WiFi LESSON 9: Using the Serial Port to Print to the Serial Monitor
 * Revision: 1.1 - Improved Version
 * Date: 2026-02-09
 * License: CC BY-NC-SA 4.0
 */

// Hardware Configuration
const int LED_PIN = 2;

// Timing Variables
const int BLINK_DELAY = 1000;
const int BOOT_DELAY  = 3000;

// Serial Messages
const char* MSG_ON    = "LED turned ON";
const char* MSG_OFF   = "LED turned OFF";
const char* MSG_START = "--- Serial Monitor Initialized Successfully ---";

void setup() {
  // Use a faster baud rate if possible (115200), but 9600 is fine for beginners
  Serial.begin(9600);
  
  // Wait for Serial Port to be ready (Native USB behavior of R4)
  while (!Serial) {
    ; // Wait
  }

  // Visual header for the console
  delay(BOOT_DELAY);
  Serial.println();
  Serial.println(MSG_START);

  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  // LED ON sequence
  digitalWrite(LED_PIN, HIGH);
  Serial.println(MSG_ON);
  delay(BLINK_DELAY);

  // LED OFF sequence
  digitalWrite(LED_PIN, LOW);
  Serial.println(MSG_OFF);
  delay(BLINK_DELAY);
}