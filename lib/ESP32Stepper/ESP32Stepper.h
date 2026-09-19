#pragma once
#include "UtilFunctions.h"
#include <Arduino.h>

class Stepper {
private:
  const uint8_t (&pins)[4];
  const int angle2step;
  int total_step;
  int target_step;

public:
  Stepper(const uint8_t (&pins)[4], const int angle2step);
  void begin();
  void step(int16_t steps);

  // こっちはブロッキング
  void moveTo(int16_t angle, int time_ms);

  // こっちは非ブロッキング(回転速度はメインのループ速度に依存する)
  void setTargetAngle(int16_t angle) { target_step = angle * angle2step; }
  int16_t getTargetAngle() const { return clip360(target_step / angle2step); }
  int16_t getCurrentAngle() const { return clip360(total_step / angle2step); }
  bool moveStep();
  
  int16_t getAngle() const { return clip360(total_step / angle2step); }
};
