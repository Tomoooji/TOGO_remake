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

public:
  RotaryActuator(PCAMotor &motor, ESP32Encoder &encoder, PID &pid);
  void begin(const uint8_t *chanel, const uint8_t *enPin);
  void setTargetAngle(float targetAngle) {
    this->targetAngle = targetAngle;
    pid.setTarget(targetAngle);
  }
  float getTargetAngle() const { return targetAngle; }
  float getCurrentAngle() const {
    return encoder.getCount() / encoder_gear_ratio;
  }
  void update();
};