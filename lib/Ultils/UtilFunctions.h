#pragma once
#include <Arduino.h>

inline int16_t clip360(int16_t angle) {
  angle = angle % 360;
  if (angle < 0) angle += 360;
  return angle;
}

/*inline int16_t AngleDifference(int16_t angle1, int16_t angle2) {
  int16_t diff = clip360(angle1 - angle2);
  if (diff > 180) diff -= 360;
  if (diff < -180) diff += 360;
  return diff;
}*/