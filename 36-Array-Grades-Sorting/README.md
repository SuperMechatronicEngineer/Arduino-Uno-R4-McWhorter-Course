# Lesson 036: Advanced Grade Analytics & Sorting System

## Project Info
- **Project Name:** Advanced Grade Analytics & Sorting System
- **Lesson:** [Arduino Uno R4 WiFi LESSON 36: Finding Average of an Array of Numbers on Arduino](https://www.youtube.com/watch?v=5_qZwNqDg-Y&list=PLGs0VKk2DiYyn0wN335MXpbi3PRJTMmex&index=40) by Paul McWhorter
- **Revision:** 1.2 (Final Version)
- **Date:** 2026-03-08
- **Author:** SuperMechatronicEngineer

## Project Description
This project implements a robust statistical analysis and data organization system for student grades. Built for the **Arduino UNO R4 WiFi**, it allows the user to dynamically allocate memory for a specific number of students, calculate the **Average**, and automatically rank grades from **Highest to Lowest**.

The core focus of this revision is **Data Integrity** and **Algorithmic Efficiency**, ensuring the firmware remains stable while providing a professional, sorted output of the processed information.

## Technical Details
* **Target Hardware:** Arduino UNO R4 WiFi.
* **Memory Management:** Dynamic Heap Allocation using `new (std::nothrow)` and `delete[]`.
* **Baud Rate:** 115200 bps (High-speed telemetry).

## Software Logic & Architecture

### 1. Strict Input Sanitization
The system features a custom `isValidNumericInput()` validator. Unlike the standard `parseFloat()`, this "firewall" scans the entire Serial buffer character-by-character to ensure data integrity.

**The validator strictly blocks:**
* **Scientific Notation:** Inputs like `3e3` are rejected to prevent logic errors in grade processing.
* **Alphanumeric Noise:** Letters or symbols (e.g., `10abc`, `!#$`) are identified and discarded.
* **Out-of-Context Characters:** If `allowFloat` is false, it also blocks the decimal point (`.`).

**Dual-Mode Logic:**
The function uses a boolean toggle (`allowFloat`) to adapt its behavior. This allows the system to enforce **Strict Integer Integrity** for the student count (where 2.5 students would be impossible) while permitting **Floating Point Precision** for the actual grades.

### 2. Optimized Sorting Engine (Bubble Sort)
To enhance the statistical report, the firmware implements an **Optimized Bubble Sort** algorithm:
* **Descending Order:** Grades are automatically rearranged from the highest to the lowest.
* **Early-Exit Optimization:** The algorithm uses a `swapped` flag to detect if the array is already sorted, preventing unnecessary CPU cycles.

### 3. Memory Safety (No-Throw)
The system uses the `(std::nothrow)` handler during heap allocation. If the SRAM is full or the requested student count exceeds limits, the program recovers gracefully with a "Fatal Error" message instead of crashing the MCU.

## License & Credits
- **Original Tutorial:** Paul McWhorter (TopTechBoy).
- **License:** This project is licensed under [CC BY-NC-SA 4.0](../../LICENSE) (Attribution-NonCommercial-ShareAlike).