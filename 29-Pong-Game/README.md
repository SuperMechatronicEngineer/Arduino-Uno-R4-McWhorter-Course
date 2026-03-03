# Lesson 029: Single Player Pong Game

## Project Info
- **Project Name:** Single Player Pong Game
- **Lesson:** [Arduino Uno R4 WiFi LESSON 29: Create a Bouncing Pixel on the R4 WiFi LED Matrix](https://www.youtube.com/watch?v=QrAduIMIhxE&list=PLGs0VKk2DiYyn0wN335MXpbi3PRJTMmex&index=34) by Paul McWhorter
- **Revision:** 1.2 (Final Version)
- **Date:** 2026-03-03
- **Author:** SuperMechatronicEngineer

## Project Description
This project evolves a simple physics simulation into a fully functional **Single Player Pong Game** using the integrated 8x12 LED matrix. The system features a real-time game engine where the player controls a paddle to deflect a ball.

The core objective of this revision was to implement an **asynchronous architecture** to handle user input and ball physics simultaneously without using blocking functions like `delay()`.

## 📺 Video Documentation
The complete build and demonstration are available on Odysee:
- **Watch here:** [Arduino UNO R4 WiFi - Single Player Pong Game](https://odysee.com/@SuperMechatronicEngineer:8/Arduino-UNO-R4-WiFi-Pong-Game:6)

## Technical Details
* **Target Hardware:** Arduino UNO R4 WiFi.
* **Display:** Integrated 12x8 LED Matrix.
* **Input (2x Push Buttons - Internal Pull-up):** 
  * **Pin 2:** Paddle DOWN 
  * **Pin 3:** Paddle UP

## Software Logic & Architecture
* **Asynchronous Multi-Timing:** The engine utilizes dual logical timers based on `millis()`. This allows for independent polling frequencies: **150ms** for paddle input (low latency) and **300ms** for ball physics, preventing the "stuttering" effect common in single-loop architectures.
* **Collision Engine:** Implements a conditional hit-box check on Column 0. The firmware evaluates the ball's Y-coordinate against the `uint8_t paddleY` state. A successful hit inverts the horizontal vector ($dx$); a miss triggers the Game Over sequence.
* **Game State Management:** Upon losing, the system enters a blocking **Game Over state** (3000ms duration) before re-initializing the environment.
* **Stochastic Realism:** Employs `randomSeed()` on an open analog pin (**A0**) to break pseudo-random determinism, ensuring unique trajectory initialization for every session.
* **High-Speed Rendering:** Employs a `uint8_t` virtual frame buffer with `memset()` for instantaneous memory clearing, ensuring zero "ghosting" artifacts during the `matrix.renderBitmap()` execution.

## License & Credits
- **Original Tutorial:** Paul McWhorter (TopTechBoy).
- **License:** This project is licensed under [CC BY-NC-SA 4.0](../../LICENSE) (Attribution-NonCommercial-ShareAlike).