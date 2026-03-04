/*
 * Project: Interactive DHT22 Climate Monitor for Arduino UNO R4 WiFi
 * Lesson: Arduino Uno R4 WiFi LESSON 31: Measuring Temperature and Humidity Using the DHT11
 * Revision: 1.2 - Final Version
 * Date: 2026-03-04
 * Author: SuperMechatronicEngineer
 * License: CC BY-NC-SA 4.0
 * See README.md for full technical documentation.
 */

#include <DHT.h>
#include "ArduinoGraphics.h"
#include "Arduino_LED_Matrix.h"

// HARDWARE CONFIGURATION
#define DHTPIN 4          // DHT22 data pin connected to digital pin 4
#define DHTTYPE DHT22     // DHT22 sensor type
#define BUTTON_PIN 2      // Push button connected to pin 2 (with internal pull-up)

// TIMING VARIABLES
unsigned long lastSensorRead;           // Last time sensor was read
const unsigned long sensorInterval = 2000;  // Read sensor every 2 seconds (background update)

// BUTTON DEBOUNCING VARIABLES
uint8_t lastButtonState = HIGH;                  // Previous button state (HIGH = not pressed with pull-up)
uint8_t buttonState = HIGH;                       // Current button state
unsigned long lastDebounceTime = 0;           // Last time button state changed
const unsigned long debounceDelay = 50;       // Debounce delay in milliseconds

// OBJECTS DECLARATION
DHT dht(DHTPIN, DHTTYPE);                     // DHT22 sensor object
ArduinoLEDMatrix matrix;                       // LED Matrix object (UNO R4 built-in)

// SENSOR VARIABLES
float humidity = 0;                            // Relative humidity in %
float temperature = 0;                          // Temperature in Celsius
float heatIndex = 0;                            // Heat index in Celsius

void setup() {
  Serial.begin(115200);
  while (!Serial);  // Wait for Serial port to connect (useful for some boards)
  
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  
  // Initialize DHT22 sensor
  dht.begin();
  
  // Initialize LED Matrix
  matrix.begin();
  
  lastSensorRead = millis();
  
  // Print startup message
  Serial.println(F("==========================================================="));
  Serial.println(F("          DHT22 + LED Matrix with Button (UNO R4)         "));
  Serial.println(F("==========================================================="));
  Serial.println(F("Press the button to display data on Serial and LED Matrix"));
  Serial.println();
}

void loop() {
  // Get current time (milliseconds since program started)
  unsigned long currentMillis = millis();

  // SENSOR READING
  if (currentMillis - lastSensorRead >= sensorInterval) {
    lastSensorRead = currentMillis;  // Update last read time

    // Read humidity and temperature from DHT22
    humidity = dht.readHumidity();
    temperature = dht.readTemperature();  // Celsius by default
  }

  // BUTTON HANDLING WITH DEBOUNCE (Detects when button is PRESSED)
  uint8_t reading = digitalRead(BUTTON_PIN);  // Read current button state

  // If button state changed, reset debounce timer
  if (reading != lastButtonState) {
    lastDebounceTime = currentMillis;
  }

  // If enough time has passed since last change, consider it stable
  if ((currentMillis - lastDebounceTime) > debounceDelay) {
    // If button state actually changed from previous stable state
    if (reading != buttonState) {
      buttonState = reading;  // Update stable state

      // BUTTON PRESS DETECTED (LOW with pull-up configuration)
      if (buttonState == LOW) {
        
        // Check if sensor readings are valid (not NaN)
        if (!isnan(humidity) && !isnan(temperature)) {
          // Calculate heat index (apparent temperature)
          // false parameter = use Celsius for calculation
          heatIndex = dht.computeHeatIndex(temperature, humidity, false);

          // STEP 1: PRINT DATA TO SERIAL MONITOR
          Serial.println(F("\n=== BUTTON PRESSED ==="));
          Serial.print(F("Temp: "));
          Serial.print(temperature, 1);         // 1 decimal place
          Serial.print(F("C | Humidity: "));
          Serial.print(humidity, 1);            // 1 decimal place
          Serial.print(F("% | Heat Index: "));
          Serial.print(heatIndex, 1);           // 1 decimal place
          Serial.println(F("C"));
          
          // STEP 2: CREATE SCROLLING TEXT FOR LED MATRIX (Spaces at beginning and end ensure clean scrolling)
          String scrollText = "  T:" + String(temperature, 1) + "C H:" + String(humidity, 1) + "% HI:" + String(heatIndex, 1) + "C  ";
          
          // STEP 3: START SCROLLING ON LED MATRIX 
          // Note: This function is BLOCKING - program waits here until scrolling completes
          matrix.beginDraw();                      // Start drawing on matrix
          matrix.textScrollSpeed(100);              // Set scrolling speed (required)
          matrix.textFont(Font_5x7);               // Use 5x7 pixel font (required)
          matrix.beginText(0, 1, 0xFF);            // Position (x=0, y=1) and max brightness
          matrix.println(scrollText);              // Add text to scroll
          matrix.endText(SCROLL_LEFT);             // Start scrolling left
          matrix.endDraw();                        // End drawing
        } else {
          // Error message if sensor readings are invalid
          Serial.println(F("ERROR: Invalid sensor readings (NaN)"));
        }
      }
    }
  }

  // Save current button state for next loop iteration
  lastButtonState = reading;
}