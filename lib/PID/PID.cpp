#include "PID.h"

PID::PID(const Gain &gain, const float &integral_limit)
    : gain(gain), integral_limit(integral_limit), target(0), integral(0), last_error(0), last_time(millis()) {}

void PID::reset() {
  integral = 0;
  last_error = 0;
  last_time = millis();
}

float PID::update(float input, float dt) {
  if (dt <= 0) {
    unsigned long current_time = millis();
    dt = (current_time - last_time) / 1000.0; // Convert milliseconds to seconds
    last_time = current_time;
  }
  float error = target - input;

  // Limit the integral term to prevent windup
  integral = constrain(integral + error * dt, -integral_limit, integral_limit);

  float derivative = (error - last_error) / dt;
  last_error = error;

  return gain.kp * error + gain.ki * integral + gain.kd * derivative;
}