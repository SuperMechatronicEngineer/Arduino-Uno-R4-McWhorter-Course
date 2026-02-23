/*
 * Project: RGB Color Loops
 * Lesson: Arduino Uno R4 WiFi LESSON 19: Mixing Colors with an RGB LED
 * Revision: 1.2 - Final Version
 * Date: 2026-02-23
 * Author: SuperMechatronicEngineer
 * License: CC BY-NC-SA 4.0
 * See README.md for full technical documentation.
 */

const byte RED_PIN   = 11;
const byte GREEN_PIN = 10;
const byte BLUE_PIN  = 9;

const unsigned int CYCLE_DELAY = 250;

void setup() {
  pinMode(RED_PIN,   OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN,  OUTPUT);
  
  Serial.begin(115200);
  Serial.setTimeout(10); 

  while (!Serial); 

  allLedsOff();
  Serial.println("--- RGB LED CYCLE INTERFACE INITIALIZED ---");
}

void loop() {
  Serial.println("\nEnter the number of color cycles to perform (0-100):");

  // Wait for user input
  while (Serial.available() == 0);
  
  String input = Serial.readString();
  input.trim();

  // Robust Input Validation Logic
  bool isNumeric = (input.length() > 0);
  for (byte i = 0; i < input.length(); i++) {
    if (!isDigit(input[i])) {
      isNumeric = false;
      break;
    }
  }

  if (isNumeric) {
    int numCycles = input.toInt();

    // Range Validation (0-100)
    if (numCycles >= 0 && numCycles <= 100) {
      Serial.print("[SUCCESS] Starting ");
      Serial.print(numCycles);
      Serial.println(" cycles (Red -> Green -> Blue).");

      for (int i = 1; i <= numCycles; i++) {
        Serial.print("Executing Cycle #");
        Serial.println(i);

        // 1. RED
        allLedsOff();
        analogWrite(RED_PIN, 255);
        delay(CYCLE_DELAY);

        // 2. GREEN
        allLedsOff();
        analogWrite(GREEN_PIN, 255);
        delay(CYCLE_DELAY);

        // 3. BLUE
        allLedsOff();
        analogWrite(BLUE_PIN, 255);
        delay(CYCLE_DELAY);

        // 4. OFF
        allLedsOff();
        delay(CYCLE_DELAY*4);
      }
      
      allLedsOff();
      Serial.println("[FINISHED] Sequence complete. Returning to standby.");
    } else {
      Serial.println("[REJECTED] Out of range. Please enter a number between 0 and 100.");
    }
  } else {
    Serial.print("[REJECTED] '");
    Serial.print(input);
    Serial.println("' is not a valid integer.");
  }
}

/**
 * Ensures mutual exclusion by turning off all RGB channels.
 */
void allLedsOff() {
  analogWrite(RED_PIN,   0);
  analogWrite(GREEN_PIN, 0);
  analogWrite(BLUE_PIN,  0);
}