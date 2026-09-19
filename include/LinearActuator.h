#pragma once
#include <Arduino.h>

#include <PCAMotor.h>
#include <PID.h>
#include <UltraSonic.h>

class LinearActuator {
private:
  PCAMotor &motor;
  HCSR04 &ultrasonic;
  PID &pid;
  float targetDistance;
  const float sensor_position_offset;
  const float min_distance_error;

public:
  LinearActuator(PCAMotor &dcMotor, HCSR04 &ultrasonic, PID &pid,
                 const float sensor_position_offset = 0.0f,
                 const float min_distance_error = 0.5f);
  void begin(const uint8_t *chanel, const uint8_t *usPin);
  void setTargetDistance(float targetDistance) {
    this->targetDistance = targetDistance;
    pid.setTarget(targetDistance);
  }
  float getTargetDistance() const { return targetDistance; }
  float getCurrentDistance() const {
    return ultrasonic.getDistance() + sensor_position_offset;
  }
  bool update();
};