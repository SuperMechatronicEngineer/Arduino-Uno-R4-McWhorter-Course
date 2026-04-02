# Lesson 049: 4-Button Incremental Stepper Motor Control

## Project Info
- **Project Name:** 4-Button Incremental Stepper Motor Control
- **Lesson:** [Arduino Uno R4 WiFi LESSON 49: Arduino Stepper Motor Control](https://www.youtube.com/watch?v=9yq4LZWyWc8&list=PLGs0VKk2DiYyn0wN335MXpbi3PRJTMmex&index=51) by Paul McWhorter
- **Revision:** 1.2 (Final Version)
- **Date:** 2026-04-02
- **Author:** SuperMechatronicEngineer

## Project Description
This project implements a precise manual control interface for a **28BYJ-48 stepper motor** using an **Arduino UNO R4 WiFi**. It allows for incremental rotation of the output shaft in **1° or 10°** steps in both directions via four momentary push-buttons.

The system is built on a **non-blocking architecture**, ensuring the microcontroller remains responsive to inputs even while the motor is in motion.

## 🏗️ Software Architecture (OOP)
The firmware is organized into two main C++ classes to ensure modularity and code reusability.

### 1. `StepperDriver` Class
Acts as the **Hardware Abstraction Layer (HAL)** for the motor.
* **Non-blocking Logic:** Uses `millis()` for step timing, allowing the CPU to perform other tasks between pulses.
* **Phase Management:** Implements an 8-step half-step sequence for maximum resolution.
* **Energy Saving:** Automatically releases motor coils (sets pins LOW) when idle to prevent overheating.

### 2. `ButtonManager` Class
Handles all user input logic.
* **Debouncing:** Integrated 50ms software filter to eliminate mechanical chatter.
* **Edge Detection:** Triggers commands on the **Rising Edge** (button release), ensuring exactly one action per press.
* **Encapsulation:** Stores pin states and target step counts internally, keeping the main `loop()` clean and readable.

## 📺 Video Documentation
Comprehensive project documentation is available in two parts on Odysee:
* **Hardware Teardown:** [Inside the 28BYJ-48 Stepper Motor: The 4,096 Step Secret Revealed](https://odysee.com/@SuperMechatronicEngineer:8/006-unipolar-stepper-motor:7)  
  *Detailed look at the 32-pole rotor and the gear train (9:32, 11:22, 9:27, 8:24) to explain the 64:1 reduction.*
* **Project Build & Demo:** [Arduino UNO R4 WiFi - 4-Button Incremental 28BYJ-48 Stepper Control](https://odysee.com/@SuperMechatronicEngineer:8/Arduino-UNO-R4-WiFi-Drive-a-28BYJ-48-Stepper:6)
  *Wiring and real-time functional test.*

## Technical Details
* **Control Board:** Arduino UNO R4 WiFi (Renesas RA4M1).
* **Actuator:** 28BYJ-48 Unipolar Stepper Motor (5V).
* **Driver:** ULN2003a Darlington Array.
* **Step Mode:** Half-step (8-pulse sequence) for 4,096 steps per full output revolution.
* **Power Supply:** 
    * **Logic:** 5V via Arduino USB.
    * **Motor:** External 5V DC power supply (Shared Ground with Arduino).
* **Inputs:** 4x Push-buttons using internal `INPUT_PULLUP` resistors.

### User Interface & Controls
The system maps four digital inputs to specific angular movements. Each command is triggered upon the **release** of the button to ensure a single, deliberate action:
* **Green Button (Pin 2):** Rotates the motor **+10° (Clockwise)**.
* **Black Button (Pin 3):** Rotates the motor **+1° (Clockwise)**.
* **Blue Button (Pin 4):** Rotates the motor **-1° (Counter-Clockwise)**.
* **Red Button (Pin 5):** Rotates the motor **-10° (Counter-Clockwise)**.

### 🕹️ ULN2003a Control Logic
Unlike an H-Bridge, the **ULN2003** is a high-voltage, high-current Darlington transistor array. It acts as a set of seven switches that connect the motor phases to **Ground** when the Arduino pins are **HIGH**.

For the 28BYJ-48 (Unipolar), the center taps are connected to +5V, and the ULN2003 sequences the Ground connection for each coil. This project uses a **Half-Step** sequence to achieve smoother motion and double the positioning resolution.

| Step | IN1 | IN2 | IN3 | IN4 |
| :--- | :--- | :--- | :--- | :--- |
| **1** | HIGH | LOW | LOW | LOW |
| **2** | HIGH | HIGH | LOW | LOW |
| **3** | LOW | HIGH | LOW | LOW |
| **4** | LOW | HIGH | HIGH | LOW |
| **5** | LOW | LOW | HIGH | LOW |
| **6** | LOW | LOW | HIGH | HIGH |
| **7** | LOW | LOW | LOW | HIGH |
| **8** | HIGH | LOW | LOW | HIGH |

## Software Architecture
### 1. StepperDriver Class
Encapsulates the 8-step lookup table and handles pin states. Step timing is controlled by comparing `millis()` against a 2ms `stepInterval`, ensuring the motor runs at a stable speed without halting the main loop.

### 2. Debouncing Logic
Each button input is debounced using a 50ms time window to filter mechanical chatter. To ensure a deliberate user action, the motor movement is initiated only on the **Rising Edge** of the signal (the moment the button is **released**), detected when the pin state transitions from LOW back to HIGH.

### Step Calculations
To achieve precise angular movement, the following step counts are used:
* **1° Increment:** $\frac{4096}{360} \approx 11.37$ $\rightarrow$ **11 steps**
* **10° Increment:** $\frac{4096 \times 10}{360} \approx 113.7$ $\rightarrow$ **114 steps**

### 4. Energy Management
The firmware includes a `release()` function that sets all driver inputs to **LOW** once the target step count is reached. This prevents continuous current flow through the motor coils when stationary, reducing heat in the ULN2003a chip and the motor.

## Wiring Diagram

| Pin | Function | Connection |
| :--- | :--- | :--- |
| **D2** | Input | Button: +10° (Clockwise) |
| **D3** | Input | Button: +1° (Clockwise) |
| **D4** | Input | Button: -1° (Counter-Clockwise) |
| **D5** | Input | Button: -10° (Counter-Clockwise) |
| **D8** | Output | ULN2003 IN1 (Orange) |
| **D9** | Output | ULN2003 IN2 (Yellow) |
| **D10** | Output | ULN2003 IN3 (Pink) |
| **D11** | Output | ULN2003 IN4 (Blue) |
| **GND** | Ground | Common Ground Rail |
| **5V** | Power | External Power to ULN2003 VCC |

## License & Credits
- **Original Tutorial:** Paul McWhorter (TopTechBoy).
- **License:** This project is licensed under [CC BY-NC-SA 4.0](../../LICENSE) (Attribution-NonCommercial-ShareAlike).