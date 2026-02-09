# Lesson 009: Serial Monitor LED Status

## Project Info
- **Project Name:** Serial Monitor LED Status
- **Lesson:** [Arduino Uno R4 WiFi LESSON 9: Using the Serial Port to Print to the Serial Monitor](https://www.youtube.com/watch?v=4N-Q28lTzqE&list=PLGs0VKk2DiYyn0wN335MXpbi3PRJTMmex&index=11) by Paul McWhorter
- **Revision:** 1.1 (Improved Version)
- **Date:** 2026-02-09
- **Author:** SuperMechatronicEngineer

## Project Description
This project implements a real-time status monitoring system using the **Serial Port** of the Arduino UNO R4 WiFi. The objective is to establish a reliable communication link between the microcontroller and the **Serial Monitor** in Arduino IDE 2.x, allowing the system to report hardware transitions (LED ON/OFF) as they occur.

## 📺 Video Documentation
The complete build and demonstration are available on Odysee:
- **Watch here:** [Arduino UNO R4 WiFi - Serial Monitor LED Status](https://odysee.com/@SuperMechatronicEngineer:8/Arduino-UNO-R4-Serial-Monitor-LED:7)

## Technical Details
* **Target Hardware:** Arduino UNO R4 WiFi
* **Active Components:** 
    * **Red LED**.
    * **1kΩ Resistor**: Selected to maintain current at approximately **3.2mA**, ensuring long-term stability for the Renesas RA4M1 microcontroller.
* **Baud Rate:** 9600 bps.
* **Connections:** Digital Pin 2 and GND.

## Software Logic & Architecture
The code is optimized for memory efficiency and communication reliability:
* **Memory Management:** Use of `const char*` pointers for fixed strings, minimizing RAM fragmentation compared to the standard `String` class.
* **Sync Logic:** Implementation of a `while (!Serial)` loop to ensure the program waits for the user to open the Serial Monitor before transmitting data.
* **User Experience:** A 3-second `BOOT_DELAY` is integrated to provide a visual window for the user to focus on the console before the monitoring starts.

## License & Credits
- **Original Tutorial:** Paul McWhorter (TopTechBoy).
- **License:** This project is licensed under [CC BY-NC-SA 4.0](../../LICENSE) (Attribution-NonCommercial-ShareAlike).