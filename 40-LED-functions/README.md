# Lesson 040: Smart Dimmer: Exponential LED Control

## Project Info
- **Project Name:** Smart Dimmer: Exponential LED Control
- **Lesson:** [Arduino Uno R4 WiFi LESSON 40: Using Arduino Functions with Local Variables Explained](https://www.youtube.com/watch?v=SeAT_sELVdw&list=PLGs0VKk2DiYyn0wN335MXpbi3PRJTMmex&index=41) by Paul McWhorter
- **Revision:** 1.2 (Final Version)
- **Date:** 2026-03-09
- **Author:** SuperMechatronicEngineer

## Project Description
This project demonstrates a structured approach to LED dimming using the **Arduino UNO R4**. Instead of a simple "always-on" loop, the system implements an **Input-Process-Output (IPO) model** designed for stability and smooth visual transitions.

Standard Arduino sketches often suffer from "flicker" or "serial flooding" due to electrical noise. This project solves that by implementing a **Software Noise Gate (Hysteresis)**. The system monitors the potentiometer but only triggers a recalculation and serial update when the physical change exceeds a defined threshold, ensuring a rock-solid output.

Because human vision is non-linear, standard linear dimming feels "jumpy" at low levels. This project uses a **Base-2 Exponential Function** to map the input, providing a much more natural dimming experience.

## 📺 Video Documentation
The complete build and demonstration are available on Odysee:
- **Watch here:** [Arduino UNO R4 WiFi - Smart Dimmer: Exponential LED Control](https://odysee.com/@SuperMechatronicEngineer:8/040-LED-Functions:e)

## Technical Details
* **Hardware:** Arduino UNO R4 WiFi, 1x Red LED (Pin 10), 1x 1kΩ Resistor, 1x 10kΩ Potentiometer (Pin A0).
* **Power Management:** The breadboard is powered directly via the **5V rail** from the Arduino, ensuring a stable reference voltage for the analog-to-digital conversion.
* **Transfer Functions:** Exponential: Implemented using the formula $PWM = [2^{(rawValue / (1023/8))}] - 1$.
* **Modular Design:** Divided into three distinct functions (**Input, Process, Output**) to demonstrate professional coding standards and reusability.
* **Signal Conditioning:** Includes a **"Zero-Floor" logic** to ensure the LED fully extinguishes at the bottom of the potentiometer's range, compensating for common ADC/potentiometer offsets.
* **Event-Driven Telemetry:** Serial data (**115200 baud**) is only sent when the input changes, keeping the monitor clean and readable.

## Software Logic & Architecture
* **Modular IPO Model:** The code is refactored into independent functional blocks:
    1. **Input Function:** Manages ADC acquisition with double-sampling for stability and implements the hysteresis threshold.
    2. **Process Function:** A pure mathematical layer that handles the exponential mapping and voltage calculation.
    3. **Output Function:** Finalizes the hardware actuation and logs data to the Serial port.
* **Exponential Mapping (Pin 10):** Uses the optimized `exp2f()` function to create a natural brightness progression that compensates for the logarithmic nature of human vision.
* **Hysteresis Logic:** By comparing the current reading with the `lastStableX` using a threshold of **3 units**, the system filters out electrical noise and prevents unnecessary CPU and Serial overhead.

## License & Credits
- **Original Tutorial:** Paul McWhorter (TopTechBoy).
- **License:** This project is licensed under [CC BY-NC-SA 4.0](../../LICENSE) (Attribution-NonCommercial-ShareAlike).