# Lesson 003 Homework: Simultaneous LED Blinker

## Project Info
- **Project Name:** Knight Rider LED Effect
- **Lesson:** [Arduino Uno R4 Wifi LESSON 3: Blink an LED With the Arduino](https://www.youtube.com/watch?v=0SENIWPdPhQ&list=PLGs0VKk2DiYyn0wN335MXpbi3PRJTMmex&index=4) by Paul McWhorter
- **Revision:** 1.0 (Initial Release)
- **Date:** 2026-02-08
- **Author:** SuperMechatronicEngineer

## Project Description
This project expands upon the basic blinking circuit by controlling an array of 4 LEDs simultaneously. The primary objective is to transition from individual pin management to **array-based addressing**, demonstrating how to synchronize multiple hardware outputs using efficient iterative loops.

## 📺 Video Documentation
The complete build and demonstration are available on Odysee:
- **Watch here:** [Arduino UNO R4 WiFi - Blinking LEDs](https://odysee.com/@SuperMechatronicEngineer:8/Arduino-UNO-R4-Blinking-LEDs:1)

## Technical Details
* **Target Hardware:** Arduino UNO R4 WiFi
* **Active Components:** 
    * **4x Red LEDs** (External).
    * **4x 1000Ω Resistors**: High-value resistors chosen for safety and low current draw (approx. 3.2mA per pin).
* **Connections:** Digital Pins 2, 3, 4, 5 and GND.

## Logic & Software Architecture
The software is designed for scalability and memory integrity:
* **Array-based Addressing:** Pins are stored in a `ledPins[]` array, allowing the system to scale without modifying the core logic.
* **Iterative State Management:** Instead of redundant code blocks for each pin, the system uses `for` loops to iterate through the array. This ensures that all LEDs transition between HIGH and LOW states in a single execution cycle.

## License & Credits
- **Original Tutorial:** Paul McWhorter (TopTechBoy).
- **License:** This work is licensed under [CC BY-NC-SA 4.0](../../LICENSE) (Attribution-NonCommercial-ShareAlike).