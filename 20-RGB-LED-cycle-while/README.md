# Lesson 020: Control an RGB LED Lighting Cycle via Serial Control using a WHILE LOOP

## Project Info
- **Project Name:** RGB LED Lighting Cycle using a WHILE LOOP
- **Lesson:** [Arduino Uno R4 WiFi LESSON 20: For Loops in Arduino](https://www.youtube.com/watch?v=CZh8QB26jjU&list=PLGs0VKk2DiYyn0wN335MXpbi3PRJTMmex&index=22) by Paul McWhorter
- **Revision:** 1.2 (Final Version)
- **Date:** 2026-02-23
- **Author:** SuperMechatronicEngineer

## Project Description
This project implements a numeric-based interface using the **Serial Monitor** to control an RGB LED on an Arduino UNO R4 WiFi. The core objective is to allow the user to specify a precise number of lighting cycles (Red -> Green -> Blue) through text-based numeric commands.

The program operates in a standby mode until an input is received. Once a value is provided, the system validates the data to ensure it is a valid integer within the safety range of **0 to 100**. This version specifically focuses on manual iteration control using a **while loop** structure.

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
* **Dynamic Cycle Execution (While Loop):** Unlike a standard for-loop, this firmware utilizes a **while loop** with a manually managed counter. The program executes the sequence (R -> G -> B -> Off) and increments the counter only after each full cycle completion.

## License & Credits
- **Original Tutorial:** Paul McWhorter (TopTechBoy).
- **License:** This project is licensed under [CC BY-NC-SA 4.0](../../LICENSE) (Attribution-NonCommercial-ShareAlike).