# Lesson 051: Measuring Distance using an HC-SR04 Ultrasonic Sensor

## Project Info
- **Project Name:** Measuring Distance using an HC-SR04 Ultrasonic Sensor
- **Lesson:** [Arduino Uno R4 WiFi LESSON 51: Using the HC-SR04 Ultrasonic Sensor for Echolocation](https://www.youtube.com/watch?v=BDmAOI6X31o&list=PLGs0VKk2DiYyn0wN335MXpbi3PRJTMmex&index=65) by Paul McWhorter
- **Revision:** 1.2 (Final Version)
- **Date:** 2026-04-13
- **Author:** SuperMechatronicEngineer

## Project Description
This project demonstrates a stable distance measurement system using the **HC-SR04 Ultrasonic Sensor** and the **Arduino UNO R4 WiFi**.

Instead of using standard blocking functions, this implementation relies on an **asynchronous, interrupt-driven approach**. This allows the microcontroller to measure the pulse duration accurately without stopping the main program execution, making the system more efficient and responsive.

## 🏗️ Software Architecture (OOP)
The firmware is designed using an Object-Oriented approach to separate the hardware timing from the main logic.

### 1. `UltrasonicAsync` Class
This class acts as the core driver for the sensor:
* **Interrupt-Driven:** Uses a hardware interrupt on the Echo pin to capture the start and end of the pulse.
* **Non-blocking Trigger:** Initiates the measurement and returns immediately, allowing other code to run while waiting for the sound echo.
* **Validation Logic:** Includes a built-in filter to ensure the calculated distance stays within the reliable physical range (3cm to 300cm).

### 2. Output Management
The main `loop()` includes a state-tracking system:
* **Anti-Spam Filter:** If the sensor goes out of range, the system prints a warning message exactly once. It stays silent until a valid object is detected again, keeping the Serial Monitor clean.
* **Timed Updates:** Measurements are triggered every 100ms to allow sound reflections to dissipate, ensuring signal stability.

## 📺 Video Documentation
The complete build and demonstration are available on Odysee:
- **Watch here:** [Arduino UNO R4 WiFi - Measuring Distance using an HC-SR04 Ultrasonic Sensor](https://odysee.com/@SuperMechatronicEngineer:8/HC-SR04:4)

## Technical Details
* **Control Board:** Arduino UNO R4 WiFi.
* **Sensor:** HC-SR04 Ultrasonic Sensor.
* **Operational Range:** 3cm to 300cm (calibrated).
* **Power Management:** 
    * **VCC:** The sensor is powered by the Arduino's **5V pin**.
    * **GND:** A **Common Ground** is established between the breadboard rail and the Arduino board to ensure signal integrity.
* **Communication:** Serial at 115200 baud.

### Measurement Logic
Distance is calculated based on the speed of sound ($343$ m/s or $0.0343$ cm/µs). Since the pulse travels to the object and back, the formula used is:
$$\text{Distance (cm)} = \frac{\text{Duration (µs)} \times 0.0343}{2} \approx \text{Duration} \times 0.01715$$

### Status Messaging
To provide a clean user interface, the system handles range errors as follows:
* **In Range:** Displays the distance in cm (e.g., `Distance: 25.4 cm`).
* **Out of Range:** If the object is closer than 3cm or further than 300cm, the monitor displays `Invalid measurement: Out of reliable range (3-300cm)` only once per event.

## Wiring Diagram
| Pin | Function | Connection |
| :--- | :--- | :--- |
| **5V** | Power | Sensor VCC |
| **GND** | Ground | Sensor GND (Common Ground) |
| **D2** | Trigger | Sensor TRIG Pin |
| **D3** | Echo | Sensor ECHO Pin (Interrupt Capable) |

## Implementation Notes
The use of the `CHANGE` interrupt on Pin 3 allows for high-precision timing of the pulse duration. By checking the pin state inside the Interrupt Service Routine (ISR), we can distinguish between the pulse start (Rising Edge) and the pulse end (Falling Edge) without using the blocking `pulseIn()` function.

## License & Credits
- **Original Tutorial:** Paul McWhorter (TopTechBoy).
- **License:** This project is licensed under [CC BY-NC-SA 4.0](../../LICENSE) (Attribution-NonCommercial-ShareAlike).