# Lesson 024: LED Toggling using a Push Button

## Project Info
- **Project Name:** LED Toggling using a Push Button
- **Lesson:** [Arduino Uno R4 WiFi LESSON 24: Make a Button Switch With a Pullup Resistor](https://www.youtube.com/watch?v=Rg9WvA8ovik&list=PLGs0VKk2DiYyn0wN335MXpbi3PRJTMmex&index=26) by Paul McWhorter
- **Revision:** 1.2 (Final Version)
- **Date:** 2026-02-25
- **Author:** SuperMechatronicEngineer

## Project Description
The core objective of this project is to implement a stable **"toggle" interface** using a momentary push button and an Arduino UNO R4 WiFi. The system transforms a transient physical pulse into a persistent binary state (ON/OFF) to control a status LED.

Unlike basic implementations, this project utilizes a **non-blocking debouncing algorithm** and is optimized with **`byte` data types**, ensuring the microcontroller remains responsive for other concurrent tasks while maintaining a minimal memory footprint.

## 📺 Video Documentation
The complete build and demonstration are available on Odysee:
- **Watch here:** [Arduino UNO R4 WiFi - LED Toggling using a Push Button](https://odysee.com/@SuperMechatronicEngineer:8/024-LED-Toggle:a)

## Technical Details
* **Target Hardware:** Arduino UNO R4 WiFi.
* **Active Components:** 
    * **Momentary Push Button**: Digital input interface connected to **Digital Pin 2**.
    * **10kΩ Resistor**: Used as an **External Pull-up** resistor for the push button to ensure signal stability.
    * **Red LED**: Status indicator connected to **Digital Pin 10**.
    * **1kΩ Resistor**: Current-limiting resistor to protect the LED and the microcontroller's GPIO.
* **Wiring Strategy:** Common Ground architecture to ensure signal integrity and precise voltage reference for the active-low trigger.
* **Baud Rate:** 115200 bps (High-speed telemetry for real-time toggle monitoring).

## Software Logic & Architecture
* **Asynchronous Debouncing:** Implements a non-blocking 50ms temporal window via `millis()` to filter mechanical chatter without halting the CPU, ensuring system scalability.
* **Edge Detection Logic:** Specifically engineered to trigger on the **Falling Edge** (HIGH to LOW transition), providing an instantaneous response to the physical button press.
* **State-Change Telemetry:** Employs a conditional logic structure to filter redundant data, updating the Serial Monitor only when a valid toggle event is confirmed.
* **Optimized Types:** Uses `byte` (uint8_t) for all state-tracking and pin variables, reducing RAM footprint and aligning with the native 8-bit register depth for digital I/O.

## License & Credits
- **Original Tutorial:** Paul McWhorter (TopTechBoy).
- **License:** This project is licensed under [CC BY-NC-SA 4.0](../../LICENSE) (Attribution-NonCommercial-ShareAlike).