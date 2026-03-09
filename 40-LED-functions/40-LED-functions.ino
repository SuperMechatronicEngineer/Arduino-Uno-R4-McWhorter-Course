/*
 * Project: Smart Dimmer: Exponential LED Control
 * Lesson: Arduino Uno R4 WiFi LESSON 40: Using Arduino Functions with Local Variables Explained
 * Revision: 1.2 - Final Version
 * Date: 2026-03-09
 * Author: SuperMechatronicEngineer
 * License: CC BY-NC-SA 4.0
 * See README.md for full technical documentation.
 */

// --- Configuration ---
const int POT_PIN = A0;
const int LED_PIN = 10;
const int NOISE_THRESHOLD = 3;

// Pre-calculated ratio to map ADC (0-1023) to exponent range (0-8).
// Uses 'f' suffix to ensure 32-bit float math, optimizing R4 FPU performance.
const float ADC_TO_EXP_RATIO = 8.0f / 1023.0f;

// State tracking
int lastStableX = -1; 

// Forward Declaration
int readADC(int pin);
int calculatePWM(int raw);
float calculateVoltage(int raw);
void displayAndActuate(int raw, float v, int pwm);

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);
  while (!Serial);
  Serial.println(F("--- Educational PWM: Exponential Logic ---"));
}

void loop() {
  // 1. INPUT
  int currentRaw = readADC(POT_PIN);

  // Trigger update only on significant change
  if (currentRaw != lastStableX) {
    lastStableX = currentRaw;

    // 2. PROCESS
    int pwmValue = calculatePWM(lastStableX);
    float voltage = calculateVoltage(lastStableX);

    // 3. OUTPUT
    displayAndActuate(lastStableX, voltage, pwmValue);
  }
}

// --- FUNCTION 1: INPUT ---
int readADC(int pin) {
  analogRead(pin); // Stability read
  int val = analogRead(pin);

  // Noise gate: if change is too small, stick to the last stable value
  if (abs(val - lastStableX) <= NOISE_THRESHOLD) {
    return lastStableX;
  }
  
  // Force 0 at the bottom of the dial
  if (val < NOISE_THRESHOLD + 1) return 0;
  
  return val;
}

// --- FUNCTION 2: PROCESS ---
int calculatePWM(int raw) {
  /* * THE MATH EXPLAINED:
   * To achieve a natural dimming effect, we use an exponential curve (Base 2).
   * 1. Scale input (0-1023) to an exponent range (0-8) using ADC_TO_EXP_RATIO.
   * 2. Calculate 2^exponent. At max (2^8), we get 256.
   * 3. Subtract 1.0f to shift the range to 0-255 (perfect for PWM).
   * 4. Result: 2^0 - 1 = 0 (Min) | 2^8 - 1 = 255 (Max).
   */
  float exponent = (float)raw * ADC_TO_EXP_RATIO; 
  float yExp = exp2f(exponent) - 1.0f;
  
  return (int)constrain(round(yExp), 0, 255);
}

float calculateVoltage(int raw) {
  // Standard 5V assumption for simplicity
  return (float)raw * (5.0 / 1023.0);
}

// --- FUNCTION 3: OUTPUT ---
void displayAndActuate(int raw, float v, int pwm) {
  analogWrite(LED_PIN, pwm);

  Serial.print(F("ADC: "));   Serial.print(raw);
  Serial.print(F("\tV: "));   Serial.print(v, 2);
  Serial.print(F("\tPWM: ")); Serial.println(pwm);
}