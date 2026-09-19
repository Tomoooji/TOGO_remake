#pragma once
#include <Arduino.h>

namespace GAINs {
// PID gains
union PID_GAIN {
  struct { float P, I, D; }; float all[3];
};
inline constexpr PID_GAIN pid_base_rotate = {0.5, 0.0, 0.0};
inline constexpr PID_GAIN pid_base_expand = {0.5, 0.0, 0.0};
inline constexpr PID_GAIN pid_base_lift = {0.5, 0.0, 0.0};
inline constexpr PID_GAIN pid_sort_slide = {1.5, 0.0, 0.0};

// Position configuration
union BASE_POSITION {
  struct {
    float Initial, Min, Max;
    float RightNear, RightFar;
    float MidNear, MidFar;
    float LeftNear, LeftFar;
    float Red1, Red2, Red3, Red4;
    float Blue1, Blue2, Blue3, Blue4;
  };
  float all[15];
};
inline const BASE_POSITION pos_base_rotate = {
  0.0,  -90.0, 90.0,  45.0,  90.0,
  0.0,  45.0,  -45.0, -90.0, 30.0,
  60.0, 90.0,  120.0, -30.0, -60.0
};
inline const BASE_POSITION pos_base_expand = {
  0.0,  0.0,  180.0, 90.0,   180.0,
  0.0,  90.0, -90.0, -180.0, 30.0,
  60.0, 90.0, 120.0, -30.0,  -60.0
};

inline constexpr union BASE_HEIGHT {
  struct { float Catch1, Catch2, Shoot; }; float all[3];
} pos_base_lift = {0.0, 5.0, 10.0};

inline constexpr union SORT_POSITION {
  struct { float Red1, Red2, Red3, Red4, Blue1, Blue2, Blue3, Blue4; }; float all[8];
} pos_sort_slide = {0.0, 5.0, 10.0, 15.0, 0.0, 5.0, 10.0, 15.0};

inline constexpr union HAND_EXPAND_POSITION {
  struct { float Catch, Shoot; }; float all[2];
} pos_hand_expand = {0.0, 5.0};

inline constexpr union HAND_CATCH_ANGLE {
  struct { float Open, Close, Grab; }; float all[3];
} pos_hand_catch = {0.0, 5.0, 10.0};

// speed limits
inline constexpr float speed_max_base_rotate = 100.0;
inline constexpr float speed_max_base_expand = 100.0;
inline constexpr float speed_max_base_lift = 100.0;
inline constexpr float speed_max_sort_slide = 100.0;
} // namespace GAINs

namespace CONFIGs {
// sensor offsets
inline constexpr float sensor_offset_base_expand = 0.0;
inline constexpr float sensor_offset_base_lift = 0.0;
inline constexpr float sensor_offset_sort_slide = 0.0;
// gear ratios
inline constexpr float pulse2ang_base_rotate = 1024;
inline constexpr float gear_hand_rotate = 1.0;
inline constexpr float gear_hand_expand = 1.0;
// integral limits
inline constexpr float integral_limit_base_rotate = 1000.0;
inline constexpr float integral_limit_base_expand = 1000.0;
inline constexpr float integral_limit_base_lift = 1000.0;
inline constexpr float integral_limit_sort_slide = 1000.0;

} // namespace CONFIGs