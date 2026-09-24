#include "RotaryActuator.h"

RotaryActuator::RotaryActuator(PCAMotor &&motor, ESP32Encoder &&encoder, PID &&pid, const uint8_t (&enPin)[2], const float encoder_gear_ratio)
    : motor{std::move(motor)}, encoder{std::move(encoder)}, pid{std::move(pid)}, enPin(enPin), targetAngle(0), encoder_gear_ratio(encoder_gear_ratio) {}

void RotaryActuator::begin() {
  motor.begin();
  ESP32Encoder::useInternalWeakPullResistors = puType::up;
  encoder.attachFullQuad(this->enPin[0], this->enPin[1]);
  encoder.clearCount();
  pid.reset();
  angle_cash = getCurrentAngle();
}

void RotaryActuator::update() {
  float currentAngle = getCurrentAngle();
  if (currentAngle-angle_cash > 180) {
    currentAngle -= 360;
  } else if (currentAngle-angle_cash < -180) {
    currentAngle += 360;
  }
  angle_cash = currentAngle;
  float controlSignal = pid.update(currentAngle);
  motor.write(controlSignal);
}

