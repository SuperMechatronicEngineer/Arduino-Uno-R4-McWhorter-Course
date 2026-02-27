# Lesson 027: RGB LED Control using Push Buttons and Internal Pull-ups

## Project Info
- **Project Name:** RGB LED Control using Push Buttons and Internal Pull-ups
- **Lesson:** [Arduino Uno R4 WiFi LESSON 27: Using Internal Pullup Resistors on Arduino](https://www.youtube.com/watch?v=8YFQAQqkHaI&list=PLGs0VKk2DiYyn0wN335MXpbi3PRJTMmex&index=29) by Paul McWhorter
- **Revision:** 1.2 (Final Version)
- **Date:** 2026-02-27
- **Author:** SuperMechatronicEngineer

## Project Description
Building on the previous multi-channel architecture, the core objective of this project is to **optimize hardware efficiency and analyze signal integrity**. While the previous version relied on external resistors, this project utilizes the **Arduino UNO R4 WiFi’s internal pull-up resistors** to manage three independent RGB channels (Red, Green, and Blue) through a refined vectorized architecture.

This project serves as a comparative study between an unstable high-impedance state (floating inputs) and a stabilized internal pull-up configuration, demonstrating the effect of Electromagnetic Interference on digital inputs.

## 📺 Video Documentation
The complete build and demonstration are available on Odysee:
- **Watch here:** [Arduino UNO R4 WiFi - RGB LED Control: Floating Pins vs Internal Pull-ups](https://odysee.com/@SuperMechatronicEngineer:8/Arduino-UNO-R4-WiFi---RGB-LED-Control-using-Push-Buttons-and-internal-:d)

## Technical Details
* **Target Hardware:** Arduino UNO R4 WiFi.
* **Active Components:** 
    * **RGB LED (Common Cathode)**: Multi-color indicator connected to **Pins 11 (R), 10 (G), and 9 (B)**.
    * **3x Momentary Push Buttons**: Independent digital inputs connected to:
        * **Pin 4**: Red Channel Toggle
        * **Pin 3**: Green Channel Toggle
        * **Pin 2**: Blue Channel Toggle
    * **3x 1kΩ Resistors**: Current-limiting resistors to protect the RGB LED segments.
* **Wiring Strategy:** Optimized common-ground architecture with independent pull-up lines for precise active-low signal triggering.
* **Baud Rate:** 115200 bps (High-speed telemetry for real-time multi-channel monitoring).

## Software Logic & Architecture
* **Vectorized Signal Tracking:** The system monitors all inputs through a centralized `for` loop. By tying array dimensions to a `NUM_CHANNELS` constant within an `enum`, the code achieves total compile-time consistency and zero RAM overhead for indexing.
* **Independent Non-Blocking Debounce:** Each channel maintains its own temporal reference using `millis()`. This allows for simultaneous interactions across different buttons while effectively filtering mechanical noise on each specific line.
* **Transition Logic:** Specifically engineered to detect a **Falling Edge** (HIGH to LOW transition) on the stabilized signal. A toggle command is executed only when a transition from 5V to 0V is confirmed.
* **Input Configuration:** Utilizes `pinMode(pin, INPUT_PULLUP)` to activate the microcontroller's internal pull-up resistors, ensuring a stable `HIGH` state when buttons are released and eliminating the need for external components.

## License & Credits
- **Original Tutorial:** Paul McWhorter (TopTechBoy).
- **License:** This project is licensed under [CC BY-NC-SA 4.0](../../LICENSE) (Attribution-NonCommercial-ShareAlike).