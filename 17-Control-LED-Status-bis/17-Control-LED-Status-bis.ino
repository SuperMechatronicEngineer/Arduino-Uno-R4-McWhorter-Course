/*
 * Project: Green, Yellow, and Red LEDs Serial Brightness Selector
 * Lesson: Arduino Uno R4 WiFi LESSON 17: Control Multiple LED from the Serial Monitor
 * Revision: 1.2 - Final Version
 * Date: 2026-02-22
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
  
  // Optimization: Reduces wait time for Serial.readString()
  Serial.setTimeout(10); 

  while (!Serial); // Wait for Serial port to be ready

  // 1. POWER-ON RESET: Ensure all LEDs start in the OFF state
  allLedsOff();

  Serial.println("--- LED CONTROL SYSTEM INITIALIZED ---");
  Serial.println("System: Ready for input...");
}

void loop() {
  Serial.println("\nStep 1: Enter color ('green', 'yellow', 'red'):");

  // Wait until user provides the color input
  while (Serial.available() == 0);
  
  delay(50); // Safety buffer for character arrival
  String colorInput = Serial.readString();
  colorInput.trim();
  colorInput.toLowerCase();

  int targetPin = -1;
  if (colorInput == "green")       targetPin = PIN_LED_GREEN;
  else if (colorInput == "yellow") targetPin = PIN_LED_YELLOW;
  else if (colorInput == "red")    targetPin = PIN_LED_RED;

  // If color is invalid, restart the loop
  if (targetPin == -1) {
    Serial.print("[ERROR] Invalid color: '"); 
    Serial.print(colorInput);
    Serial.println("'. Please try again.");
    return; 
  }

  // Formatting for user feedback
  colorInput.toUpperCase(); 
  Serial.print("[SELECTED] "); 
  Serial.println(colorInput);

  // --- STEP 2: REQUEST BRIGHTNESS ---
  bool validBrightness = false;
  while (!validBrightness) {
    Serial.println("Step 2: Enter brightness level (0 to 10):");
    
    // Wait until user provides the numeric input
    while (Serial.available() == 0);
    
    delay(50);
    String brightnessInput = Serial.readString();
    brightnessInput.trim();

    // Numeric Validation Logic
    bool isNumeric = (brightnessInput.length() > 0);
    for (byte i = 0; i < brightnessInput.length(); i++) {
      if (!isDigit(brightnessInput[i])) {
        isNumeric = false;
        break;
      }
    }

    if (isNumeric) {
      int level = brightnessInput.toInt();
      if (level >= 0 && level <= 10) {
        // Exponential Transfer Function for natural human perception
        // Formula: y = 2^(x/1.25) - 1
        float yExp = pow(2, (level / 1.25)) - 1;

        // 2. MUTUAL EXCLUSION: Shut down previous LED before lighting the new one
        allLedsOff();
        analogWrite(targetPin, (int)yExp);

        Serial.print("[SUCCESS] "); 
        Serial.print(colorInput);
        Serial.print(" set to level "); 
        Serial.print(level);
        Serial.print(" (PWM: ");
        Serial.print((int)yExp);
        Serial.println(")");
        
        validBrightness = true; // Exit the brightness selection loop
      } else {
        Serial.println("[REJECTED] Out of range. Enter a number between 0 and 10.");
      }
    } else {
      Serial.print("[REJECTED] '");
      Serial.print(brightnessInput);
      Serial.println("' is not a valid number.");
    }
  }
}

// Function to shut down all LEDs.
void allLedsOff() {
  analogWrite(PIN_LED_GREEN,  0);
  analogWrite(PIN_LED_YELLOW, 0);
  analogWrite(PIN_LED_RED,    0);
}