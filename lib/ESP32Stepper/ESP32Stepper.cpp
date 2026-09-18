#include "ESP32Stepper.h"

Stepper::Stepper(const int angle2step)
    : angle2step(angle2step), total_step(0), pins(nullptr) {}

void Stepper::attach(const uint8_t pins[4]) {
  this->pins = pins;
  pinMode(pins[0], OUTPUT);
  pinMode(pins[1], OUTPUT);
  pinMode(pins[2], OUTPUT);
  pinMode(pins[3], OUTPUT);
}

void Stepper::write(int16_t angle) {
  if (pins == nullptr)
    return; // Check if pins are attached
  int16_t steps =
      angle * angle2step; // Convert angle to steps based on gear ratio
  for (int16_t i = 0; i < abs(steps); i++) {
    total_step += (steps > 0) ? 1 : -1;
    total_step %= 4; // Ensure step is within the range of 0-3
    // Set the pins based on the current step
    switch (total_step) {
    case 0:
      digitalWrite(pins[0], HIGH);
      digitalWrite(pins[1], LOW);
      digitalWrite(pins[2], LOW);
      digitalWrite(pins[3], LOW);
      break;
    case 1:
      digitalWrite(pins[0], LOW);
      digitalWrite(pins[1], HIGH);
      digitalWrite(pins[2], LOW);
      digitalWrite(pins[3], LOW);
      break;
    case 2:
      digitalWrite(pins[0], LOW);
      digitalWrite(pins[1], LOW);
      digitalWrite(pins[2], HIGH);
      digitalWrite(pins[3], LOW);
      break;
    case 3:
      digitalWrite(pins[0], LOW);
      digitalWrite(pins[1], LOW);
      digitalWrite(pins[2], LOW);
      digitalWrite(pins[3], HIGH);
      break;
    }
  }
}