#include "LinearActuator.h"

LinearActuator::LinearActuator(PCAMotor &dcMotor, HCSR04 &ultrasonic, PID &pid,
                               const float sensor_position_offset,
                               const float min_distance_error)
    : motor(dcMotor), ultrasonic(ultrasonic), pid(pid), targetDistance(0),
      sensor_position_offset(sensor_position_offset),
      min_distance_error(min_distance_error) {}

void LinearActuator::begin(const uint8_t *chanel, const uint8_t *usPin) {
  motor.begin(chanel);
  ultrasonic.begin(usPin);
  pid.reset();
}

bool LinearActuator::update() {
  //ultrasonic.update();
  float currentDistance = getCurrentDistance();
  float controlSignal = pid.update(currentDistance);
  motor.write(controlSignal);
  return abs(currentDistance - targetDistance) < this->min_distance_error;
}
