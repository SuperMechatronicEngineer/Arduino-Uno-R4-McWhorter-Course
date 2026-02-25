/*
 * Project: LED Toggling using a Push Button
 * Lesson: Arduino Uno R4 WiFi LESSON 24: Make a Button Switch With a Pullup Resistor
 * Revision: 1.2 - Final Version
 * Date: 2026-02-25
 * Author: SuperMechatronicEngineer
 * License: CC BY-NC-SA 4.0
 * See README.md for full technical documentation.
 */

// Pin Definitions
const byte BUTTON_PIN = 2;
const byte LED_PIN = 10;

// LED and Button State Variables (Optimized as bytes)
byte ledState = LOW;           // 0 or 1, tracks the LED status
byte lastStableState = HIGH;    // Confirmed state after debounce
byte lastInstantReading = HIGH; // Immediate state from previous loop

// Debounce Timing Variables
unsigned long lastDebounceTime = 0;  
const unsigned long DEBOUNCE_DELAY = 50; 

void setup() {
  Serial.begin(115200);
  
  pinMode(BUTTON_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  
  digitalWrite(LED_PIN, ledState);
  
  Serial.println("--- System Initialized (Byte-Optimized) ---");
}

void loop() {
  // 1. DigitalRead returns an int, but we store only the necessary byte
  byte currentReading = digitalRead(BUTTON_PIN);

  // 2. Monitor for signal transitions
  if (currentReading != lastInstantReading) {
    lastDebounceTime = millis();
  }

  // 3. Confirm stability after the DEBOUNCE_DELAY
  if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY) {
    
    // 4. State change detection
    if (currentReading != lastStableState) {
      lastStableState = currentReading; 

      // 5. Trigger toggle on Falling Edge (Button Press with Pull-up)
      if (lastStableState == LOW) {
        ledState = !ledState; // Logical NOT works perfectly on byte 0/1
        digitalWrite(LED_PIN, ledState);
        Serial.print("Toggle Event -> LED: ");
        Serial.println(ledState ? "ON" : "OFF");
      }
    }
  }

  // 6. Update history for the next cycle
  lastInstantReading = currentReading;
}