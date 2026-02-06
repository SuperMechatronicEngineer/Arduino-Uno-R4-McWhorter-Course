# Lesson 005 Homework: 4-Bit Binary Counter

## Project Info
- **Project Name:** 4-Bit Binary Counter
- **Lesson:** [Arduino Uno R4 WiFi LESSON 5: Explaining How Computers Work Based On Binary Numbers](https://www.youtube.com/watch?v=cSOpMpynXAI&list=PLGs0VKk2DiYyn0wN335MXpbi3PRJTMmex&index=6) by Paul McWhorter
- **Revision:** 1.0 (Initial Release)
- **Date:** 2026-02-06
- **Author:** SuperMechatronicEngineer

## Project Description
This project implements a **4-bit binary counter** using an array of 4 LEDs. The system visualizes how decimal integers (0-15) are represented in binary form within a computer's memory. By using bitwise manipulation, the code translates the state of each individual bit directly to a corresponding physical LED.

## 📺 Video Documentation
The complete build and demonstration are available on Odysee:
- **Watch here:** [Arduino UNO R4 WiFi - Binary Counter](https://odysee.com/@SuperMechatronicEngineer:8/Arduino-UNO-R4-Binary-Counter:e)

## Technical Details
* **Target Hardware:** Arduino UNO R4 WiFi
* **Active Components:** * **4x Red LEDs** (External).
    * **4x 1000Ω Resistors**: High-value resistors chosen for safety and low current draw (approx. 3.2mA per pin).
* **Connections:** Digital Pins 2, 3, 4, 5 and GND.

## Logic & Software Architecture
The software is designed for scalability and memory integrity:
* **Array-based Addressing:** Pins are stored in a `ledPins[]` array, allowing the system to scale without modifying the core logic.
* **Memory Safety:** The `for` loops utilize strict exit conditions (`i < numLeds`) to prevent out-of-bounds indexing errors.
* **C++ bitwise operators** to ensure the code remains efficient, readable, and easily scalable:
    * **Dynamic Range:** The counter limit is determined by the expression `(1 << numLeds)`. This ensures that if the number of LEDs in the array changes, the counter automatically adjusts its maximum value ($2^n$).
    * **Bitwise Extraction:** Instead of using complex mathematical operations, the `displayBinary()` function isolates each bit using **Right Shift** (`>>`) and a **Bitwise AND** mask (`& 1`)

## License & Credits
- **Original Tutorial:** Paul McWhorter (TopTechBoy).
- **License:** This work is licensed under [CC BY-NC-SA 4.0](../../LICENSE) (Attribution-NonCommercial-ShareAlike).