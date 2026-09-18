#pragma once
#include <Arduino.h>
#include "PCA9685.h"

class PCAMotor{
  private:
    PCA9685& pwm;
    const uint8_t* chanels;
    int16_t speed;
    const int16_t SPEED_MAX;
  public:
    PCAMotor(PCA9685& pwm, const int speed_max = 255):pwm(pwm),SPEED_MAX(speed_max){};
    void begin(const uint8_t* chanels);
    int setSpeed(int16_t speed);
    void write(int16_t speed);
    void write();
};

