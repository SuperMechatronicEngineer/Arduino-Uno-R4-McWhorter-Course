# Lesson 014: Linear vs Exponential LED Control via Serial Monitor

## Project Info
- **Project Name:** Linear vs Exponential LED Control via Serial Monitor
- **Lesson:** [Arduino Uno R4 WiFi LESSON 14: Read User Input From the Serial Monitor](https://www.youtube.com/watch?v=GpsP5zySI_A&list=PLGs0VKk2DiYyn0wN335MXpbi3PRJTMmex&index=21) by Paul McWhorter
- **Revision:** 1.2 (Final Version)
- **Date:** 2026-02-19
- **Author:** SuperMechatronicEngineer

## Project Description
This project explores the relationship between mathematical functions and human visual perception by interfacing the **Serial Monitor** with an Arduino UNO R4 WiFi.

The system uses a **serial communication logic** to process user commands. By entering a value from **0 to 10**, the microcontroller simultaneously drives two LEDs to compare a **linear relationship** against a **base-2 exponential function**. This setup demonstrates how different transfer functions affect the perceived smoothness of light dimming and how to implement a stable, lag-free digital interface.

## 📺 Video Documentation
The complete build and demonstration are available on Odysee:
- **Watch here:** [Arduino UNO R4 WiFi - Linear vs Exponential LED Control via Serial Monitor](https://odysee.com/@SuperMechatronicEngineer:8/014-LED-Voltage-Serial:1)

## Technical Details
* **Target Hardware:** Arduino UNO R4 WiFi.
* **Active Components:** 
    * **2x Red LEDs**.
    * **2x 1kΩ Resistor**: Used for the LED to ensure low current draw and component longevity.
* **Baud Rate:** 115200 bps (High-speed telemetry).
* **Connections:** Digital Pin 11 (Linear Output), Digital Pin 10 (Exponential Output).

## Software Logic & Architecture
* **Strict Serial Validation:** The architecture implements a byte-by-byte buffer scan. It uses `isDigit()` and `isSpace()` filters to ensure that only pure numeric strings are processed, immediately rejecting invalid characters (letters/symbols) to prevent hardware state errors.
* **Latency Optimization:** By manually handling the serial buffer, the logic bypasses the standard 1000ms `Serial.parseInt()` timeout, achieving near-instantaneous LED updates upon user input.
* **Linear Transfer Function (Pin 11):** Implements a direct scaling formula $y = x \cdot 25.5$. This highlights a constant scale factor that maps the user-defined 0-10 range directly to the 8-bit PWM resolution (0-255).
* **Exponential Mapping (Pin 10):** Uses the base-2 power formula $y = 2^{(x / 1.25)} - 1$. This curve is specifically designed to create a natural brightness progression, compensating for the logarithmic sensitivity of human vision and providing a smoother dimming experience compared to the linear output.

## License & Credits
- **Original Tutorial:** Paul McWhorter (TopTechBoy).
- **License:** This project is licensed under [CC BY-NC-SA 4.0](../../LICENSE) (Attribution-NonCommercial-ShareAlike).