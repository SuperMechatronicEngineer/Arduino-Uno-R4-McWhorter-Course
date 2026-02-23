/*
 * Project: RGB Color Loops
 * Lesson: Arduino Uno R4 WiFi LESSON 20: For Loops in Arduino
 * Revision: 1.2 - Final Version
 * Date: 2026-02-23
 * Author: SuperMechatronicEngineer
 * License: CC BY-NC-SA 4.0
 * See README.md for full technical documentation.
 */

// Hardware Configuration: Pin assignments using optimized data types
const byte RED_PIN   = 11;
const byte GREEN_PIN = 10;
const byte BLUE_PIN  = 9;

// Timing Configuration (milliseconds)
const unsigned int CYCLE_DELAY = 250;

void setup() {
  // Initialize digital pins as outputs
  pinMode(RED_PIN,   OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN,  OUTPUT);
  
  // High-speed telemetry initialization
  Serial.begin(115200);
  Serial.setTimeout(10); 

  // Wait for Serial port to stabilize
  while (!Serial); 

  // Ensure hardware starts in a safe (OFF) state
  allLedsOff();
  Serial.println("--- RGB LED SYSTEM INITIALIZED ---");
  Serial.println("Status: Standby - Awaiting User Command");
}

void loop() {
  Serial.println("\nEnter the number of color cycles to perform (0-100):");

  // Block execution until serial data is available
  while (Serial.available() == 0);
  
  // Read and sanitize input string
  String input = Serial.readString();
  input.trim();

  // Robust Input Validation: Ensure string is purely numeric
  bool isNumeric = (input.length() > 0);
  for (byte i = 0; i < input.length(); i++) {
    if (!isDigit(input[i])) {
      isNumeric = false;
      break;
    }
  }

  if (isNumeric) {
    int numCycles = input.toInt();

    // Logical Boundary Check (Range Validation)
    if (numCycles >= 0 && numCycles <= 100) {
      Serial.print("[VALIDATED] Initiating ");
      Serial.print(numCycles);
      Serial.println(" cycles.");

      // Manual control loop using 'while' structure
      int count = 1; 
      while (count <= numCycles) {
        Serial.print("-> Executing Cycle #");
        Serial.println(count);

        // Stage 1: RED Activation
        allLedsOff();
        analogWrite(RED_PIN, 255);
        delay(CYCLE_DELAY);

        // Stage 2: GREEN Activation
        allLedsOff();
        analogWrite(GREEN_PIN, 255);
        delay(CYCLE_DELAY);

        // Stage 3: BLUE Activation
        allLedsOff();
        analogWrite(BLUE_PIN, 255);
        delay(CYCLE_DELAY);

        // Stage 4: Safety Interval (ALL OFF)
        allLedsOff();
        delay(CYCLE_DELAY * 4);

        // Manual iteration increment
        count++; 
      }
      
      allLedsOff();
      Serial.println("[COMPLETED] All cycles finished. Returning to standby.");
    } else {
      Serial.println("[ERROR] Out of Range. Please enter a value between 0 and 100.");
    }
  } else {
    Serial.print("[ERROR] Invalid Input: '");
    Serial.print(input);
    Serial.println("' is not a valid integer.");
  }
}

/**
 * Mutual Exclusion Logic:
 * Ensures all RGB channels are set to 0V to prevent unintended color mixing.
 */
void allLedsOff() {
  analogWrite(RED_PIN,   0);
  analogWrite(GREEN_PIN, 0);
  analogWrite(BLUE_PIN,  0);
}