#include "PCAMotor.h"

PCAMotor::PCAMotor(PCA9685 &pwm, const uint8_t (&chanels)[2], const int speed_max)
    : pwm(pwm), chanels(chanels), SPEED_MAX(speed_max) {}

void PCAMotor::begin() {
  pwm.setPWM(this->chanels[0], 0, 0);
  pwm.setPWM(this->chanels[1], 0, 0);
}

void PCAMotor::write(int16_t speed) {
  this->setSpeed(speed);
  this->write();
}

void PCAMotor::write() {
  int16_t pwm_value = map(this->speed, -SPEED_MAX, SPEED_MAX, 0, 4095);
  pwm.setPWM(chanels[0], 0, pwm_value);
  pwm.setPWM(chanels[1], 0, pwm_value);
}