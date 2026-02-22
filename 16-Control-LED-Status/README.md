# Lesson 016: Green, Yellow, and Red LEDs Serial Control

## Project Info
- **Project Name:** Green, Yellow, and Red LEDs Serial Control
- **Lesson:** [Arduino Uno R4 WiFi LESSON 16: Understanding If Statements and Conditionals](https://www.youtube.com/watch?v=H5OlCuUWEg8&list=PLGs0VKk2DiYyn0wN335MXpbi3PRJTMmex&index=19) by Paul McWhorter
- **Revision:** 1.2 (Final Version)
- **Date:** 2026-02-21
- **Author:** SuperMechatronicEngineer

## Project Description
This project demonstrates how to implement a reliable text-based interface by using the **Serial Monitor** to control three colored LEDs (Green, Yellow, and Red) on an Arduino UNO R4 WiFi.

The system utilizes a **string processing logic** to interpret user commands. By entering specific words like "green", "red", or "off", the microcontroller manages the state of the LEDs with mutual exclusion, ensuring only the selected LED is active. This setup highlights how to build a user-friendly digital interface that handles case-insensitivity and formatting errors while maintaining high responsiveness.

## 📺 Video Documentation
The complete build and demonstration are available on Odysee:
- **Watch here:** [Arduino UNO R4 WiFi - Control 3 LEDs Status via Serial Monitor](https://odysee.com/@SuperMechatronicEngineer:8/016-LEDs-Control-Serial:8)

## Technical Details
* **Target Hardware:** Arduino UNO R4 WiFi.
* **Active Components:** 
    * **Digital Pin 11**: Green LED.
    * **Digital Pin 10**: Yellow LED.
    * **Digital Pin 9**: Red LED.
    * **3x 1kΩ Resistor**: Used for the LED to ensure low current draw and component longevity.
* **Baud Rate:** 115200 bps (High-speed telemetry).

## Software Logic & Architecture
* **Data Normalization:** The architecture uses `input.trim()` and `input.toLowerCase()` to sanitize the serial buffer. This ensures that the system rejects hidden characters (like `\n` or `\r`) and remains "human-friendly," accepting commands regardless of capitalization (e.g., "RED", "Red", or "red").
* **Timeout Optimization:** To eliminate the default 1000ms delay found in standard Arduino functions like `Serial.readString()`, the project implements `Serial.setTimeout(10)`. This allows for near-instantaneous hardware updates, providing a lag-free experience even with "No Line Ending" serial settings.
* **Error Handling:** The system includes a feedback loop that monitors the input string. If the command does not match the predefined set, the Serial console returns a specific error message, guiding the user back to the valid command set.

## License & Credits
- **Original Tutorial:** Paul McWhorter (TopTechBoy).
- **License:** This project is licensed under [CC BY-NC-SA 4.0](../../LICENSE) (Attribution-NonCommercial-ShareAlike).