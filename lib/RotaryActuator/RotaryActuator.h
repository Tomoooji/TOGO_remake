#pragma once
#include <utility>
#include <Arduino.h>

#include <ESP32Encoder.h>
#include <PCAMotor.h>
#include <Radian.h>
#include <PID.h>
//#include <UtilFunctions.h>

class RotaryActuator {
private:
  PCAMotor motor;
  ESP32Encoder encoder;
  PID<RadianAbsPi<float>> pid;
  RadianAbsPi<float> targetAngle;
  const float encoder_gear_ratio;
  const uint8_t (&enPin)[2];

public:
  RotaryActuator(PCAMotor &&motor, ESP32Encoder &&encoder, PID<RadianAbsPi<float>> &&pid,
                 const uint8_t (&enPin)[2], const float encoder_gear_ratio);
  void begin();
  void update();
  void setTargetAngle(RadianAbsPi<float> rgetAngle) {
    pid.setTarget(targetAngle);
  }
  RadianAbsPi<float> getCurrentAngle() {
    return RadianAbsPi<float>(this->encoder.getCount() / encoder_gear_ratio).normalize();
  }
  RadianAbsPi<float> getTargetAngle() const { return targetAngle.normalize(); }
};
