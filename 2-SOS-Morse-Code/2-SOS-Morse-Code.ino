/*
 * Project: SOS Distress Signal
 * Lesson: How to Build Circuits With a Breadboard - Lesson 2
 * Revision: 1.0 - Initial Release
 * Date: 2026-01-28
 * License: CC BY-NC-SA 4.0
 * See README.md for full technical documentation.
 */

const int ledPin = 2;                // Pin connected to the LED
const int dotMs = 100;               // Duration of a Morse "dot" in milliseconds
const int dashMs = 3 * dotMs;        // Duration of a Morse "dash" (three times a dot)
const int signalPause = dotMs;       // Pause between dots or dashes within a letter
const int letterPause = 3 * dotMs;   // Pause between letters
const int wordPause = 7 * dotMs;     // Pause between repeated SOS signals

void setup() {
  pinMode(ledPin, OUTPUT);           // Set the LED pin as an output
}

void loop() {
  morseS();                          // Transmit Morse code for 'S' (. . .)
  delay(letterPause);               // Pause between letters
  morseO();                          // Transmit Morse code for 'O' (- - -)
  delay(letterPause);               // Pause between letters
  morseS();                          // Transmit Morse code for 'S' again
  delay(wordPause);                 // Pause before repeating SOS
}

// Transmit a Morse "dot" by turning the LED on briefly
void dot() {
  digitalWrite(ledPin, HIGH);       // Turn on the LED
  delay(dotMs);                     // Keep it on for the duration of a dot
  digitalWrite(ledPin, LOW);        // Turn off the LED
  delay(signalPause);               // Pause between signals
}

// Transmit a Morse "dash" by turning the LED on longer
void dash() {
  digitalWrite(ledPin, HIGH);       // Turn on the LED
  delay(dashMs);                    // Keep it on for the duration of a dash
  digitalWrite(ledPin, LOW);        // Turn off the LED
  delay(signalPause);  // Pause between signals 
}

// Transmit the letter 'S' in Morse code (. . .)
void morseS() {
  for (int i = 0; i < 3; i++) {
    dot();                          // Send a dot
  }
}

// Transmit the letter 'O' in Morse code (- - -)
void morseO() {
  for (int i = 0; i < 3; i++) {
    dash();                         // Send a dash
  }
}