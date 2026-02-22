/*
 * Project: RGB LED Color Selector
 * Lesson: Arduino Uno R4 WiFi LESSON 18: Controlling RGB LED with an Arduino
 * Revision: 1.2 - Final Version
 * Date: 2026-02-22
 * Author: SuperMechatronicEngineer
 * License: CC BY-NC-SA 4.0
 * See README.md for full technical documentation.
 */

// Pin Definitions
const int RED_PIN   = 11;
const int GREEN_PIN = 10;
const int BLUE_PIN  = 9;

void setup() {
  pinMode(RED_PIN,   OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN,  OUTPUT);
  
  Serial.begin(115200);
  Serial.setTimeout(10); 

  while (!Serial); 

  // Power-on Reset
  allLedsOff();

  Serial.println("--- RGB LED INTERFACE INITIALIZED ---");
}

void loop() {
  // GUIDED INTERACTION: The system waits for the user
  Serial.println("\nStep 1: Enter color name (red, green, blue, cyan, magenta, yellow, orange, white, off):");

  // Wait until user provides input (The "Wall")
  while (Serial.available() == 0);
  
  delay(50); // Safety buffer for character arrival
  String colorInput = Serial.readString();
  colorInput.trim();
  colorInput.toLowerCase();

  // Clear previous state before applying new color
  allLedsOff();

  bool validColor = true;

  // COLOR SELECTION LOGIC
  if (colorInput == "red")          { analogWrite(RED_PIN, 255); }
  else if (colorInput == "green")   { analogWrite(GREEN_PIN, 255); }
  else if (colorInput == "blue")    { analogWrite(BLUE_PIN, 255); }
  else if (colorInput == "cyan")    { analogWrite(GREEN_PIN, 255); analogWrite(BLUE_PIN, 255); }
  else if (colorInput == "magenta") { analogWrite(RED_PIN, 255);   analogWrite(BLUE_PIN, 255); }
  else if (colorInput == "yellow")  { analogWrite(RED_PIN, 255);   analogWrite(GREEN_PIN, 150); }
  else if (colorInput == "orange")  { analogWrite(RED_PIN, 255);   analogWrite(GREEN_PIN, 25); }
  else if (colorInput == "white")   { analogWrite(RED_PIN, 255);   analogWrite(GREEN_PIN, 225); analogWrite(BLUE_PIN, 200); }
  else if (colorInput == "off")     { /* Already cleared by allLedsOff() */ }
  else {
    validColor = false;
  }

  // USER FEEDBACK
  if (validColor) {
    Serial.print("[SUCCESS] LED set to: ");
    colorInput.toUpperCase(); 
    Serial.println(colorInput);
  } else {
    Serial.print("[ERROR] '");
    Serial.print(colorInput);
    Serial.println("' is not a valid color name.");
  }
}

void allLedsOff() {
  analogWrite(RED_PIN,   0);
  analogWrite(GREEN_PIN, 0);
  analogWrite(BLUE_PIN,  0);
}