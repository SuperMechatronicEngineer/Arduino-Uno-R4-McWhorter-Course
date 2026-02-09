# Lesson 010: LED Breathing Effect

## Project Info
- **Project Name:** LED Breathing Effect
- **Lesson:** [Arduino Uno R4 WiFi LESSON 10: Writing Analog Voltages With the Arduino](https://www.youtube.com/watch?v=lTzOvBYNo3U&list=PLGs0VKk2DiYyn0wN335MXpbi3PRJTMmex&index=11) by Paul McWhorter
- **Revision:** 1.1 (Improved Version)
- **Date:** 2026-02-09
- **Author:** SuperMechatronicEngineer

## Project Description
This project implements a **"breathing" light effect** by modulating PWM (Pulse Width Modulation) signals on an Arduino UNO R4 WiFi. The system creates a continuous cycle of gradual brightness transitions, while providing real-time data feedback through the Serial Port.

## 📺 Video Documentation
The complete build and demonstration are available on Odysee:
- **Watch here:** [Arduino UNO R4 WiFi - LED Breathing Effect](https://odysee.com/@SuperMechatronicEngineer:8/Arduino-UNO-R4-PWM-LED-Fade:e)

## Technical Details
* **Target Hardware:** Arduino UNO R4 WiFi
* **Active Components:** 
    * **Red LED**.
    * **1kΩ Resistor**: Selected to maintain current at approximately **3.2mA**, ensuring long-term stability for the Renesas RA4M1 microcontroller.
* **Baud Rate:** 115200 bps.
* **Connections:** Digital Pin 11 and GND.

## Software Logic & Architecture
The code is designed to be lean and synchronized, managing the full fade cycle:
* **Bi-directional Fade:** The logic handles both **Fade-In** (increasing brightness) and **Fade-Out** (decreasing brightness) using a single mathematical sign inversion: `fadeAmount = -fadeAmount`.
* **Synchronized Monitoring:** Serial output is executed immediately before `analogWrite`, ensuring the monitored value perfectly matches the hardware state.
* **System Ready Gate:** Implementation of `while (!Serial)` and `BOOT_DELAY` for stable initialization.

## License & Credits
- **Original Tutorial:** Paul McWhorter (TopTechBoy).
- **License:** This project is licensed under [CC BY-NC-SA 4.0](../../LICENSE) (Attribution-NonCommercial-ShareAlike).