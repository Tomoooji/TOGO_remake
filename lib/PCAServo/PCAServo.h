#pragma once
#include "PCA9685.h"
#include "Utils.h"

class PCAServo {
private:
  PCA9685 &pwm;
  const uint8_t &chanel;
  int16_t angle;

public:
  PCAServo(PCA9685 &pwm, const uint8_t &chanel);
  void begin();
  void write();
  void write(int16_t angle);
  int setAngle(int16_t angle) {
    this->angle = clip360(angle);
    return this->angle;
  }
};