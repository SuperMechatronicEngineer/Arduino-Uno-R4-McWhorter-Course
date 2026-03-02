/*
 * Project: The Bouncing Pixel
 * Lesson: Arduino Uno R4 WiFi LESSON 28: Using the LED Matrix on the Arduino R4 WiFi
 * Revision: 1.2 - Final Version
 * Date: 2026-03-01
 * Author: SuperMechatronicEngineer
 * License: CC BY-NC-SA 4.0
 * See README.md for full technical documentation.
 */

#include "Arduino_LED_Matrix.h"

// Create an instance of the LED matrix controller
ArduinoLEDMatrix matrix;

// Define a structure to keep the ball's position and speed organized
struct Ball {
  int8_t x, y;   // Current position (x=column, y=row)
  int8_t dx, dy; // Direction/Velocity (-1 or 1)
};

// Declare a global variable for the ball
Ball ball;

// 2D array representing the LED matrix state (8 rows x 12 columns)
uint8_t frame[8][12];

void setup() {
  // Initialize the LED matrix
  matrix.begin();
  
  // Seed the random number generator using an unconnected analog pin
  // to ensure a different starting position/direction each time
  randomSeed(analogRead(A0));

  // Set initial random position for the ball
  // Avoiding the absolute edges (0 and 11 for x, 0 and 7 for y)
  ball.x = random(1, 11);
  ball.y = random(1, 7);

  // Set initial random direction (-1 for left/up, 1 for right/down)
  ball.dx = (random(0, 2) == 0) ? -1 : 1;
  ball.dy = (random(0, 2) == 0) ? -1 : 1;
}

void loop() {
  // 1. Clear the virtual frame buffer (turn all LEDs off)
  memset(frame, 0, sizeof(frame));

  // 2. Update the ball's position based on its current direction
  ball.x += ball.dx;
  ball.y += ball.dy;

  // 3. Handle boundary collisions (bouncing)
  
  // Check horizontal boundaries (left and right)
  if (ball.x <= 0 || ball.x >= 11) {
    ball.dx = -ball.dx; // Reverse horizontal direction
  }
  
  // Check vertical boundaries (top and bottom)
  if (ball.y <= 0 || ball.y >= 7) {
    ball.dy = -ball.dy; // Reverse vertical direction
  }

  // 4. Turn on the LED at the new position in the frame buffer
  frame[ball.y][ball.x] = 1;

  // 5. Render the frame buffer to the physical LED matrix
  matrix.renderBitmap(frame, 8, 12);

  // 6. Pause for a short time to control the animation speed (in milliseconds)
  delay(100);
}