# Lesson 035: Dynamic Grades Acquisition System

## Project Info
- **Project Name:** Dynamic Grades Acquisition System
- **Lesson:** [Arduino Uno R4 WiFi LESSON 35: Understanding and Using Arrays in Projects](https://www.youtube.com/watch?v=HWkQHzCNdx8&list=PLGs0VKk2DiYyn0wN335MXpbi3PRJTMmex&index=38) by Paul McWhorter
- **Revision:** 1.2 (Final Version)
- **Date:** 2026-03-08
- **Author:** SuperMechatronicEngineer

## Project Description
This project implements a robust statistical analysis system for student grades. Built for the **Arduino UNO R4 WiFi**, it allows the user to dynamically allocate memory for a specific number of students and calculate the **Average, Maximum, and Minimum** scores.

The core focus of this revision is **Input Sanitization** and **Memory Safety**, ensuring the firmware remains stable even when faced with invalid user entries or memory constraints.

## Technical Details
* **Target Hardware:** Arduino UNO R4 WiFi.
* **Memory Management:** Dynamic Heap Allocation using `new (std::nothrow)` and `delete[]`.
* **Baud Rate:** 115200 bps (High-speed telemetry).

## Software Logic & Architecture
* **Strict Input Sanitization:** The system features a custom `isValidNumericInput()` validator. Unlike standard `parseFloat()`, this "firewall" scans the entire Serial buffer character-by-character to block:
    * **Scientific Notation:** Inputs like `3e3` are rejected.
    * **Alphanumeric Noise:** Letters or symbols (e.g., `10abc`, `-5`) are identified before parsing.
* **Dual-Mode Validation:** The validator uses a boolean toggle (`allowFloat`) to enforce **Strict Integer Integrity** for the student count (no decimals allowed) while permitting **Floating Point Precision** for the actual grades.
* **Memory Safety (No-Throw):** Uses the `(std::nothrow)` handler during allocation. If the Heap is full, the program recovers gracefully with a "Fatal Error" message instead of crashing the MCU.

## License & Credits
- **Original Tutorial:** Paul McWhorter (TopTechBoy).
- **License:** This project is licensed under [CC BY-NC-SA 4.0](../../LICENSE) (Attribution-NonCommercial-ShareAlike).