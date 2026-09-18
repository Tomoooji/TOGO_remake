#pragma once
#include <Arduino.h>

class PID{
  public:
    PID(const float gain[3]);
    void setGain(const float gain[3]);
    void setTarget(float target);
    void reset();
    float update(float input, float dt);
};