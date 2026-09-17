#pragma once
#include <Arduino.h>
#include "PCA9685.h"

class PCAServo{
  private:
    PCA9685& pwm;
    const uint8_t* chanel;
    int16_t angle;
  public:
    PCAServo(PCA9685& pwm);
    void begin(const uint8_t* chanel);
    int setAngle(int16_t angle);
    void write(int16_t angle);
    void write();
};