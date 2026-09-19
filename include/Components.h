#pragma once

#include "PCA9685.h"
extern PCA9685 pwmPCA9685;

#include "ESP32Stepper.h"
#include "PCAMotor.h"
#include "PCAServo.h"
#include "PID.h"
#include "UltraSonic.h"
#include <ESP32Encoder.h>

#include "GainConfig.h"
#include "PinConfig.h"

// くにくのさくではある(ほんとはムーブコンストラクタと右辺値参照を使って実体を集約？したい)
struct BaseRotate {
  BaseRotate() : dcMotor(pwmPCA9685, Chanels::dc_base_rotate, GAINs::speed_max_base_rotate),
                 encoder(),
                 pid(GAINs::pid_base_rotate.all, CONFIGs::integral_limit_base_rotate) {}
  PCAMotor dcMotor;
  ESP32Encoder encoder;
  const uint8_t (&enPin)[2] = PINs::en_base_rotate;
  PID pid;
};

struct BaseExpand {
  BaseExpand() : dcMotor(pwmPCA9685, Chanels::dc_base_expand, GAINs::speed_max_base_expand),
                 ultrasonic(PINs::us_base_expand),
                 pid(GAINs::pid_base_expand.all, CONFIGs::integral_limit_base_expand) {}
  PCAMotor dcMotor;
  HCSR04 ultrasonic;
  PID pid;
};

struct BaseLift {
  BaseLift() : dcMotor(pwmPCA9685, Chanels::dc_base_lift, GAINs::speed_max_base_lift),
               ultrasonic(PINs::us_base_lift),
               pid(GAINs::pid_base_lift.all, CONFIGs::integral_limit_base_lift) {}
  PCAMotor dcMotor;
  HCSR04 ultrasonic;
  PID pid;
};

struct Hand {
  PCAServo svLeft, svMiddle, svRight;
  Stepper stRotate, stExpand;
  Hand() : svLeft(pwmPCA9685, Chanels::sv_hand_catchs[0]),
           svMiddle(pwmPCA9685, Chanels::sv_hand_catchs[1]),
           svRight(pwmPCA9685, Chanels::sv_hand_catchs[2]),
           stRotate(PINs::st_hand_rotate, CONFIGs::gear_hand_rotate),
           stExpand(PINs::st_hand_expand, CONFIGs::gear_hand_expand) {}
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
  SortSlide() : dcMotor(pwmPCA9685, Chanels::dc_sort_slide, GAINs::speed_max_sort_slide),
                ultrasonic(PINs::us_sort_slide),
                pid(GAINs::pid_sort_slide.all, CONFIGs::integral_limit_sort_slide) {}
};

struct SortGate {
  PCAServo svLeft, svRight;
  SortGate() : svLeft(pwmPCA9685, Chanels::sv_sort_gates[0]),
               svRight(pwmPCA9685, Chanels::sv_sort_gates[1]) {}
  void begin() {
    svLeft.begin();
    svRight.begin();
  }
};
