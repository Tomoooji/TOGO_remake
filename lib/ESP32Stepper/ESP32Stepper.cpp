#include "ESP32Stepper.h"

Stepper::Stepper(const uint8_t (&pins)[4], const int angle2step)
    : angle2step(angle2step), total_step(0), pins(pins) {}

void Stepper::begin() {
  pinMode(pins[0], OUTPUT);
  pinMode(pins[1], OUTPUT);
  pinMode(pins[2], OUTPUT);
  pinMode(pins[3], OUTPUT);
}

void Stepper::step(int16_t steps) {
  digitalWrite(pins[0], (steps + 3) & 2);
  digitalWrite(pins[1], (steps + 1) & 2);
  digitalWrite(pins[2], (steps + 2) & 2);
  digitalWrite(pins[3], (steps + 0) & 2);
}

void Stepper::moveTo(int16_t angle, int time_ms) {
  int16_t steps = angle * angle2step;
  int step_time = time_ms * 1000 / abs(steps);
  for (int16_t i = 0; i < abs(steps); i++) {
    total_step += (steps > 0) ? 1 : -1;
    step(total_step);
    delayMicroseconds(step_time);
  }
}

bool Stepper::moveStep() {
  if (total_step < target_step) {
    total_step++;
    step(total_step);
  } else if (total_step > target_step) {
    total_step--;
    step(total_step);
  }
  return total_step == target_step;
}