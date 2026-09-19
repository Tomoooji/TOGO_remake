#include "RotaryActuator.h"
//#include <Utils.h>

RotaryActuator::RotaryActuator(PCAMotor &motor, ESP32Encoder &encoder, PID &pid, const uint8_t (&enPin)[2])
    : motor(motor), encoder(encoder), pid(pid), enPin(enPin), targetAngle(0) {}

void RotaryActuator::begin() {
  motor.begin();
  encoder.attachFullQuad(this->enPin[0], this->enPin[1]);
  pid.reset();
}

void RotaryActuator::update() {
  float currentAngle = getCurrentAngle();
  float controlSignal = pid.update(currentAngle);
  motor.write(controlSignal);
}

