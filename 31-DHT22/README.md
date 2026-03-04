# Lesson 031: Interactive DHT22 Climate Monitor for Arduino UNO R4 WiFi

## Project Info
- **Project Name:** Interactive DHT22 Climate Monitor for Arduino UNO R4 WiFi
- **Lesson:** [Arduino Uno R4 WiFi LESSON 31: Measuring Temperature and Humidity Using the DHT11](https://www.youtube.com/watch?v=AXLgZzLfwI8&list=PLGs0VKk2DiYyn0wN335MXpbi3PRJTMmex&index=33) by Paul McWhorter
- **Revision:** 1.2 (Final Version)
- **Date:** 2026-03-04
- **Author:** SuperMechatronicEngineer

## Project Description
This project implements an interactive **Environmental Monitor** on the Arduino UNO R4 WiFi, providing real-time visualization of **Ambient Temperature**, **Relative Humidity**, and the **Calculated Heat Index** (Apparent Temperature).

The system features an **optimized data-handling routine**, allowing the user to trigger these climate metrics through a dedicated physical interface and the integrated 12x8 LED matrix.

## 📺 Video Documentation
The complete build and demonstration are available on Odysee:
- **Watch here:** [Arduino UNO R4 WiFi - Interactive DHT22 Climate Monitor](https://odysee.com/@SuperMechatronicEngineer:8/31-DHT22:f)

## Technical Details
* **Target Hardware:** Arduino UNO R4 WiFi.
* **Display:** Integrated 12x8 LED Matrix (utilizing `ArduinoGraphics`).
* **Sensor:** DHT22 (AM2302) humidity and thermistor sensor.
* **Input Interface:** 
  * **Component:** 1x Tactile Push Button.
  * **Pin:** Digital **Pin 2**.
  * **Configuration:** Internal Pull-up resistor enabled (Active LOW).

## Software Logic & Architecture
* **Semi-Asynchronous Sampling Logic:** To overcome the DHT22’s slow response time (approx. 2s) without stalling the micro during idle states, the firmware implements a `millis()` based architecture. 
  * **Idle State:** The sensor is sampled every **2000ms** in the background while waiting for user input.
  * **Display State:** Note that the `ArduinoGraphics` scrolling function is **blocking**. During the animation, the background sampling is momentarily suspended to dedicate full CPU resources to smooth LED rendering. 
* **Robust Manual Triggering:** The system utilizes a software debouncing algorithm (**50ms window**) to filter mechanical noise from the push button. This "on-demand" approach keeps the matrix dark until a deliberate press is detected, triggering an immediate data scroll.
* **Memory Efficiency:** Uses the `F()` macro for all static strings to conserve SRAM.

## License & Credits
- **Original Tutorial:** Paul McWhorter (TopTechBoy).
- **License:** This project is licensed under [CC BY-NC-SA 4.0](../../LICENSE) (Attribution-NonCommercial-ShareAlike).