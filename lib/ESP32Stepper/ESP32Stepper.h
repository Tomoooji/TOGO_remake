#pragma once
#include <Arduino.h>

class Stepper {
private:
  const uint8_t *pins;
  const int angle2step;
  int total_step;

public:
  Stepper(const int angle2step);
  void attach(const uint8_t pins[4]);
  void step(int16_t steps);
  void moveTo(int16_t angle, int time_ms);
  float getAngle() const { return total_step / static_cast<float>(angle2step); }
};
