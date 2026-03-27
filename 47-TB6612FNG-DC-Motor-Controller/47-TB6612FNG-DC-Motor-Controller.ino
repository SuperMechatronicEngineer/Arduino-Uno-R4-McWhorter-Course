/*
 * Project: DC Motor Control using TB6612FNG
 * Lesson: Arduino Uno R4 WiFi LESSON 47: Bidirectional DC Motor Control With the TA6586 Motor Controller
 * Revision: 1.2 - Final Version
 * Note: Upgraded to TB6612FNG (Toshiba) over TA6586 for superior efficiency and versatility.
 * Date: 2026-03-27
 * Author: SuperMechatronicEngineer
 * License: CC BY-NC-SA 4.0
 * See README.md for full technical documentation.
 */

#include <Arduino.h>

// === Pin Mapping (constexpr for compile-time optimization) ===
constexpr uint8_t PIN_PWMA   = 5;      // Speed control (PWM)
constexpr uint8_t PIN_AI1    = 3;      // Direction Input 1
constexpr uint8_t PIN_AI2    = 4;      // Direction Input 2
constexpr uint8_t PIN_BUTTON = 6;      // Toggle Button (Internal Pull-up)
constexpr uint8_t PIN_POT    = A0;     // Speed Potentiometer

// === System Constants ===
constexpr uint32_t DEBOUNCE_DELAY_MS = 150; 
constexpr uint32_t INERTIA_DELAY_MS  = 300; 
constexpr uint16_t ADC_RESOLUTION    = 1024; // 10-bit Analog resolution
constexpr uint16_t PWM_MAX_VAL       = ADC_RESOLUTION - 1;

// --- Calibration Constants (Adjusted for 4.65V supply) ---
constexpr uint16_t POT_MIN_RAW = 5;    
constexpr uint16_t POT_MAX_RAW = 1015; 
constexpr uint16_t DEADZONE    = 5;    // Noise floor for absolute zero

// === Shared State (accessed by ISR) ===
volatile bool g_directionChangeRequested = false;
volatile uint32_t g_lastInterruptTime    = 0;

// === Internal State Machine Variables (Global scope) ===
bool m_isForward         = true;
bool m_isWaitingForStop  = false;
uint32_t m_stopStartTime = 0;

// === Function Prototypes ===
void handleButtonInterrupt();
void applyDirectionHardware();
void updateTelemetry(uint16_t currentSpeed);

void setup() {
  // 1. Initialize Serial with R4 Synchronization
  Serial.begin(115200);
  while (!Serial) { } 

  // 2. Configure Pin Modes
  pinMode(PIN_PWMA, OUTPUT);
  pinMode(PIN_AI1, OUTPUT);
  pinMode(PIN_AI2, OUTPUT);
  
  // 3. Configure Input with Internal Pull-up (Pin 6 to GND)
  pinMode(PIN_BUTTON, INPUT_PULLUP);
  
  // 4. Attach Hardware Interrupt (Falling Edge for Active-LOW)
  attachInterrupt(digitalPinToInterrupt(PIN_BUTTON), handleButtonInterrupt, FALLING);

  // 5. Initial Hardware State
  applyDirectionHardware();        // Set initial orientation
  analogWriteResolution(10);       // Match R4 capability (0-1023)
  
  Serial.println(F("--- SYSTEM READY ---"));
  Serial.println(F("Logic: Linear Interpolation & Pre-calc Clipping"));
}

void loop() {
  // 1. Read Raw Value
  uint16_t rawValue = analogRead(PIN_POT);
  int32_t potValue = 0;

  // 2. Pre-calculation Clipping
  if (rawValue <= POT_MIN_RAW) {
    potValue = 0;
  } 
  else if (rawValue >= POT_MAX_RAW) {
    potValue = PWM_MAX_VAL;
  } 
  else {
    // 3. Linear Interpolation (y = m * (x - x1))
    // Use int32_t for intermediate math to prevent overflow
    potValue = (int32_t)(rawValue - POT_MIN_RAW) * PWM_MAX_VAL / (POT_MAX_RAW - POT_MIN_RAW);
  }

  // 4. Deadzone Filter (Software Stability)
  if (potValue < DEADZONE) potValue = 0;

  // --- State A: Handling Interrupt Request ---
  if (g_directionChangeRequested) {
    g_directionChangeRequested = false;
    m_isWaitingForStop = true;
    m_stopStartTime = millis();
    
    analogWrite(PIN_PWMA, 0); // Immediate Preemptive Stop
    Serial.println(F("[EVENT] Direction change detected."));
  }

  // --- State B: Safe-Inversion Delay Logic ---
  if (m_isWaitingForStop) {
    if (millis() - m_stopStartTime >= INERTIA_DELAY_MS) {
      m_isForward = !m_isForward;     // Toggle internal state
      applyDirectionHardware();       // Update H-Bridge pins
      m_isWaitingForStop = false;     // Resume normal operation
      Serial.print(F("[STATUS] Motor inverted to: "));
      Serial.println(m_isForward ? F("FORWARD") : F("REVERSE"));
    }
  } 
  else {
    // --- State C: Normal Speed Modulation ---
    analogWrite(PIN_PWMA, potValue);
  }

  // Periodic Telemetry (Non-blocking)
  updateTelemetry((uint16_t)potValue);
}

// === Interrupt Service Routine (ISR) ===
void handleButtonInterrupt() {
  uint32_t currentTime = millis();
  // Hardware-level software debounce
  if (currentTime - g_lastInterruptTime > DEBOUNCE_DELAY_MS) {
    g_directionChangeRequested = true;
    g_lastInterruptTime = currentTime;
  }
}

// === Hardware Abstraction Layer (HAL) Helpers ===
void applyDirectionHardware() {
  digitalWrite(PIN_AI1, m_isForward ? HIGH : LOW);
  digitalWrite(PIN_AI2, m_isForward ? LOW : HIGH);
}

void updateTelemetry(uint16_t currentSpeed) {
  static uint32_t lastReport = 0;
  if (millis() - lastReport > 250) { // Update every 250ms
    Serial.print(F("PWM_CMD: ")); Serial.print(currentSpeed);
    Serial.print(F(" | DIR: ")); Serial.println(m_isForward ? "FWD" : "REV");
    lastReport = millis();
  }
}