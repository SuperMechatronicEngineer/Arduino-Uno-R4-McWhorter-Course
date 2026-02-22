/*
 * Project: Green, Yellow, and Red LEDs Serial Selector
 * Lesson: Arduino Uno R4 WiFi LESSON 16: Understanding If Statements and Conditionals
 * Revision: 1.2 - Final Version
 * Date: 2026-02-21
 * Author: SuperMechatronicEngineer
 * License: CC BY-NC-SA 4.0
 * See README.md for full technical documentation.
 */

// Pin Definitions
const int PIN_LED_GREEN  = 11;
const int PIN_LED_YELLOW = 10;
const int PIN_LED_RED    = 9;

void setup() {
  pinMode(PIN_LED_GREEN,  OUTPUT);
  pinMode(PIN_LED_YELLOW, OUTPUT);
  pinMode(PIN_LED_RED,    OUTPUT);
  
  Serial.begin(115200);
  
  // Optimization: Reduces the wait time for Serial.readString()
  // This makes the response instantaneous even with "No Line Ending"
  Serial.setTimeout(10); 

  while (!Serial); // Wait for Serial port to be ready

  Serial.println("--- LED CONTROL SYSTEM INITIALIZED ---");
  Serial.println("Commands: 'green', 'yellow', 'red', or 'off'");
  Serial.println("System: Ready for input...");
  Serial.println("--------------------------------------");
}

void loop() {
  if (Serial.available() > 0) {
    // Safety buffer for character arrival
    delay(50); 

    // Read the content from the buffer
    String input = Serial.readString();

    // --- DATA NORMALIZATION ---
    input.trim();          // Removes leading/trailing spaces and hidden chars (\n, \r)
    input.toLowerCase();   // Handles case-insensitivity (e.g., "ReD" -> "red")

    // Ignore empty entries
    if (input.length() == 0) return;

    // --- CONTROL LOGIC ---
    if (input == "green") {
      setOnlyOneActive(PIN_LED_GREEN);
      Serial.println("[OK] Mode: GREEN");
    } 
    else if (input == "yellow") {
      setOnlyOneActive(PIN_LED_YELLOW);
      Serial.println("[OK] Mode: YELLOW");
    } 
    else if (input == "red") {
      setOnlyOneActive(PIN_LED_RED);
      Serial.println("[OK] Mode: RED");
    } 
    else if (input == "off") {
      allLedsOff();
      Serial.println("[OK] Mode: ALL OFF");
    } 
    else {
      // Error handling
      Serial.print("[ERROR] Unknown command: '");
      Serial.print(input);
      Serial.println("' - Try: green, yellow, red, or off.");
    }
  }
}

// Logic to turn on one LED and turn off the others
void setOnlyOneActive(int activePin) {
  digitalWrite(PIN_LED_GREEN,  (activePin == PIN_LED_GREEN)  ? HIGH : LOW);
  digitalWrite(PIN_LED_YELLOW, (activePin == PIN_LED_YELLOW) ? HIGH : LOW);
  digitalWrite(PIN_LED_RED,    (activePin == PIN_LED_RED)    ? HIGH : LOW);
}

// Function: Safety shutdown of all LEDs
void allLedsOff() {
  digitalWrite(PIN_LED_GREEN,  LOW);
  digitalWrite(PIN_LED_YELLOW, LOW);
  digitalWrite(PIN_LED_RED,    LOW);
}