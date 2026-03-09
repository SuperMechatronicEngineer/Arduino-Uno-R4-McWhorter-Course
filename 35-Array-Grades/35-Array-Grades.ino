/*
 * Project: Dynamic Grades Acquisition System
 * Lesson: Arduino Uno R4 WiFi LESSON 35: Understanding and Using Arrays in Projects
 * Revision: 1.2 - Final Version
 * Date: 2026-03-08
 * Author: SuperMechatronicEngineer
 * License: CC BY-NC-SA 4.0
 * See README.md for full technical documentation.
 */

#include <new> 

// Global variable to store the sanitized input string
String validatedInput = "";

void setup() {
  Serial.begin(115200);
  Serial.setTimeout(100); 
  while (!Serial); 

  Serial.println(F("=============================================="));
  Serial.println(F("         SAFE GRADE STATISTICS SYSTEM        "));
  Serial.println(F("=============================================="));
  Serial.println(F("Status: Ready. Acceptable Grade Range: 0 - 100"));
}

void loop() {
  int numGrades = 0;

  // 1. INPUT VALIDATION: TOTAL NUMBER OF STUDENTS (Integers Only)
  while (numGrades <= 0) {
    Serial.println(F("\nHow many student grades do you want to process?"));
    while (Serial.available() == 0); 

    // 'false' means NO decimal points allowed for student count
    if (isValidNumericInput(false)) { 
      numGrades = validatedInput.toInt();
    } else {
      Serial.println(F("[!] Error: Only plain integers (0-9) allowed here."));
    }
    clearBuffer(); 

    if (numGrades <= 0) Serial.println(F("Error: Please enter a positive integer."));
  }

  // 2. SAFE DYNAMIC HEAP ALLOCATION
  float* gradeList = new (std::nothrow) float[numGrades];
  if (gradeList == nullptr) {
    Serial.println(F("!!! FATAL ERROR: Out of Memory !!!"));
    return; 
  }

  // 3. DATA ACQUISITION WITH STRICT VALIDATION (Decimals Allowed)
  for (int i = 0; i < numGrades; i++) {
    float tempGrade = -1.0; 

    while (tempGrade < 0 || tempGrade > 100) {
      Serial.print(F("Enter grade (0-100) for student #"));
      Serial.print(i + 1);
      Serial.print(F(": "));

      while (Serial.available() == 0);

      // 'true' means ONE decimal point is allowed for grades
      if (isValidNumericInput(true)) { 
        tempGrade = validatedInput.toFloat();
      } else {
        Serial.println(F("\n[!] Error: Invalid characters or scientific notation ('e')."));
      }
      clearBuffer();

      if (tempGrade < 0 || tempGrade > 100) {
        Serial.println(F("Error: Grade must be between 0.0 and 100.0."));
      }
    }
    
    gradeList[i] = tempGrade;
    Serial.println(gradeList[i], 2); 
  }

  // 4. DATA RECAP
  Serial.println(F("\n--- Entered Grades Recap ---"));
  for (int i = 0; i < numGrades; i++) {
    Serial.print(F("Student #"));
    Serial.print(i + 1);
    Serial.print(F(": "));
    Serial.println(gradeList[i], 2);
  }

  // 5. STATISTICAL ANALYSIS (Scanning Algorithm)
  float sum = 0;
  float maxGrade = -1.0;
  float minGrade = 101.0;

  for (int i = 0; i < numGrades; i++) {
    float current = gradeList[i];
    sum += current;
    if (current > maxGrade) maxGrade = current;
    if (current < minGrade) minGrade = current;
  }

  // 6. FINAL RESULTS
  Serial.println(F("\n--- FINAL STATISTICS ---"));
  Serial.print(F("Average Score: ")); Serial.println(sum / numGrades, 2);
  Serial.print(F("Highest Score: ")); Serial.println(maxGrade, 2);
  Serial.print(F("Lowest Score:  ")); Serial.println(minGrade, 2);

  // 7. HEAP MEMORY CLEANUP
  delete[] gradeList;

  Serial.println(F("\n---------------------------------------------"));
  Serial.println(F("Session complete. Heap memory released."));
  Serial.println(F("Type ANY CHARACTER to restart a new session..."));
  while (Serial.available() == 0); 
  clearBuffer(); 
}

/**
 * Custom Buffer Validator
 * Scans the entire input string to ensure it contains only digits and (optionally) one dot.
 * Effectively blocks 'e', 'E', '-', '+', and alphabetic noise.
 */
bool isValidNumericInput(bool allowFloat) {
  delay(10); // Short delay to ensure buffer is full
  
  validatedInput = Serial.readString();
  validatedInput.trim(); 

  if (validatedInput.length() == 0) return false;

  bool dotFound = false;

  for (uint16_t i = 0; i < validatedInput.length(); i++) {
    char c = validatedInput.charAt(i);

    // Standard digit check
    if (isDigit(c)) continue;

    // Decimal point logic
    if (allowFloat && c == '.') {
      if (dotFound) return false; // Reject if a second dot is found
      dotFound = true;
      continue;
    }

    // Reject anything else (including scientific 'e')
    return false;
  }
  return true; 
}

void clearBuffer() {
  delay(10); 
  while (Serial.available() > 0) Serial.read(); 
}