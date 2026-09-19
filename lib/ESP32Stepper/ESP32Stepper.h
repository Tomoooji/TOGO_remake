#pragma once
#include <Arduino.h>

class Stepper {
private:
  const uint8_t *pins;
  const int angle2step;
  int total_step;
  int target_step;

public:
  Stepper(const int angle2step);
  void attach(const uint8_t pins[4]);
  void step(int16_t steps);

  // こっちはブロッキング
  void moveTo(int16_t angle, int time_ms);

  // こっちは非ブロッキング(回転速度はメインのループ速度に依存する)
  void setTargetAngle(int16_t angle) { target_step = angle * angle2step; }
  int16_t getTargetAngle() const { return target_step / angle2step; }
  bool moveStep();
  
  float getAngle() const { return total_step / static_cast<float>(angle2step); }
};
