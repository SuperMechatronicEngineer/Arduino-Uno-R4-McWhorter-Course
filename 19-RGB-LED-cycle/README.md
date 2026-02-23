# Lesson 019: Control an RGB LED lightning Cycle via Serial Control

## Project Info
- **Project Name:** Control an RGB LED lightning Cycle via Serial Control
- **Lesson:** [Arduino Uno R4 WiFi LESSON 19: Mixing Colors with an RGB LED](https://www.youtube.com/watch?v=YniHyGypG9w&list=PLGs0VKk2DiYyn0wN335MXpbi3PRJTMmex&index=21) by Paul McWhorter
- **Revision:** 1.2 (Final Version)
- **Date:** 2026-02-23
- **Author:** SuperMechatronicEngineer

## Project Description
This project implements a numeric-based interface using the **Serial Monitor** to control an RGB LED on an Arduino UNO R4 WiFi. The core objective is to allow the user to specify a precise number of lighting cycles (Red -> Green -> Blue) through text-based numeric commands.

The program operates in a standby mode until an input is received. Once a value is provided, the system validates the data to ensure it is a valid integer within the safety range of **0 to 100**.

## 📺 Video Documentation
The complete build and demonstration are available on Odysee:
- **Watch here:** [Arduino UNO R4 WiFi - Control an RGB LED lighting Cycle via Serial Monitor](https://odysee.com/@SuperMechatronicEngineer:8/019-RGB-LED-Cycle:6)

## Technical Details
* **Target Hardware:** Arduino UNO R4 WiFi.
* **Active Components:** 
    * **Common Cathode RGB LED**: The shared negative terminal (GND) is connected directly to the breadboard's ground rail.
    * **Digital Pin 11**: Red Anode.
    * **Digital Pin 10**: Green Anode.
    * **Digital Pin 9**: Blue Anode.
    * **3x 1kΩ Resistor**: Placed on each anode (R, G, B) to ensure low current draw and component longevity.
* **Baud Rate:** 115200 bps (High-speed telemetry).

## Software Logic & Architecture
* **Robust Input Validation:** The system features a "fail-safe" logic that checks the input character-by-character using `isDigit()`. It distinguishes between valid integers, out-of-range values, and non-numeric strings, preventing undefined behavior.
* **Responsive Command Interface:** To maximize responsiveness, the architecture uses `while (Serial.available() == 0)` to wait for input. Combined with `Serial.setTimeout(10)`, this eliminates the default serial lag, triggering the lighting sequence instantly upon pressing Enter.
* **Dynamic Cycle Execution:** The firmware translates the user's numeric input into a controlled `for` loop. Each cycle follows a strict sequence (R -> G -> B -> Off) with precisely timed delays, providing clear visual feedback of the system's status.
* **Hardware Safety & Mutual Exclusion:** Through a dedicated `allLedsOff()` function, the code enforces a "Clear-before-Write" policy. This ensures **mutual exclusion** between the RGB channels, protecting the hardware from current spikes and ensuring absolute color purity during each stage of the cycle.

## License & Credits
- **Original Tutorial:** Paul McWhorter (TopTechBoy).
- **License:** This project is licensed under [CC BY-NC-SA 4.0](../../LICENSE) (Attribution-NonCommercial-ShareAlike).