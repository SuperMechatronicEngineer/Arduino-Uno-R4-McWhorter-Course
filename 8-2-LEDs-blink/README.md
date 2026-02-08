# Lesson 008 Homework: 2-LEDs Variables

## Project Info
- **Project Name:** 2-LEDs Variables Control
- **Lesson:** [Arduino Uno R4 WiFi LESSON 8: Using Variables in Arduino](https://www.youtube.com/watch?v=Ucvwq5hFc3U&list=PLGs0VKk2DiYyn0wN335MXpbi3PRJTMmex&index=9) by Paul McWhorter
- **Revision:** 1.1 - Optimized Version
- **Date:** 2026-02-08
- **Author:** SuperMechatronicEngineer

## Project Description
This project demonstrates the fundamental use of **global variables** and **constants** to control timing patterns. Unlike previous exercises, this program manages two different LEDs (Red and Green) with distinct behaviors: a slow 10-blink cycle for the Red LED followed by a fast 5-blink cycle for the Green LED, repeating indefinitely.

## 📺 Video Documentation
The complete build and demonstration are available on Odysee:
- **Watch here:** [Arduino UNO R4 WiFi - LEDs Variables & Timing](https://odysee.com/@SuperMechatronicEngineer:8/LED-variables:b)

## Technical Details
* **Target Hardware:** Arduino UNO R4 WiFi
* **Active Components:** 
    * **1x Red LED & 1x Green LED**.
    * **2x 1000Ω Resistors**: High-value resistors chosen for safety and low current draw (approx. 3.2mA per pin).
* **Connections:** Digital Pins 2 (Red), 3 (Green) and GND.

## Logic & Software Architecture
The software prioritizes **modularity** and the **DRY (Don't Repeat Yourself)** principle:
* **Parametric Control:** All timing intervals and repetition counts are stored in global constants (`blinkIntervalRed`, `blinkTimesGreen`, etc.).
* **Semantic Indexing:** While using an array for pin management, the code logic distinguishes between the two LEDs, ensuring a clear execution order.

## License & Credits
- **Original Tutorial:** Paul McWhorter (TopTechBoy).
- **License:** This work is licensed under [CC BY-NC-SA 4.0](../../LICENSE) (Attribution-NonCommercial-ShareAlike).