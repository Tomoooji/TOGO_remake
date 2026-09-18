#include "RotaryActuator.h"

RotaryActuator::RotaryActuator(PCAMotor &motor, ESP32Encoder &encoder, PID &pid)
    : motor(motor), encoder(encoder), pid(pid), targetAngle(0) {}

void RotaryActuator::begin(const uint8_t *chanel, const uint8_t *enPin) {
  motor.begin(chanel);
  encoder.attachFullQuad(*enPin, *(enPin + 1));
  pid.reset();
}

void RotaryActuator::update() {
  float currentAngle = getCurrentAngle();
  float controlSignal = pid.update(currentAngle);
  motor.write(controlSignal);
}
