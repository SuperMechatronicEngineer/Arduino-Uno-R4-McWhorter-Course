/*
 * Project: LED Control from the Serial Monitor
 * Lesson: Arduino Uno R4 WiFi LESSON 14: Read User Input From the Serial Monitor
 * Revision: 1.2 - Final Version
 * Date: 2026-02-19
 * Author: SuperMechatronicEngineer
 * License: CC BY-NC-SA 4.0
 * See README.md for full technical documentation.
 */

const int LED_LINEAR = 11;
const int LED_EXPONENTIAL = 10;

void setup() {
  pinMode(LED_LINEAR, OUTPUT);
  pinMode(LED_EXPONENTIAL, OUTPUT);
  
  Serial.begin(115200);
  
  // Wait for Serial port to connect
  while (!Serial);
  
  Serial.println("--- BRIGHTNESS LED CONTROL SYSTEM ---");
  Serial.println("Instructions: Enter ONLY a number between 0 and 10.");
  Serial.println("Compatibility: Works with any Line Ending setting.");
}

void loop() {
  if (Serial.available() > 0) {
    // 1. Brief delay to ensure the entire string has arrived in the buffer
    delay(50); 
    
    String inputString = "";
    bool isOnlyDigits = true;

    // 2. Read everything currently in the buffer
    while (Serial.available() > 0) {
      char c = Serial.read();
      
      // Ignore formatting characters (spaces, tabs, newlines, carriage returns)
      if (isSpace(c) || c == '\n' || c == '\r') {
        continue; 
      }
      
      // If the character is not a space/newline but is NOT a digit...
      if (!isDigit(c)) {
        isOnlyDigits = false;
      }
      
      inputString += c; // Build the filtered string
    }

    // 3. Final Validation
    if (inputString.length() == 0) {
      return; // Ignore empty inputs (e.g., just pressing Enter)
    }

    if (!isOnlyDigits) {
      Serial.print("[REJECTED]: Input [");
      Serial.print(inputString);
      Serial.println("] contains invalid characters. Use digits only.");
    } 
    else {
      // Convert to integer now that we are certain it's a pure number
      int x = inputString.toInt();

      if (x >= 0 && x <= 10) {
        // --- LOGARITHMIC & LINEAR FORMULAS ---
        float yLinear = x * 25.5;
        float yExp = pow(2, (x / 1.25)) - 1;

        analogWrite(LED_LINEAR, (int)yLinear);
        analogWrite(LED_EXPONENTIAL, (int)yExp);

        Serial.print("[ACCEPTED]: Level "); 
        Serial.print(x);
        Serial.print(" | Linear PWM: "); Serial.print((int)yLinear);
        Serial.print(" | Exp PWM: "); Serial.println((int)yExp);
      } 
      else {
        Serial.print("[REJECTED]: Value "); 
        Serial.print(x);
        Serial.println(" is out of range (0-10).");
      }
    }
    Serial.println("\nEnter next value (0-10):");
  }
}