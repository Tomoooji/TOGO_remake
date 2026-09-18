#pragma once
#include <Arduino.h>

class Stepper{
  public:
    Stepper();
    void attach(const uint8_t pin[4]);
    void write(int16_t angle);
};