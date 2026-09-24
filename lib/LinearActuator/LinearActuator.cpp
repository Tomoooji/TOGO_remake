#include "LinearActuator.h"

LinearActuator::LinearActuator(PCAMotor &&dcMotor, HCSR04Async &&ultrasonic, PID &&pid,
                               const float &sensor_position_offset,
                               const float &min_distance_error)
    : motor{std::move(dcMotor)}, ultrasonic{std::move(ultrasonic)}, pid{std::move(pid)},
      sensor_position_offset(sensor_position_offset), min_distance_error(min_distance_error), targetDistance(0) {}
LinearActuator::LinearActuator(PCAMotor &&dcMotor, HCSR04Async &&ultrasonic, PID &&pid,
                               const float &sensor_position_offset)
    : motor{std::move(dcMotor)}, ultrasonic{std::move(ultrasonic)}, pid{std::move(pid)},
      sensor_position_offset(sensor_position_offset), targetDistance(0) {}

void LinearActuator::begin() {
  motor.begin();
  ultrasonic.begin();
  pid.reset();
}

bool LinearActuator::update() {
  float currentDistance = getCurrentDistance();
  float controlSignal = pid.update(currentDistance);
  motor.write(controlSignal);
  return abs(currentDistance - targetDistance) < this->min_distance_error;
}

