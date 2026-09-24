#pragma once
#include <Arduino.h>
#include <utility>

#include <PCAMotor.h>
#include <PID.h>
#include <UltraSonicAsync.h>

class LinearActuator {
private:
  constexpr static float default_min_distance_error = 0.5f;
  PCAMotor motor;
  HCSR04Async ultrasonic;
  PID pid;
  float targetDistance;
  const float &sensor_position_offset;
  const float &min_distance_error = default_min_distance_error;

public:
  LinearActuator(PCAMotor &&dcMotor, HCSR04Async &&ultrasonic, PID &&pid,
                 const float &sensor_position_offset,
                 const float &min_distance_error);
  LinearActuator(PCAMotor &&dcMotor, HCSR04Async &&ultrasonic, PID &&pid,
                 const float &sensor_position_offset);
  void begin();
  bool update();
  void setTargetDistance(float targetDistance) {
    this->targetDistance = targetDistance;
    pid.setTarget(targetDistance);
  }
  float getTargetDistance() const { return targetDistance; }
  float getCurrentDistance() const {
    return ultrasonic.getDistance() + sensor_position_offset;
  }
};
