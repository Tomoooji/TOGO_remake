#pragma once
#include <Arduino.h>

#include "PCAMotor.h"
#include "ESP32Encoder.h"
#include "PID.h"

class RotaryActuator{
  public:
    RotaryActuator(PCAMotor& dcMotor, ESP32Encoder& encoder, PID& pid);
    void begin(const uint8_t* chanel, const uint8_t* enPin);
    void setTargetAngle(float targetAngle);
    void update();
};