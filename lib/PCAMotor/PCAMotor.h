#pragma once
#include <PCA9685.h>

class PCAMotor {
private:
  PCA9685 &pwm;
  const uint8_t (&chanels)[2];
  int16_t speed;
  const int16_t SPEED_MAX;

public:
  PCAMotor(PCA9685 &pwm, const uint8_t (&chanels)[2], const int speed_max = 255);
  void begin();
  void write(int16_t speed);
  void write();
  int setSpeed(int16_t speed) {
    this->speed = constrain(speed, -SPEED_MAX, SPEED_MAX);
    return speed;
  }
};
