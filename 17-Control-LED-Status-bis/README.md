# Lesson 017: Green, Yellow, and Red LEDs Serial Control

## Project Info
- **Project Name:** Green, Yellow, and Red LEDs Serial Control
- **Lesson:** [Arduino Uno R4 WiFi LESSON 17: Control Multiple LED from the Serial Monitor](https://www.youtube.com/watch?v=Ai7uqYHt_Yc&list=PLGs0VKk2DiYyn0wN335MXpbi3PRJTMmex&index=19) by Paul McWhorter
- **Revision:** 1.2 (Final Version)
- **Date:** 2026-02-22
- **Author:** SuperMechatronicEngineer

## Project Description
This project implements an sequential text-based interface using the **Serial Monitor** to control both the selection and the intensity of three LEDs (Green, Yellow, and Red) on an Arduino UNO R4 WiFi.

The system is built on a **sequential logic** that guides the user through a two-step dialogue: first selecting the LED color, then defining its intensity from 0 to 10. A key feature is the implementation of the **Weber-Fechner Law** via the exponential formula:
$$y = 2^{(x / 1.25)} - 1$$
This choice compensates for the human eye's logarithmic perception of light, ensuring that brightness increments appear uniform and natural to the viewer. Throughout the process, the code enforces **mutual exclusion** and robust input validation, filtering out non-numeric errors while maintaining near-instantaneous responsiveness.

## 📺 Video Documentation
The complete build and demonstration are available on Odysee:
- **Watch here:** [Arduino UNO R4 WiFi - Control 3 LEDs Brightness via Serial Monitor](https://odysee.com/@SuperMechatronicEngineer:8/017-Control-LED-Bis:1)

## Technical Details
* **Target Hardware:** Arduino UNO R4 WiFi.
* **Active Components:** 
    * **Digital Pin 11**: Green LED.
    * **Digital Pin 10**: Yellow LED.
    * **Digital Pin 9**: Red LED.
    * **3x 1kΩ Resistor**: Used for the LED to ensure low current draw and component longevity.
* **Baud Rate:** 115200 bps (High-speed telemetry).

## Software Logic & Architecture
* **Sequential Two-Step Interface:** The program architecture implements a blocking state logic using `while (Serial.available() == 0)`. This forces a guided workflow where the user must successfully select a valid LED color before the system prompts for the brightness level.
* **Data Normalization & Validation:** Beyond using `.trim()` and `.toLowerCase()` for color strings, the system features a robust numeric validation loop. It scans the brightness input buffer character-by-character with `isDigit()`, utilizing a `break` statement to immediately reject non-numeric entries and prevent parsing errors.
* **Performance & High-Speed Telemetry:** To ensure near-instantaneous responsiveness, the project utilizes a **115200 baud rate** combined with `Serial.setTimeout(10)`. This eliminates the default 1-second lag in serial communication, providing immediate hardware feedback.
* **Hardware Safety & Mutual Exclusion:** The architecture prioritizes electrical stability through a "Power-on Reset" in the `setup()` and a "Switch-before-Write" logic in the `loop()`. By calling `allLedsOff()` before any new `analogWrite()`, the system guarantees that only one LED is active at any given time.

## License & Credits
- **Original Tutorial:** Paul McWhorter (TopTechBoy).
- **License:** This project is licensed under [CC BY-NC-SA 4.0](../../LICENSE) (Attribution-NonCommercial-ShareAlike).