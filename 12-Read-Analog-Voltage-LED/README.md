# Lesson 012: Potentiometer LED Control

## Project Info
- **Project Name:** Potentiometer LED Control
- **Lesson:** [Arduino Uno R4 WiFi LESSON 12: Read Analog Voltages on the Arduino](https://www.youtube.com/watch?v=Vp5u_8KAzFw&list=PLGs0VKk2DiYyn0wN335MXpbi3PRJTMmex&index=13) by Paul McWhorter
- **Revision:** 1.2 (Final Version)
- **Date:** 2026-02-11
- **Author:** SuperMechatronicEngineer

## Project Description
This project demonstrates manual LED intensity control by interfacing a **10kΩ potentiometer** with an Arduino UNO R4 WiFi. The core objective is to implement a **linear relationship** between the physical rotation of the trimmer and the LED's brightness, mapping 10-bit analog input (ADC) directly to 8-bit pulse width modulation (PWM) output.

## 📺 Video Documentation
The complete build and demonstration are available on Odysee:
- **Watch here:** [Arduino UNO R4 WiFi - Manual LED Control: Linear Transfer Function](https://odysee.com/@SuperMechatronicEngineer:8/Arduino-UNO-R4-Pot-LED-Control:9)

## Technical Details
* **Target Hardware:** Arduino UNO R4 WiFi.
* **Active Components:** 
    * **Red LED**.
    * **1kΩ Resistor**: Used for the LED to ensure low current draw and component longevity.
    * **10kΩ Potentiometer**: Used as a voltage divider to provide the analog input.
* **Power Supply:** The breadboard is powered via the **5V pin** from the Arduino board.
* **Baud Rate:** 115200 bps (High-speed telemetry).
* **Connections:** Analog Pin A0 (Potentiometer), Digital Pin 11 (LED), and GND.

## Software Logic & Architecture
The code focuses on precision and mathematical transparency:
* **Linear Transfer Function:** Instead of using the standard `map()` function, the project implements a direct scaling formula: $PWM = \text{rawValue} \cdot (255.0 / 1023.0)$. This allows for a clear understanding of the **Scale Factor** between different resolutions.
* **Real-Time Telemetry:** The system monitors three synchronized variables: the raw 10-bit input value, the real-world A0 voltage (0-5V), and the resulting 8-bit PWM command.

## License & Credits
- **Original Tutorial:** Paul McWhorter (TopTechBoy).
- **License:** This project is licensed under [CC BY-NC-SA 4.0](../../LICENSE) (Attribution-NonCommercial-ShareAlike).