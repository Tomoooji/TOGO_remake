#include "LinearActuator.h"

LinearActuator::LinearActuator(PCAMotor &dcMotor, HCSR04 &ultrasonic, PID &pid)
    : motor(dcMotor), ultrasonic(ultrasonic), pid(pid), targetDistance(0) {}

void LinearActuator::begin(const uint8_t *chanel, const uint8_t *usPin) {
  motor.begin(chanel);
  ultrasonic.begin(usPin);
  pid.reset();
}

void LinearActuator::update() {
  ultrasonic.update();
  float currentDistance = getCurrentDistance();
  float controlSignal = pid.update(currentDistance);
  motor.write(controlSignal);
}
