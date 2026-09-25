#include "RotaryActuator.h"

RotaryActuator::RotaryActuator(PCAMotor &&motor, ESP32Encoder &&encoder, PID<RadianAbsPi<float>> &&pid, const uint8_t (&enPin)[2], const float encoder_gear_ratio)
    : motor{std::move(motor)}, encoder{std::move(encoder)}, pid{std::move(pid)}, enPin(enPin), targetAngle(0), encoder_gear_ratio(encoder_gear_ratio) {}

void RotaryActuator::begin() {
  motor.begin();
  ESP32Encoder::useInternalWeakPullResistors = puType::up;
  encoder.attachFullQuad(this->enPin[0], this->enPin[1]);
  encoder.clearCount();
  pid.reset();
}

void RotaryActuator::update() {
  motor.write(float(pid.update(getCurrentAngle())));///
}

