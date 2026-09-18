#pragma once

#include "PCA9685.h"
extern PCA9685 pwmPCA9685;

#include <ESP32Encoder.h>
#include "UltraSonic.h"
#include "ESP32Stepper.h"
#include "PCAMotor.h"
#include "PCAServo.h"
#include "PID.h"

#include "RotaryActuator.h"
#include "LinearActuator.h"

#include "PinConfig.h"
#include "GainConfig.h"

// くにくのさくではある(ほんとはムーブコンストラクタと右辺値参照を使って実体を集約？したい)
struct BaseRotate{
  BaseRotate():dcMotor(pwmPCA9685), encoder(), pid(GAINs::pid_base_rotate){}
  PCAMotor dcMotor;
  ESP32Encoder encoder;
  PID pid;
};

struct BaseExpand{
  BaseExpand():dcMotor(pwmPCA9685), ultrasonic(), pid(GAINs::pid_base_expand){}
  PCAMotor dcMotor;
  HCSR04 ultrasonic;
  PID pid;
  
};

struct BaseLift{
  BaseLift():dcMotor(pwmPCA9685), ultrasonic(), pid(GAINs::pid_base_lift){}
  PCAMotor dcMotor;
  HCSR04 ultrasonic;
  PID pid;
};

struct Hand{
  PCAServo svCatch1, svCatch2, svCatch3;
  Stepper stRotate, stExpand;
  void attach(const uint8_t svCatchPin[], const uint8_t stRotatePin[], const uint8_t stExpandPin[]){
    svCatch1.attach(&svCatchPin[0]);
    svCatch2.attach(&svCatchPin[1]);
    svCatch3.attach(&svCatchPin[2]);
    stRotate.attach(stRotatePin);
    stExpand.attach(stExpandPin);
  }
};

struct SortSlide{
  SortSlide():dcMotor(pwmPCA9685), ultrasonic(), pid(GAINs::pid_sort_slide){}
  PCAMotor dcMotor;
  HCSR04 ultrasonic;
  PID pid;
};

struct SortGate{
  PCAServo svLeft, svRight;
  void attach(const uint8_t svGatePin[]){
    svLeft.attach(&svGatePin[0]);
    svRight.attach(&svGatePin[1]);
  }
};
