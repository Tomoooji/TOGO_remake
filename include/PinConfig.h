#pragma once
#include <Arduino.h>

namespace Channels {
inline constexpr uint8_t dc_base_rotate[2] = {0, 1};
inline constexpr uint8_t dc_base_expand[2] = {2, 3};
inline constexpr uint8_t dc_base_lift[2] = {4, 5};
inline constexpr uint8_t dc_sort_slide[2] = {6, 7};

inline constexpr uint8_t sv_hand_catchs[3] = {8, 9, 10}; // {left, middle, right}
inline constexpr uint8_t sv_sort_gates[2] = {11, 12}; // {left, right}

// inline constexpr uint8_t led_statas[] = {};
} // namespace Channels

namespace Pins {
// inline constexpr uint8_t sv_hand_catchs[3] = {4, 13, 14}; // {left, middle,
// right} inline constexpr uint8_t sv_sort_gates[2] = {16, 5}; // {left, right}

inline constexpr uint8_t st_hand_rotate[4] = {18, 19, 23, 25};
inline constexpr uint8_t st_hand_expand[4] = {26, 15, 0, 2};

inline constexpr uint8_t en_base_rotate[2] = {36, 39};

inline constexpr uint8_t us_base_expand[2] = {32, 34}; // {Trig, Echo}
inline constexpr uint8_t us_base_lift[2] = {33, 35};   // {Trig, Echo}
inline constexpr uint8_t us_sort_slide[2] = {27, 12};  // {Trig, Echo}
} // namespace PINs
