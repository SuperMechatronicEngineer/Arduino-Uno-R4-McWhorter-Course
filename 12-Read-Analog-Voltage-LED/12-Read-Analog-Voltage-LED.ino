/*
 * Project: LED Breathing Effect
 * Lesson: Arduino Uno R4 WiFi LESSON 12: Read Analog Voltages on the Arduino
 * Revision: 1.2 - Final Version
 * Date: 2026-02-09
 * Author: SuperMechatronicEngineer
 * License: CC BY-NC-SA 4.0
 * See README.md for full technical documentation.
 */

// Pin Definitions
const int POT_PIN = A0;
const int LED_PIN = 11;

// Constants for Mapping
const float ADC_MAX = 1023.0;
const float PWM_MAX = 255.0;

// Communication Constants
const unsigned long BAUD_RATE = 115200;
const int BOOT_DELAY = 2000;

void setup() {
  pinMode(LED_PIN, OUTPUT);

  Serial.begin(BAUD_RATE);
  while (!Serial); 
  delay(BOOT_DELAY);

  Serial.println("--- Constant Scale Factor Control Ready ---");
  Serial.println("Raw (10-bit) \t Voltage (V) \t PWM (8-bit)");
}

void loop() {
  int rawValue = analogRead(POT_PIN);

  // Calcolo con il fattore di conversione isolato
  // (PWM_MAX / ADC_MAX) è il "guadagno" del sistema
  int pwmValue = rawValue * (PWM_MAX / ADC_MAX);

  analogWrite(LED_PIN, pwmValue);

  // Stessa logica per la tensione: (5.0 / 1023.0) è il valore in Volt di un singolo step
  float voltage = rawValue * (5.0 / ADC_MAX);

  Serial.print(rawValue);
  Serial.print("\t\t ");
  Serial.print(voltage, 3);
  Serial.print(" V \t\t ");
  Serial.println(pwmValue);

  delay(20); 
}