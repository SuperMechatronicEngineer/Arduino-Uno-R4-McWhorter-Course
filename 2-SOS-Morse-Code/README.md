# Lesson 002 Homework: LED SOS Morse Code Signal

## Project Info
- **Project Name:** SOS Distress Signal
- **Lesson:** [Arduino Uno R4 Lesson 2](https://www.youtube.com/watch?v=S1NJJRpWHpA) by Paul McWhorter
- **Revision:** 1.0 (Initial Release)
- **Date:** 2026-01-28
- **Author:** SuperMechatronicEngineer

## Project Description
This project implements the international distress signal **SOS** (`... --- ...`) using an external LED connected to the **Arduino UNO R4**. The goal is to demonstrate modular programming through functions and to apply standard Morse code timing ratios.

## 📺 Video Documentation
The complete build and demonstration are available on Odysee:
- **Watch here:** [Arduino UNO R4 SOS](https://odysee/@SuperMechatronicEngineer:8/Arduino-UNO-R4-SOS:5?r=BPrXVvEkYtt5G2X6G8NsWVkY2qgQxn1P)

## Technical Details
* **Target Hardware:** Arduino UNO R4 WiFi
* **Active Component:** * **Red LED** (External).
    * **1kΩ Resistor**: A conservative choice to ensure the current remains well below the **8mA** digital pin limit, providing a safety margin for the Renesas RA4M1 microcontroller.
* **Connection:** Digital Pin 2 (Anode) and GND (Cathode).

## Electrical Calculations
To verify the safety of the circuit, we apply Ohm's Law:
$I = \frac{V_{source} - V_{led}}{R}$

* $V_{source} = 5V$
* $V_{led} \approx 1.8V$ (Typical for Red LEDs)
* $R = 1000\Omega$

**Result:** $I = \frac{5V - 1.8V}{1000\Omega} = 3.2mA$
The resulting current of **3.2mA** is safely below the **8mA** threshold per pin.

## Timing Logic
The signal is based on a "dot" duration of **100ms**. All other intervals are calculated as multiples of this base unit:
* **Dash**: $3 \times \text{dot}$
* **Letter Pause**: $3 \times \text{dot}$
* **Word Pause**: $7 \times \text{dot}$

## License & Credits
- **Original Tutorial:** Paul McWhorter (TopTechBoy)
- **Music:** "Background Music" by Dmitrii Spis (NastelBom) via Pixabay.
- **License:** This project is licensed under [CC BY-NC-SA 4.0](../../LICENSE) (Attribution-NonCommercial-ShareAlike).