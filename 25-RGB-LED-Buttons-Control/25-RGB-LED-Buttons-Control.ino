/*
 * Project: RGB LED Control using Push Buttons
 * Lesson: Arduino Uno R4 WiFi LESSON 25: Make a Toggle Switch with Button Switch
 * Revision: 1.2 - Final Version
 * Date: 2026-02-25
 * Author: SuperMechatronicEngineer
 * License: CC BY-NC-SA 4.0
 * See README.md for full technical documentation.
 */

// 1. Automated Indexing: NUM_CHANNELS is calculated by the compiler.
enum {RED, GREEN, BLUE, NUM_CHANNELS};

// 2. Hardware Mapping
const byte BUTTON_PINS[NUM_CHANNELS] = {4, 3, 2};   
const byte LED_PINS[NUM_CHANNELS]    = {11, 10, 9}; 

// 3. State Variables (Vectorized for multi-channel tracking)
byte ledStates[NUM_CHANNELS]           = {LOW, LOW, LOW};   // Current LED status
byte lastStableStates[NUM_CHANNELS]    = {HIGH, HIGH, HIGH}; // State confirmed after debounce
byte lastInstantReadings[NUM_CHANNELS] = {HIGH, HIGH, HIGH}; // Reading from the previous loop
byte currentReadings[NUM_CHANNELS]     = {HIGH, HIGH, HIGH}; // Direct hardware reading vector

// 4. Timing Constants and Independent Timers
unsigned long lastDebounceTimes[NUM_CHANNELS] = {0, 0, 0};
const unsigned long DEBOUNCE_DELAY = 50; // Threshold for signal stabilization (ms)

void setup() {
  // Initialize Serial at 115200 for low-latency debugging
  Serial.begin(115200);
  
  for (byte i = 0; i < NUM_CHANNELS; i++) {
    pinMode(BUTTON_PINS[i], INPUT); // Assumes buttons with external pull-up resistors
    pinMode(LED_PINS[i], OUTPUT);   // Set pins for LED anode control
    
    // Set initial hardware state
    digitalWrite(LED_PINS[i], ledStates[i]);
  }
  
  Serial.print("--- RGB Multi-Channel System Initialized | Channels: ");
  Serial.print(NUM_CHANNELS);
  Serial.println(" ---");
}

void loop() {
  // Iterate through each channel (automatically scales with NUM_CHANNELS)
  for (byte i = 0; i < NUM_CHANNELS; i++) {
    
    // 5. Acquisition: Read current hardware state into the specific vector index
    currentReadings[i] = digitalRead(BUTTON_PINS[i]);

    // 6. Transition Detection: Reset timer if signal instability is detected
    if (currentReadings[i] != lastInstantReadings[i]) {
      lastDebounceTimes[i] = millis(); 
    }

    // 7. Stability Verification: Process logic only after DEBOUNCE_DELAY is reached
    if ((millis() - lastDebounceTimes[i]) > DEBOUNCE_DELAY) {
      
      // 8. State Change Analysis: Compare stabilized reading with the previous stable state
      if (currentReadings[i] != lastStableStates[i]) {
        lastStableStates[i] = currentReadings[i];

        // 9. Edge Triggering: Toggle on Falling Edge (Button pressed with Pull-up)
        if (lastStableStates[i] == LOW) {
          ledStates[i] = !ledStates[i]; // Flip logic state
          digitalWrite(LED_PINS[i], ledStates[i]);
          
          // Debugging/Feedback Output
          Serial.print("Event Detected -> Channel: ");
          Serial.print(i == RED ? "RED" : (i == GREEN ? "GREEN" : "BLUE"));
          Serial.println(ledStates[i] ? " [ACTIVE]" : " [INACTIVE]");
        }
      }
    }

    // 10. Memory Update: Store the current reading for the next iteration cycle
    lastInstantReadings[i] = currentReadings[i];
  }
}