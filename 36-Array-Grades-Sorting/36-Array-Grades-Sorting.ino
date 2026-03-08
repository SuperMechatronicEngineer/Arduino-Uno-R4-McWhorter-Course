/*
 * Project: Advanced Grade Analytics & Sorting System
 * Arduino Uno R4 WiFi LESSON 36: Finding Average of an Array of Numbers on Arduino
 * Revision: 1.2 - Final Version
 * Date: 2026-03-08
 * Author: SuperMechatronicEngineer
 * License: CC BY-NC-SA 4.0
 * See README.md for full technical documentation.
 */

#include <new> 

// Global variable to store the sanitized input string
String validatedInput = "";

// Function Prototype
void bubbleSortDescending(float arr[], int n);
bool isValidNumericInput(bool allowFloat);
void clearBuffer();

void setup() {
  Serial.begin(115200);
  Serial.setTimeout(100); 
  while (!Serial); 

  Serial.println(F("=============================================="));
  Serial.println(F("      SAFE GRADE STATISTICS & SORTING       "));
  Serial.println(F("=============================================="));
  Serial.println(F("Status: Ready. Acceptable Grade Range: 0 - 100"));
}

void loop() {
  int numGrades = 0;

  // 1. INPUT VALIDATION: TOTAL NUMBER OF STUDENTS
  while (numGrades <= 0) {
    Serial.println(F("\nHow many student grades do you want to process?"));
    while (Serial.available() == 0); 

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

  // 3. DATA ACQUISITION
  for (int i = 0; i < numGrades; i++) {
    float tempGrade = -1.0; 
    while (tempGrade < 0 || tempGrade > 100) {
      Serial.print(F("Enter grade (0-100) for student #"));
      Serial.print(i + 1);
      Serial.print(F(": "));

      while (Serial.available() == 0);

      if (isValidNumericInput(true)) { 
        tempGrade = validatedInput.toFloat();
      } else {
        Serial.println(F("\n[!] Error: Invalid characters or scientific notation ('e')."));
        // Note: tempGrade remains at its initial value (-1.0)
      }
      clearBuffer();

      if (tempGrade < 0 || tempGrade > 100) {
        Serial.println(F("Error: Grade must be between 0.0 and 100.0."));
      }
    }
    gradeList[i] = tempGrade;
    Serial.println(gradeList[i], 2); 
  }

  // 4. SORTING (Descending Order)
  // Call the sorting function before displaying results
  bubbleSortDescending(gradeList, numGrades);

  // 5. DATA RECAP (Now Sorted)
  Serial.println(F("\n--- Sorted Grades (Highest to Lowest) ---"));
  for (int i = 0; i < numGrades; i++) {
    Serial.print(F("Rank #"));
    Serial.print(i + 1);
    Serial.print(F(": "));
    Serial.println(gradeList[i], 2);
  }

  // 6. STATISTICAL ANALYSIS
  float sum = 0;
  // After sorting, the Max is at position [0] and the Min is at [n-1]
  float maxGrade = gradeList[0];
  float minGrade = gradeList[numGrades - 1];

  for (int i = 0; i < numGrades; i++) {
    sum += gradeList[i];
  }

  // 7. FINAL RESULTS
  Serial.println(F("\n--- FINAL STATISTICS ---"));
  Serial.print(F("Average Score: ")); Serial.println(sum / numGrades, 2);
  Serial.print(F("Highest Score: ")); Serial.println(maxGrade, 2);
  Serial.print(F("Lowest Score:  ")); Serial.println(minGrade, 2);

  // 8. HEAP MEMORY CLEANUP
  delete[] gradeList;

  Serial.println(F("\n---------------------------------------------"));
  Serial.println(F("Type ANY CHARACTER to restart a new session..."));
  while (Serial.available() == 0); 
  clearBuffer(); 
}

/*
 * Sorts an array of floats in descending order (Highest to Lowest).
 * Uses the Bubble Sort algorithm with an "Early-Exit" optimization.
 */
void bubbleSortDescending(float arr[], int n) {

  // Outer loop: Manages the number of passes through the array.
  // Each pass ensures the smallest remaining value "bubbles" to the end.
  for (int i = 0; i < n - 1; i++) {
    bool swapped = false;

    // Inner loop: Compares adjacent elements.
    // The range decreases by 'i' because the last 'i' elements are already sorted.
    for (int j = 0; j < n - i - 1; j++) {
      
      // Inverted condition: if the current element is LESS than the next one, swap them.
      if (arr[j] < arr[j + 1]) { 
        float temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
        
        // Mark that a swap occurred in this pass.
        swapped = true;
      }
    }

    // Optimization: If no two elements were swapped during a pass,
    // the array is already sorted, and we can exit the loop early.
    if (!swapped) break; 
  }
}

bool isValidNumericInput(bool allowFloat) {
  delay(10); 
  validatedInput = Serial.readString();
  validatedInput.trim(); 

  if (validatedInput.length() == 0) return false;
  bool dotFound = false;
  for (uint16_t i = 0; i < validatedInput.length(); i++) {
    char c = validatedInput.charAt(i);
    if (isDigit(c)) continue;
    if (allowFloat && c == '.') {
      if (dotFound) return false;
      dotFound = true;
      continue;
    }
    return false;
  }
  return true; 
}

void clearBuffer() {
  delay(10); 
  while (Serial.available() > 0) Serial.read(); 
}