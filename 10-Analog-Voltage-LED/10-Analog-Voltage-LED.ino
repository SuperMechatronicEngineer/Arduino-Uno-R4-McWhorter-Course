/*
 * Project: LED Breathing Effect
 * Lesson:  Arduino Uno R4 WiFi LESSON 10: Writing Analog Voltages With the Arduino
 * Revision: 1.2 - Final Version
 * Date: 2026-02-09
 * License: CC BY-NC-SA 4.0
 */

const int LED_PIN = 11;
const int FADE_DELAY = 50; 
const int BOOT_DELAY = 3000;

int brightness = 0;
int fadeAmount = 5;

const char* MSG = "Brightness: ";
const char* MSG_START = "--- Serial Monitor Initialized Successfully ---";

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  
  while (!Serial){
    ; // Wait
  }  

  // Visual header for the console
  delay(BOOT_DELAY);
  Serial.println();
  Serial.println(MSG_START);
}

void loop() {
  // 1. Monitor & Apply (Synchronized)
  Serial.print(MSG);
  Serial.println(brightness);
  analogWrite(LED_PIN, brightness);

  // 2. Logic (Asciutta)
  brightness += fadeAmount;

  if (brightness <= 0 || brightness >= 255) {
    fadeAmount = -fadeAmount; 
  }

  delay(FADE_DELAY);
}