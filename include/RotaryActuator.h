#pragma once
#include <Arduino.h>

#include "ESP32Encoder.h"
#include "PCAMotor.h"
#include "PID.h"

class RotaryActuator {
private:
  PCAMotor &motor;
  ESP32Encoder &encoder;
  PID &pid;
  float targetAngle;
  const float encoder_gear_ratio = 1.0;
  const uint8_t (&enPin)[2];

public:
  RotaryActuator(PCAMotor &motor, ESP32Encoder &encoder, PID &pid,
                 const uint8_t (&enPin)[2]);
  void begin();
  void update();
  void setTargetAngle(float targetAngle) {
    this->targetAngle = clip360(targetAngle);
    pid.setTarget(targetAngle);
  }
  float getCurrentAngle() const {
    return encoder.getCount() / encoder_gear_ratio;
  }
  float getTargetAngle() const { return targetAngle; }
};
