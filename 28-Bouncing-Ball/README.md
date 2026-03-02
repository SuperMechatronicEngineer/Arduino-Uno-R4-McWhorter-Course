# Lesson 028: The Bouncing Pixel

## Project Info
- **Project Name:** The Bouncing Pixel
- **Lesson:** [Arduino Uno R4 WiFi LESSON 28: Using the LED Matrix on the Arduino R4 WiFi](https://www.youtube.com/watch?v=P-wJEo8hUCg&list=PLGs0VKk2DiYyn0wN335MXpbi3PRJTMmex&index=31) by Paul McWhorter
- **Revision:** 1.2 (Final Version)
- **Date:** 2026-03-02
- **Author:** SuperMechatronicEngineer

## Project Description
This project implements a **dynamic physics simulation** on the integrated 8x12 LED matrix. The system calculates the trajectory of a single pixel in real-time, simulating elastic collisions against the matrix boundaries using a dedicated **vector-based struct architecture**.

The core objective is to move beyond static frame-by-step animations, creating a kinetic environment where the pixel acts as a physical entity with its own heading, velocity, and boundary awareness.

## 📺 Video Documentation
The complete build and demonstration are available on Odysee:
- **Watch here:** [Arduino UNO R4 WiFi - The Bouncing Pixel](https://odysee.com/@SuperMechatronicEngineer:8/028-Bouncing-Ball:5)

## Technical Details
* **Target Hardware:** Arduino UNO R4 WiFi.
* **Display:** Integrated 12x8 LED Matrix.

## Software Logic & Architecture
* **Encapsulated Vector Structure:** The project implements a `struct Ball` to group spatial coordinates ($x, y$) and velocity vectors ($dx, dy$). This object-oriented approach ensures clean memory management and allows the pixel to be treated as a single physical entity with an independent state.
* **Stochastic Vector Initialization:** The `randomSeed()` function leverages atmospheric noise from an open analog pin (**A0**) to generate a unique starting position and velocity. This ensures the ball never follows the same path twice, breaking the determinism of standard pseudo-random algorithms.
* **Optimized Frame Buffering:** To ensure fluid motion at 100ms intervals, the code utilizes a `uint8_t` buffer and `memset()` for high-speed memory clearing. This prevents "ghosting" and ensures that only the current calculated position is rendered via `matrix.renderBitmap()`.
* **Kinetic Boundary Logic:** The firmware updates the pixel's coordinates and immediately evaluates them against the matrix limits ($12 \times 8$). Upon detecting a boundary violation (Left/Right or Top/Bottom), the specific velocity component is inverted, creating a seamless and mathematically accurate bounce effect.

## License & Credits
- **Original Tutorial:** Paul McWhorter (TopTechBoy).
- **License:** This project is licensed under [CC BY-NC-SA 4.0](../../LICENSE) (Attribution-NonCommercial-ShareAlike).