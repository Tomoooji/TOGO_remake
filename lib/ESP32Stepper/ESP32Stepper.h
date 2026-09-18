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
  void write(int16_t angle);
  float getAngle();
};
