# Lesson 003 Homework: Bidirectional LED Sequencer (Knight Rider)

## Project Info
- **Project Name:** Knight Rider LED Effect
- **Lesson:** [Arduino Uno R4 Wifi LESSON 3: Blink an LED With the Arduino](https://www.youtube.com/watch?v=0SENIWPdPhQ&list=PLGs0VKk2DiYyn0wN335MXpbi3PRJTMmex&index=4) by Paul McWhorter
- **Revision:** 1.0 (Initial Release)
- **Date:** 2026-02-06
- **Author:** SuperMechatronicEngineer

## Project Description
This project implements a bidirectional LED sequencer, commonly known as the **"Knight Rider"** or "Supercar" effect. Building upon the single-LED circuit from Lesson 2, this system expands to a multiple-output array. The primary objective is to demonstrate efficient pin management using **arrays** and to implement optimized control logic through iterative loops.

## 📺 Video Documentation
The complete build and demonstration are available on Odysee:
- **Watch here:** [Arduino UNO R4 WiFi - Knight Rider](https://odysee.com/@SuperMechatronicEngineer:8/Arduino-UNO-R4-Knight-Rider:9)

## Technical Details
* **Target Hardware:** Arduino UNO R4 WiFi
* **Active Components:** * **4x Red LEDs** (External).
    * **4x 1000Ω Resistors**: Selected to provide optimal brightness while keeping current within safe operating limits.
* **Connections:** Digital Pins 2, 3, 4, 5 and GND.

## Logic & Software Architecture
The software is designed for scalability and memory integrity:
* **Array-based Addressing:** Pins are stored in a `ledPins[]` array, allowing the system to scale without modifying the core logic.
* **Memory Safety:** The `for` loops utilize strict exit conditions (`i < numLeds`) to prevent out-of-bounds indexing errors.
* **Sequence Optimization:** The return sequence is calibrated (`numLeds - 2` down to `1`) to prevent "double-blinking" at the boundary LEDs, ensuring a smooth and continuous visual transition.

## License & Credits
- **Original Tutorial:** Paul McWhorter (TopTechBoy).
- **License:** This work is licensed under [CC BY-NC-SA 4.0](../../LICENSE) (Attribution-NonCommercial-ShareAlike).