/*
 * Project: PIR Motion Security Alarm
 * Lesson: Arduino Uno R4 WiFi LESSON 44: Playing Music On Your Arduino With a Passive Buzzer
 * Revision: 1.2 - Final Version
 * Date: 2026-03-11
 * Author: SuperMechatronicEngineer
 * License: CC BY-NC-SA 4.0
 * See README.md for full technical documentation.
 */

const uint8_t PIR_PIN = 2;      // Input from PIR sensor
const uint8_t BUZZER_PIN = 9;   // Output to Transistor base
const uint8_t LED_PIN = 12;     // Output to Red LED

void setup() {
  pinMode(PIR_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  
  // High-speed Serial communication
  Serial.begin(115200);
  while (!Serial); // Ensures serial communication is ready before proceeding

  Serial.println(F("================================"));
  Serial.println(F("   SECURITY SYSTEM INITIALIZING  "));
  Serial.println(F("================================"));

  // PIR sensors require a warm-up period to calibrate infrared levels
  Serial.print("Sensor Warm-up (10s): ");
  for (uint8_t i = 1; i <= 10; i++) {
    Serial.print(i);
    Serial.print("... ");
    delay(1000);
  }

  Serial.println(F("\n[STATUS] SYSTEM ARMED AND READY"));
}

void loop() {
  // Check if the sensor output is triggered (HIGH)
  if (digitalRead(PIR_PIN) == HIGH) {
    Serial.println(F("[!] ALERT: Motion Detected!"));
    
    digitalWrite(LED_PIN, HIGH);

    for (uint8_t i = 0; i < 5; i++) {
      tone(BUZZER_PIN, 1500); // High pitch (approx. 1.5kHz)
      delay(250);
      tone(BUZZER_PIN, 800);  // Low pitch (approx. 0.8kHz)
      delay(250);
    }
    
    noTone(BUZZER_PIN); 
    digitalWrite(LED_PIN, LOW); 

    /*
     * This small delay filters out electrical noise or "bouncing" signals that occur when
     * the buzzer stops, preventing accidental double-triggering of the PIR sensor.
     */
    delay(200); 
  }
}