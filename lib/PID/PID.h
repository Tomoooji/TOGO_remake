#pragma once
#include <Arduino.h>

class PID {
public:
  struct Gain {
    float kp;
    float ki;
    float kd;
  };
private:
  const Gain &gain;
  const float &integral_limit;
  float target;
  float integral;
  float last_error;
  unsigned long last_time;

public:
  PID(const Gain &gain, const float &integral_limit);
  void reset();
  float update(float input, float dt = 0);
  void setTarget(float target) {
    this->target = target;
    last_time = millis();
  }
};