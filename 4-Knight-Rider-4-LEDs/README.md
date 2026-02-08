# Lesson 004 Homework: Bidirectional LED Sequencer (Knight Rider)

## Project Info
- **Project Name:** Knight Rider LED Effect
- **Lesson:** [Arduino Uno R4 Wifi LESSON 4: Building Clean and Neat Circuits on a Breadboard](https://www.youtube.com/watch?v=JUptf53Ni0A&list=PLGs0VKk2DiYyn0wN335MXpbi3PRJTMmex&index=5) by Paul McWhorter
- **Revision:** 1.0 (Initial Release)
- **Date:** 2026-02-06
- **Author:** SuperMechatronicEngineer

## Project Description
This project implements a bidirectional LED sequencer, commonly known as the **"Knight Rider"** or "Supercar" effect. This project is a further development of my Lesson 3 homework from Paul McWhorter's 'Arduino Uno R4 WiFi' series. Based on the foundation of the 4-LED simultaneous blink exercise, I expanded the logic to implement a sequential, back-and-forth scanning effect. This demonstrates a more advanced application of **array indexing** to handle individual LED timing.

## 📺 Video Documentation
The complete build and demonstration are available on Odysee:
- **Watch here:** [Arduino UNO R4 WiFi - Knight Rider](https://odysee.com/@SuperMechatronicEngineer:8/Arduino-UNO-R4-Knight-Rider:9)

## Technical Details
* **Target Hardware:** Arduino UNO R4 WiFi
* **Active Components:** 
    * **4x Red LEDs** (External).
    * **4x 1000Ω Resistors**: High-value resistors chosen for safety and low current draw (approx. 3.2mA per pin).
* **Connections:** Digital Pins 2, 3, 4, 5 and GND.

## Logic & Software Architecture
The software is designed for scalability and memory integrity:
* **Array-based Addressing:** Pins are stored in a `ledPins[]` array, allowing the system to scale without modifying the core logic.
* **Memory Safety:** The `for` loops utilize strict exit conditions (`i < numLeds`) to prevent out-of-bounds indexing errors.
* **Sequence Optimization:** The return sequence is calibrated (`numLeds - 2` down to `1`) to prevent "double-blinking" at the boundary LEDs, ensuring a smooth and continuous visual transition.

## License & Credits
- **Original Tutorial:** Paul McWhorter (TopTechBoy).
- **License:** This work is licensed under [CC BY-NC-SA 4.0](../../LICENSE) (Attribution-NonCommercial-ShareAlike).