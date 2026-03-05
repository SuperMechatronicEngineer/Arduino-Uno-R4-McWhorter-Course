# Lesson 033: Photoresistor Controlled Servo Actuator

## Project Info
- **Project Name:** Photoresistor Controlled Servo Actuator
- **Lesson:** [Arduino Uno R4 WiFi LESSON 33: Using a Photoresistor in a Project](https://www.youtube.com/watch?v=AEJ-j7EDyZ4&list=PLGs0VKk2DiYyn0wN335MXpbi3PRJTMmex&index=35) by Paul McWhorter
- **Revision:** 1.2 (Final Version)
- **Date:** 2026-03-05
- **Author:** SuperMechatronicEngineer

## Project Description
This project implements an ambient light detection system that translates environmental brightness into precise mechanical movement. Using an **Arduino UNO R4 WiFi**, the system reads the analog signal from a Photoresistor (LDR) and commands an **SM-S2309S micro servo** to an angular position (0° to 160°) through a calibrated linear transfer function.

The project emphasizes software efficiency, using non-blocking timing and optimized data types to ensure a smooth response and readable telemetry.

## 📺 Video Documentation
The complete build and demonstration are available on Odysee:
- **Watch here:** [Arduino UNO R4 WiFi - Photoresistor Controlled Servo Actuator](https://odysee.com/@SuperMechatronicEngineer:8/033-Servo-and-Photoresistor:0)

## Technical Details
* **Target Hardware:** Arduino UNO R4 WiFi.
* **Active Components:** 
  * **SM-S2309S Micro Servo**: Actuator calibrated for a 0-160° range. Connected to **Digital Pin 3** (PWM).
  * **Photoresistor (LDR)**: Connected in a voltage divider circuit with a **4.7kΩ resistor** to Analog Pin **A0**.
* **Power Strategy:** Integrated 5V rail from the Arduino UNO R4 WiFi.
* **Baud Rate:** 115200 bps (High-speed telemetry).

## Software Logic & Architecture
* **Optimized User Feedback:** Telemetry is decoupled from the main loop via a 500ms timer (2Hz), preventing "data flooding" and ensuring human-readable logs while the servo updates at 50Hz.
* **Numerical Integrity:** Uses **32-bit integer promotion** during mapping calculations to prevent overflow and maintain precision without the overhead of floating-point math.
* **Mechanical Safety:** Enforces software constraints (0-160°) to prevent mechanical stall and hardware stress.

## Conversion Formulas
The firmware relies on explicit equations to map the 10-bit ADC values to the output domains:

### 1. Voltage Calculation
Calculated for real-time telemetry to monitor the voltage divider output:
$$V = \frac{ADC_{val} \cdot 5.0}{1023}$$

### 2. Angular Position (Linear Mapping)
The mechanical angle $\theta$ is calculated using a linear interpolation formula. This approach is preferred over the standard `map()` function for better transparency and control over data types:

$$\theta = \frac{(x - in\_min) \cdot (out\_max - out\_min)}{in\_max - in\_min} + out\_min$$

**Variables Definition:**
* **$x$**: The current raw value read from the ADC (**rawADC**).
* **$in\_min$**: The minimum calibration point (darkness), set to **143** (approx. 0.7V).
* **$in\_max$**: The maximum calibration point (full light), set to **1002** (approx. 4.9V).
* **$out\_min$**: The starting angle of the servo motor range (**0°**).
* **$out\_max$**: The maximum safe angle for the actuator (**160°**).

## License & Credits
- **Original Tutorial:** Paul McWhorter (TopTechBoy).
- **License:** This project is licensed under [CC BY-NC-SA 4.0](../../LICENSE) (Attribution-NonCommercial-ShareAlike).