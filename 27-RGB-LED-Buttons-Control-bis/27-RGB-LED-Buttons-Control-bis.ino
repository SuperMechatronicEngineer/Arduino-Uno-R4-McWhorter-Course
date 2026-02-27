/*
 * Project: RGB LED Control using Push Buttons (Internal Pull-up Version)
 * Lesson: Arduino Uno R4 WiFi LESSON 27: Using Internal Pullup Resistors on Arduino
 * Revision: 1.2 - Final Version
 * Date: 2026-02-27
 * Author: SuperMechatronicEngineer
 * License: CC BY-NC-SA 4.0
 * See README.md for full technical documentation.
 */

enum { RED, GREEN, BLUE, NUM_CHANNELS };

const byte BUTTON_PINS[NUM_CHANNELS] = {4, 3, 2};   
const byte LED_PINS[NUM_CHANNELS]    = {11, 10, 9}; 

byte ledStates[NUM_CHANNELS]           = {LOW, LOW, LOW};
byte lastStableStates[NUM_CHANNELS]    = {HIGH, HIGH, HIGH}; 
byte lastInstantReadings[NUM_CHANNELS] = {HIGH, HIGH, HIGH};
byte currentReadings[NUM_CHANNELS]     = {HIGH, HIGH, HIGH};

unsigned long lastDebounceTimes[NUM_CHANNELS] = {0, 0, 0};
const unsigned long DEBOUNCE_DELAY = 50; 

void setup() {
  Serial.begin(115200);
  
  for (byte i = 0; i < NUM_CHANNELS; i++) {
    // UPDATED: Activated internal pull-up resistor
    // This eliminates the need for external 10k resistors
    pinMode(BUTTON_PINS[i], INPUT_PULLUP); 
    
    pinMode(LED_PINS[i], OUTPUT);
    digitalWrite(LED_PINS[i], ledStates[i]);
  }
  
  Serial.print("--- System Ready | Internal Pull-ups Active | Channels: ");
  Serial.print(NUM_CHANNELS);
  Serial.println(" ---");
}

void loop() {
  for (byte i = 0; i < NUM_CHANNELS; i++) {
    
    currentReadings[i] = digitalRead(BUTTON_PINS[i]);

    if (currentReadings[i] != lastInstantReadings[i]) {
      lastDebounceTimes[i] = millis(); 
    }

    if ((millis() - lastDebounceTimes[i]) > DEBOUNCE_DELAY) {
      if (currentReadings[i] != lastStableStates[i]) {
        lastStableStates[i] = currentReadings[i];

        // LOGIC REMAINS FALLING EDGE: 
        // With Pull-up, HIGH = Released, LOW = Pressed
        if (lastStableStates[i] == LOW) {
          ledStates[i] = !ledStates[i]; 
          digitalWrite(LED_PINS[i], ledStates[i]);
          
          Serial.print("Event Detected -> Channel: ");
          Serial.print(i == RED ? "RED" : (i == GREEN ? "GREEN" : "BLUE"));
          Serial.println(ledStates[i] ? " [ACTIVE]" : " [INACTIVE]");
        }
      }
    }
    lastInstantReadings[i] = currentReadings[i];
  }
}