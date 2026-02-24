# Lesson 022: Control a Servo Motor using a Potentiometer

## Project Info
- **Project Name:** Control a Servo Motor using a Potentiometer
- **Lesson:** [Arduino Uno R4 WiFi LESSON 22: Control a Servo With Your Arduino](https://www.youtube.com/watch?v=mDyQkTIzDsc&list=PLGs0VKk2DiYyn0wN335MXpbi3PRJTMmex&index=24) by Paul McWhorter
- **Revision:** 1.2 (Final Version)
- **Date:** 2026-02-24
- **Author:** SuperMechatronicEngineer

## Project Description
This project implements a precision-oriented control system for a micro servo motor using an **Arduino UNO R4 WiFi**. The core objective is to translate the analog input from a 10k potentiometer into a precise mechanical position (0° to 160°) through an explicit linear transfer function.

The system ensures that the servo operates within its physical safety limits while providing detailed feedback via the Serial Monitor. This project emphasizes mathematical transparency and hardware stability.

## 📺 Video Documentation
The complete build and demonstration are available on Odysee:
- **Watch here:** [Arduino UNO R4 WiFi - Control a Servo Motor using a Potentiometer](https://odysee.com/@SuperMechatronicEngineer:8/022-Servo-Pot:1)

## Technical Details
* **Target Hardware:** Arduino UNO R4 WiFi.
* **Active Components:** 
    * **SM-S2309S Micro Servo**: Actuator calibrated for a 0-160° range. Connected to **Digital Pin 11** (PWM).
    * **10kΩ Potentiometer**: Analog input device connected to **Analog Pin A0**.
    * **External Power Supply (5V 1A)**: Dedicated source for high-current motor loads. draw and component longevity.
* **Wiring Strategy:** Common Ground architecture between Arduino and external power.
* **Baud Rate:** 115200 bps (High-speed telemetry).

## Software Logic & Architecture
* **Explicit Mapping:** Utilizes slope coefficients instead of the standard `map()` function for both voltage and angle calculations.
* **State-Change Telemetry:** Employs a C++ `static` local variable to filter redundant data, updating the Serial Monitor only when physical movement is detected.
* **Mechanical Safety:** Enforces software constraints (0-160°) to prevent mechanical stall and servo overheating, respecting the physical limits of the SM-S2309S.
* **Optimized Types:** Uses `float` for calculation precision and `byte` for hardware commands to optimize memory usage.

## Conversion Formulas
The firmware relies on explicit linear equations to map the 10-bit ADC values (0 to 1023) to their respective domains:
* **Voltage Calculation:** Derived from the system's resolution ($V_{ref} / ADC_{max}$):
  $$V = \frac{5.0}{1023} \cdot ADC_{val}$$
* **Angular Position:** Calculated using the specific mechanical slope for the 160° range:
  $$\theta = \frac{160.0}{1023} \cdot ADC_{val}$$

## License & Credits
- **Original Tutorial:** Paul McWhorter (TopTechBoy).
- **License:** This project is licensed under [CC BY-NC-SA 4.0](../../LICENSE) (Attribution-NonCommercial-ShareAlike).