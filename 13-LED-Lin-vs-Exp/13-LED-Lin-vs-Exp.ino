/*
 * Project: Potentiometer LED Control - Linear vs. Exponential
 * Lesson:  Arduino Uno R4 WiFi LESSON 13: Dimmable LED Controlled by a Potentiometer
 * Revision: 1.2 - Final Version
 * Date: 2026-02-09
 * License: CC BY-NC-SA 4.0
 */

// Pin Definitions
const int POT_PIN = A0;
const int LED_LINEAR = 11;
const int LED_EXPONENTIAL = 10;

// Timing Constants
const unsigned long SERIAL_INTERVAL = 200; // Update serial monitor every 200ms
unsigned long lastSerialTime = 0;          // Stores the last update timestamp

// Communication Constants
const unsigned long BAUD_RATE = 115200;
const int BOOT_DELAY = 2000;

void setup() {
  // Initialize LED Pins
  pinMode(LED_LINEAR, OUTPUT);
  pinMode(LED_EXPONENTIAL, OUTPUT);

  // Initialize Serial Communication
  Serial.begin(BAUD_RATE);
  while (!Serial); // Wait for Serial connection (specific for R4/USB)
  delay(BOOT_DELAY);

  Serial.println("--- Dual Mode LED Control: Time-Based Telemetry ---");
  Serial.println("Raw\tVoltage\tLinear\tExp");
}

void loop() {
  // 1. Acquisition and Calculation (Executed at maximum CPU speed)
  int x = analogRead(POT_PIN);
  float voltage = x * (5.0 / 1023.0);
  float yLinear = x * (255.0 / 1023.0);
  
  // Exponential base-2 function: y = 2^(x / 127.875) - 1
  float yExp = pow(2, (x / 127.875)) - 1;

  // 2. Hardware Output (Immediate responsiveness to trimmer movement)
  analogWrite(LED_LINEAR, (int)yLinear);
  analogWrite(LED_EXPONENTIAL, (int)yExp);

  // 3. Timed Telemetry (Decoupled from loop speed using millis)
  unsigned long currentTime = millis();
  if (currentTime - lastSerialTime >= SERIAL_INTERVAL) {
    lastSerialTime = currentTime;

    Serial.print(x);
    Serial.print("\t");
    Serial.print(voltage, 2);
    Serial.print("V\t");
    Serial.print((int)yLinear);
    Serial.print("\t");
    Serial.println((int)yExp);
  }
}