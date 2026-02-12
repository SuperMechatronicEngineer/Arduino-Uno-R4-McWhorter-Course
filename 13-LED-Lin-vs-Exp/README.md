# Lesson 013: Potentiometer LED Control (Linear vs Exponential)

## Project Info
- **Project Name:** Manual LED Control: Linear vs Exponential Transfer Function
- **Lesson:** [Arduino Uno R4 WiFi LESSON 13: Dimmable LED Controlled by a Potentiometer](https://www.youtube.com/watch?v=PXf51k0alGU&list=PLGs0VKk2DiYyn0wN335MXpbi3PRJTMmex&index=15) by Paul McWhorter
- **Revision:** 1.2 (Final Version)
- **Date:** 2026-02-12
- **Author:** SuperMechatronicEngineer

## Project Description
This project explores the relationship between mathematical functions and human visual perception by interfacing a **10kΩ potentiometer** with an Arduino UNO R4 WiFi. The system controls two LEDs simultaneously to compare a **linear relationship** against a **base-2 exponential function**, demonstrating how different transfer functions affect the perceived smoothness of light dimming.

## 📺 Video Documentation
The complete build and demonstration are available on Odysee:
- **Watch here:** [Arduino UNO R4 WiFi - Manual LED Control: Linear vs Exponential Transfer Function](https://odysee.com/@SuperMechatronicEngineer:8/Arduino-UNO-R4-Pot-LED-Lin-vs-Exp:1)

## Technical Details
* **Target Hardware:** Arduino UNO R4 WiFi.
* **Active Components:** 
    * **2x Red LEDs**.
    * **2x 1kΩ Resistor**: Used for the LED to ensure low current draw and component longevity.
    * **10kΩ Potentiometer**: Used as a voltage divider to provide the analog input.
* **Power Supply:** The breadboard is powered via the **5V pin** from the Arduino board.
* **Baud Rate:** 115200 bps (High-speed telemetry).
* **Connections:** Analog Pin A0 (Input), Digital Pin 11 (Linear Output), Digital Pin 10 (Exponential Output).

## Software Logic & Architecture
The code focuses on precision, mathematical transparency, and telemetry optimization:
* **Linear Transfer Function (Pin 11):** Implements a direct scaling formula $PWM = \text{rawValue} \cdot (255.0 / 1023.0)$, highlighting the constant scale factor between resolutions.
* **Exponential Mapping (Pin 10):** Uses the formula $y = 2^{(x / 127.875)} - 1$ to create a natural brightness progression that compensates for the logarithmic nature of human vision.
* **Timed Telemetry (Decoupled):** Data transmission is managed via a non-blocking timer (`millis()`) set to **200ms**. This ensures the Serial Monitor remains readable and independent of the input sampling rate, providing a professional monitoring interface for raw ADC, voltage, and dual PWM values.

## License & Credits
- **Original Tutorial:** Paul McWhorter (TopTechBoy).
- **License:** This project is licensed under [CC BY-NC-SA 4.0](../../LICENSE) (Attribution-NonCommercial-ShareAlike).