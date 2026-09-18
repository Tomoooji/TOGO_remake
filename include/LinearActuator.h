#pragma once
#include <Arduino.h>

#include "PCAMotor.h"
#include "UltraSonic.h"
#include "PID.h"

class LinearActuator{
  public:
    LinearActuator(PCAMotor& dcMotor, HCSR04& ultrasonic, PID& pid);
    void begin(const uint8_t* chanel, const uint8_t* trigPin);
    void setTargetDistance(float targetDistance);
    void update();
};