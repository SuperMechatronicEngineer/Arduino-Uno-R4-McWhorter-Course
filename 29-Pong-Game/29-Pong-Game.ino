/*
 * Project: Single Player Pong Game
 * Lesson: Arduino Uno R4 WiFi LESSON 29: Create a Bouncing Pixel on the R4 WiFi LED Matrix
 * Revision: 1.2 - Final Version
 * Date: 2026-03-03
 * Author: SuperMechatronicEngineer
 * License: CC BY-NC-SA 4.0
 * See README.md for full technical documentation.
 */

#include "Arduino_LED_Matrix.h"

ArduinoLEDMatrix matrix;

// Pin Definitions (Inverted for specific wiring)
const uint8_t PIN_DOWN = 2; 
const uint8_t PIN_UP = 3;   

// Structure to encapsulate ball properties
struct Ball {
  int8_t x, y;   // 2D Coordinates (0-11 for x, 0-7 for y)
  int8_t dx, dy; // Direction vectors (-1 or 1)
};

Ball ball;
uint8_t paddleY = 4;   // Player's paddle position (Unsigned 8-bit for optimization)
uint8_t frame[8][12];  // Buffer to hold the matrix state before rendering

// Timing Management (Non-blocking)
unsigned long lastBallMove = 0;
const unsigned long ballInterval = 300; // Time in ms between ball steps

unsigned long lastPaddleMove = 0;
const unsigned long paddleInterval = 150; // Delay to make paddle movement manageable

/**
 * Resets the game to the starting conditions.
 * Sets the ball in the middle and resets timers to synchronize movements.
 */
void resetGame() {
  ball.x = 5; 
  ball.y = random(0, 8);
  ball.dx = -1; // Initially moves toward the player
  ball.dy = (random(0, 2) == 0) ? -1 : 1;
  paddleY = 4;
  
  unsigned long current = millis();
  lastBallMove = current;
  lastPaddleMove = current;
}

/**
 * Executes a visual blinking sequence when the player loses.
 * Fills the matrix entirely to provide clear feedback.
 */
void triggerGameOver() {
  for (int i = 0; i < 6; i++) {
    memset(frame, 1, sizeof(frame)); // Turn all pixels ON
    matrix.renderBitmap(frame, 8, 12);
    delay(250); 
    memset(frame, 0, sizeof(frame)); // Turn all pixels OFF
    matrix.renderBitmap(frame, 8, 12);
    delay(250);
  }
  resetGame(); // Return to start
}

/**
 * Translates the logical variables (ball and paddle positions) 
 * into the 2D frame buffer and sends it to the LED Matrix hardware.
 */
void renderCurrentState() {
  memset(frame, 0, sizeof(frame));    // Wipe the frame clean
  frame[paddleY][0] = 1;              // Set the paddle pixel
  frame[ball.y][ball.x] = 1;          // Set the ball pixel
  matrix.renderBitmap(frame, 8, 12);  // Display the buffer
}

/**
 * Handles the physics engine: wall bounces, paddle collisions,
 * and game-over conditions.
 */
void updatePhysics() {
  // Move ball based on its current heading
  ball.x += ball.dx;
  ball.y += ball.dy;

  // 1. Boundary Checks: Bouncing off top, bottom, and right edges
  if (ball.y <= 0 || ball.y >= 7) ball.dy = -ball.dy;
  if (ball.x >= 11) ball.dx = -ball.dx;

  // 2. Collision Check: Interaction with the player's paddle at Column 0
  if (ball.x == 0 && ball.y == paddleY) {
      // Impact detected: reverse direction but keep ball at x=0 for rendering
      ball.dx = -ball.dx; 
  } else if (ball.x < 0) {
      // Failure: Ball passed the paddle column. 
      triggerGameOver();
  }
}

void setup() {
  matrix.begin();
  
  pinMode(PIN_UP, INPUT_PULLUP);
  pinMode(PIN_DOWN, INPUT_PULLUP);
  
  randomSeed(analogRead(A0));
  
  resetGame();
}

void loop() {
  unsigned long currentMillis = millis();

  // Handle Paddle Input: Independent of ball speed
  if (currentMillis - lastPaddleMove >= paddleInterval) {
    bool inputDetected = false;
    
    // Up Button logic with boundary guard
    if (digitalRead(PIN_UP) == LOW && paddleY > 0) {
      paddleY--;
      inputDetected = true;
    }
    // Down Button logic with boundary guard
    if (digitalRead(PIN_DOWN) == LOW && paddleY < 7) {
      paddleY++;
      inputDetected = true;
    }
    
    if (inputDetected) {
      lastPaddleMove = currentMillis;
      renderCurrentState(); // Instant feedback for movement
    }
  }

  // Handle Ball Movement: Fixed temporal interval
  if (currentMillis - lastBallMove >= ballInterval) {
    lastBallMove = currentMillis;
    updatePhysics();
    renderCurrentState();
  }
}