#pragma once
#include <Arduino.h>

namespace Chanels{
  constexpr uint8_t dc_base_rotate[2] = {0,1};
  constexpr uint8_t dc_base_expand[2] = {2,3};
  constexpr uint8_t dc_base_lift[2] = {4,5};
  constexpr uint8_t dc_sort_slide[2] = {6,7};
  //constexpr uint8_t led_statas[] = {};
}
namespace PINs{
  constexpr uint8_t sv_hand_catchs[3] = {};
  constexpr uint8_t sv_sort_gates[2] = {};
  constexpr uint8_t st_hand_rotate[4] = {};
  constexpr uint8_t st_hand_expand[4] = {};
  constexpr uint8_t en_base_rotate[2] = {};
  constexpr uint8_t us_base_expand[2] = {};
  constexpr uint8_t us_base_lift[2] = {};
  constexpr uint8_t us_sort_slide[2] = {};
}
