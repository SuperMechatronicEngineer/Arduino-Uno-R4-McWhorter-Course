# Lesson 025: RGB LED Control using Push Buttons

## Project Info
- **Project Name:** LED Toggling using a Push Button
- **Lesson:** [Arduino Uno R4 WiFi LESSON 25: Make a Toggle Switch with Button Switch](https://www.youtube.com/watch?v=Is8YhpQVVX8&list=PLGs0VKk2DiYyn0wN335MXpbi3PRJTMmex&index=26) by Paul McWhorter
- **Revision:** 1.2 (Final Version)
- **Date:** 2026-02-25
- **Author:** SuperMechatronicEngineer

## Project Description
The core objective of this project is to evolve the previous toggle logic into a **scalable, multi-channel signal processing interface**. Using an Arduino UNO R4 WiFi, the system independently manages three distinct channels (Red, Green, and Blue) using a **vectorized data architecture**.

Instead of duplicating logic for each input, this project utilizes an optimized structure where all hardware mappings and signal states are stored in arrays. This ensures the firmware remains lightweight, easy to maintain, and ready for expansion without increasing execution overhead.

## 📺 Video Documentation
The complete build and demonstration are available on Odysee:
- **Watch here:** [Arduino UNO R4 WiFi - RGB LED Control using Push Buttons](https://odysee.com/@SuperMechatronicEngineer:8/025-RGB-LED-Control:9)

## Technical Details
* **Target Hardware:** Arduino UNO R4 WiFi.
* **Active Components:** 
    * **RGB LED (Common Cathode)**: Multi-color indicator connected to **Pins 11 (R), 10 (G), and 9 (B)**.
    * **3x Momentary Push Buttons**: Independent digital inputs connected to:
        * **Pin 4**: Red Channel Toggle
        * **Pin 3**: Green Channel Toggle
        * **Pin 2**: Blue Channel Toggle
    * **3x 10kΩ Resistors**: Configured as **External Pull-up** resistors to ensure signal stability.
    * **3x 1kΩ Resistors**: Current-limiting resistors to protect the RGB LED segments.
* **Wiring Strategy:** Optimized common-ground architecture with independent pull-up lines for precise active-low signal triggering.
* **Baud Rate:** 115200 bps (High-speed telemetry for real-time multi-channel monitoring).

## Software Logic & Architecture
* **Vectorized Signal Tracking:** The system monitors all inputs through a centralized `for` loop. By tying array dimensions to a `NUM_CHANNELS` constant within an `enum`, the code achieves total compile-time consistency and zero RAM overhead for indexing.
* **Independent Non-Blocking Debounce:** Each channel maintains its own temporal reference using `millis()`. This allows for simultaneous interactions across different buttons while effectively filtering mechanical noise on each specific line.
* **Transition Logic:** Specifically engineered to detect a **Falling Edge** (HIGH to LOW transition) on the stabilized signal. A toggle command is executed only when a transition from 5V to 0V is confirmed.

## License & Credits
- **Original Tutorial:** Paul McWhorter (TopTechBoy).
- **License:** This project is licensed under [CC BY-NC-SA 4.0](../../LICENSE) (Attribution-NonCommercial-ShareAlike).