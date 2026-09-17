#pragma once
#include <Arduino.h>

namespace GAINs{
  // PID gains
  inline constexpr float pid_base_rotate[3] = {0.5,0.0,0.0};
  inline constexpr float pid_base_expand[3] = {0.5,0.0,0.0};
  inline constexpr float pid_base_lift[3] = {0.5,0.0,0.0};
  inline constexpr float pid_sort_slide[3] = {1.5,0.0,0.0};
  // Position configuration
  inline constexpr float pos_base_rotate[15];
  inline constexpr float pos_base_expand[15];
  inline constexpr float pos_base_lift[2];
  inline constexpr float pos_sort_slide[4];
  inline constexpr float pos_hand_expand[2];
  inline constexpr float pos_hand_catch[3];
  // gear ratios
  inline constexpr float pulse2ang_base_rotate = 1024;
  inline constexpr float gear_hand_rotate = 1.0;
  // speed limits
  inline constexpr float speed_max_base_rotate = 100.0;
  inline constexpr float speed_max_base_expand = 100.0;
  inline constexpr float speed_max_base_lift = 100.0;
  inline constexpr float speed_max_sort_slide = 100.0;
  inline constexpr float speed_max_hand_expand = 10.0;
  inline constexpr float speed_max_hand_rotate = 10.0;

}