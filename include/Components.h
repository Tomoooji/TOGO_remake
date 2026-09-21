#pragma once

#include <PCA9685.h>
extern PCA9685 pwmPCA9685;

#include <ESP32Stepper.h>
#include <PCAMotor.h>
#include <PCAServo.h>
#include <PID.h>
#include <UltraSonic.h>
#include <ESP32Encoder.h>

#include "GainConfig.h"
#include "PinConfig.h"

// くにくのさくではある(ほんとはムーブコンストラクタと右辺値参照を使って実体を集約？したい)
struct BaseRotate {
  BaseRotate() : dcMotor(pwmPCA9685, Channels::dc_base_rotate, Gains::speed_max_base_rotate),
                 encoder(),
                 pid(Gains::pid_base_rotate.all, Configs::integral_limit_base_rotate) {}
  PCAMotor dcMotor;
  ESP32Encoder encoder;
  const uint8_t (&enPin)[2] = Pins::en_base_rotate;
  PID pid;
};

struct BaseExpand {
  BaseExpand() : dcMotor(pwmPCA9685, Channels::dc_base_expand, Gains::speed_max_base_expand),
                 ultrasonic(Pins::us_base_expand),
                 pid(Gains::pid_base_expand.all, Configs::integral_limit_base_expand) {}
  PCAMotor dcMotor;
  HCSR04 ultrasonic;
  PID pid;
};

struct BaseLift {
  BaseLift() : dcMotor(pwmPCA9685, Channels::dc_base_lift, Gains::speed_max_base_lift),
               ultrasonic(Pins::us_base_lift),
               pid(Gains::pid_base_lift.all, Configs::integral_limit_base_lift) {}
  PCAMotor dcMotor;
  HCSR04 ultrasonic;
  PID pid;
};

struct Hand {
  PCAServo svLeft, svMiddle, svRight;
  Stepper stRotate, stExpand;
  Hand() : svLeft(pwmPCA9685, Channels::sv_hand_catchs[0]),
           svMiddle(pwmPCA9685, Channels::sv_hand_catchs[1]),
           svRight(pwmPCA9685, Channels::sv_hand_catchs[2]),
           stRotate(Pins::st_hand_rotate, Configs::gear_hand_rotate),
           stExpand(Pins::st_hand_expand, Configs::gear_hand_expand) {}
  void begin() {
    svLeft.begin();
    svMiddle.begin();
    svRight.begin();
    stRotate.begin();
    stExpand.begin();
  }
};

struct SortSlide {
  PCAMotor dcMotor;
  HCSR04 ultrasonic;
  PID pid;
  SortSlide() : dcMotor(pwmPCA9685, Channels::dc_sort_slide, Gains::speed_max_sort_slide),
                ultrasonic(Pins::us_sort_slide),
                pid(Gains::pid_sort_slide.all, Configs::integral_limit_sort_slide) {}
};

struct SortGate {
  PCAServo svLeft, svRight;
  SortGate() : svLeft(pwmPCA9685, Channels::sv_sort_gates[0]),
               svRight(pwmPCA9685, Channels::sv_sort_gates[1]) {}
  void begin() {
    svLeft.begin();
    svRight.begin();
  }
};
