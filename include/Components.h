#pragma once

#include <ESP32Stepper.h>
#include <PCAServo.h>
#include "GainConfig.h"
#include "PinConfig.h"

extern PCA9685 pwmPCA9685;

struct Hand {
  PCAServo svLeft, svMiddle, svRight;
  Stepper stRotate, stExpand;
  Hand() : svLeft(pwmPCA9685, Channels::sv_hand_catchs[0]),
           svMiddle(pwmPCA9685, Channels::sv_hand_catchs[1]),
           svRight(pwmPCA9685, Channels::sv_hand_catchs[2]),
           stRotate(Pins::st_hand_rotate, Configs::gear_hand_rotate),
           stExpand(Pins::st_hand_expand, Configs::gear_hand_expand) {}
};

struct SortGate {
  PCAServo svLeft, svRight;
  SortGate() : svLeft(pwmPCA9685, Channels::sv_sort_gates[0]),
               svRight(pwmPCA9685, Channels::sv_sort_gates[1]) {}
};
