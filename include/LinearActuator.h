#pragma once
#include <Arduino.h>

#include "PCAMotor.h"
#include "PID.h"
#include "UltraSonic.h"

class LinearActuator {
private:
  PCAMotor &motor;
  HCSR04 &ultrasonic;
  PID &pid;
  float targetDistance;
  const float sensor_position_offset =
      0.0; // Offset to account for the physical position of the ultrasonic
           // sensor
public:
  LinearActuator(PCAMotor &dcMotor, HCSR04 &ultrasonic, PID &pid);
  void begin(const uint8_t *chanel, const uint8_t *usPin);
  void setTargetDistance(float targetDistance) {
    this->targetDistance = targetDistance;
    pid.setTarget(targetDistance);
  }
  float getTargetDistance() const { return targetDistance; }
  float getCurrentDistance() const {
    return ultrasonic.getDistance() + sensor_position_offset;
  }
  void update();
};