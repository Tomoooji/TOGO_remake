#pragma once
#include <utility>
#include <Arduino.h>

//#include <Radian.h>
#include <ESP32Encoder.h>
#include <PCAMotor.h>
#include <PID.h>
#include <UtilFunctions.h>

class RotaryActuator {
private:
  PCAMotor motor;
  ESP32Encoder encoder;
  PID pid;
  float targetAngle;
  const float encoder_gear_ratio;
  const uint8_t (&enPin)[2];
  float angle_cash;

public:
  RotaryActuator(PCAMotor &&motor, ESP32Encoder &&encoder, PID &&pid,
                 const uint8_t (&enPin)[2], const float encoder_gear_ratio);
  void begin();
  void update();
  void setTargetAngle(float targetAngle) {
    this->targetAngle = clip360(targetAngle);
    pid.setTarget(targetAngle);
  }
  float getCurrentAngle() {
    return this->encoder.getCount() / encoder_gear_ratio;
  }
  float getTargetAngle() const { return targetAngle; }
};
