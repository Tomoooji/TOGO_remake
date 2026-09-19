#include "PCAServo.h"

PCAServo::PCAServo(PCA9685 &pwm, const uint8_t &chanel)
    : pwm(pwm), chanel(chanel) {}

void PCAServo::begin() { pwm.setPWM(this->chanel, 0, 0); }

void PCAServo::write() {
  int16_t pwm_value = map(this->angle, 0, 180, 0, 4095);
  pwm.setPWM(this->chanel, 0, pwm_value);
}

void PCAServo::write(int16_t angle) {
  this->setAngle(angle);
  this->write();
}