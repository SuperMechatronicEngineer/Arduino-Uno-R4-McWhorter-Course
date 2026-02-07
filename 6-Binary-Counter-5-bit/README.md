# Lesson 006 Homework: 5-Bit Binary Counter

## Project Info
- **Project Name:** 5-Bit Binary Counter
- **Lesson:** [Arduino Uno R4 WiFi LESSON 6: Create a Binary Counter With Arduino](https://www.youtube.com/watch?v=KEtut8pzXZA&list=PLGs0VKk2DiYyn0wN335MXpbi3PRJTMmex&index=8) by Paul McWhorter
- **Revision:** 1.0 (Initial Release)
- **Date:** 2026-02-07
- **Author:** SuperMechatronicEngineer

## Project Description
This project implements a **5-bit binary counter** using an array of 5 LEDs. The system visualizes how decimal integers (0-31) are represented in binary form within a computer's memory. By expanding the hardware to a 5-LED array, the project demonstrates the scalability of bitwise logic, mapping the internal state of an integer directly to the physical output without changing the core software architecture.

## 📺 Video Documentation
The complete build and demonstration are available on Odysee:
- **Watch here:** [Arduino UNO R4 WiFi - 5-bit Binary Counter](https://odysee.com/@SuperMechatronicEngineer:8/Arduino-UNO-R4-5-bit-Binary-Counter:0)

## Technical Details
* **Target Hardware:** Arduino UNO R4 WiFi
* **Active Components:** 
    * **5x Red LEDs** (External).
    * **5x 1000Ω Resistors**: High-value resistors chosen for safety and low current draw (approx. 3.2mA per pin).
* **Connections:** Digital Pins 2, 3, 4, 5, 6 and GND.

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