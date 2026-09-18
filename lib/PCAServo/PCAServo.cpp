#include "PCAServo.h"

PCAServo::PCAServo(PCA9685 &pwm) : pwm(pwm) {}

void PCAServo::attach(const uint8_t *chanel) {
  this->chanel = chanel;
  pwm.setPWM(*chanel, 0, 0);
}

int PCAServo::setAngle(int16_t angle) {
  this->angle = angle;
  return angle;
}

void PCAServo::write(int16_t angle) {
  this->setAngle(angle);
  this->write();
}

void PCAServo::write() {
  int16_t pwm_value = map(this->angle, 0, 180, 0, 4095);
  pwm.setPWM(*this->chanel, 0, pwm_value);
}