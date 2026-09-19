#pragma once
#include <Arduino.h>

class PID {
private:
  enum { P, I, D };
  const float *gain;
  float target;
  float integral;
  float last_error;
  unsigned long last_time;
  const float integral_limit =
      1000.0; // Limit for integral term to prevent windup

public:
  PID(const float *gain);
  void reset();
  float update(float input, float dt = 0);
  void setTarget(float target) {
    this->target = target;
    last_time = millis();
  }
  void setGain(const float *gain) { this->gain = gain; }
};