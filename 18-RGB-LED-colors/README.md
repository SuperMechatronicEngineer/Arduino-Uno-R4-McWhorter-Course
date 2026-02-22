# Lesson 018: Control an RGB LED via Serial Control

## Project Info
- **Project Name:** Control an RGB LED via Serial Control
- **Lesson:** [Arduino Uno R4 WiFi LESSON 18: Controlling RGB LED with an Arduino](https://www.youtube.com/watch?v=ASHBCGGeEPk&list=PLGs0VKk2DiYyn0wN335MXpbi3PRJTMmex&index=19) by Paul McWhorter
- **Revision:** 1.2 (Final Version)
- **Date:** 2026-02-22
- **Author:** SuperMechatronicEngineer

## Project Description
This project implements a text-based interface using the **Serial Monitor** to control an RGB LED on an Arduino UNO R4 WiFi. Unlike a simple ON/OFF toggle, this system allows the user to select from eight different calibrated colors through a guided dialogue.

The program waits for the user to type a command and then instantly updates the LED. It recognizes eight distinct colors: **red, green, blue, cyan, magenta, yellow, orange**, and **white**, plus a dedicated **off** command to extinguish the light. The system is built on **linear logic** and custom hardware calibration; I manually fine-tuned the PWM ratios for complex hues (like Yellow, Orange, and White) to compensate for the varying intensities of the RGB chips. Throughout the process, the code enforces **mutual exclusion** and robust input validation, maintaining near-instantaneous responsiveness.

## 📺 Video Documentation
The complete build and demonstration are available on Odysee:
- **Watch here:** [Arduino UNO R4 WiFi - Control an RGB LED via Serial Monitor](https://odysee.com/@SuperMechatronicEngineer:8/018-RGB-LED:4)

## Technical Details
* **Target Hardware:** Arduino UNO R4 WiFi.
* **Active Components:** 
    * **Common Cathode RGB LED**: The shared negative terminal (GND) is connected directly to the breadboard's ground rail.
    * **Digital Pin 11**: Red Anode.
    * **Digital Pin 10**: Green Anode.
    * **Digital Pin 9**: Blue Anode.
    * **3x 1kΩ Resistor**: Placed on each anode (R, G, B) to ensure low current draw and component longevity.
* **Baud Rate:** 115200 bps (High-speed telemetry).

## Software Logic & Architecture
* **Responsive Command Interface:** The program architecture implements a responsive logic using `while (Serial.available() == 0)`. This structure waits for user input without idling, ensuring the system stays ready to process the next color command immediately.
* **Data Normalization & Validation:** The system uses `.trim()` and `.toLowerCase()` to handle user strings. This makes the interface robust against extra spaces or mixed-case letters, providing a seamless user experience. If an unrecognized command is entered, the system triggers a specific error alert.
* **Performance & High-Speed Telemetry:** To ensure near-instantaneous responsiveness, the project utilizes a **115200 baud rate** combined with `Serial.setTimeout(10)`. This eliminates the default 1-second lag in serial communication, providing immediate hardware feedback upon pressing Enter.
* **Hardware Safety & Mutual Exclusion:** The architecture prioritizes electrical stability through a "Power-on Reset" in the `setup()` and a "Clear-before-Write" logic in the `loop()`. By calling a dedicated function to turn off all channels before applying a new color, the system guarantees a clean transition between states and prevents unintended color mixing.

## License & Credits
- **Original Tutorial:** Paul McWhorter (TopTechBoy).
- **License:** This project is licensed under [CC BY-NC-SA 4.0](../../LICENSE) (Attribution-NonCommercial-ShareAlike).