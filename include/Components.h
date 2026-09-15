#include <Arduino.h>

// 何でもかんでもinlineするとちょっとした変更時の再コンパイルが遅くなるという話ありけり(一旦無視)

#include "PCA9685.h"
inline PCA9685 pwmPCA9685(0x40);

#include <ESP32Servo.h>
#include <ESP32Encoder.h>
#include <UltraSonic.h>
//#include <ESP32Stepper.h>
#include <PCAMotor.h>
#include <PID.h>

#include "RotaryActuator.h"
#include "LinearActuator.h"

#include "PinConfig.h"
#include "GainConfig.h"

namespace BaseRotate{
  inline PCAMotor dcMotor(pwmPCA9685);
  inline ESP32Encoder encoder;
  inline PID pid(OutGains::pid_base_rotate);

  inline RotaryActuator BaseRotateUnit(dcMotor,encoder,pid);
}

namespace BaseExpand{
  inline PCAMotor dcMotor(pwmPCA9685);
  inline HCSR04 ultrasonic;
  inline PID pid(OutGains::pid_base_expand);

  inline LinearActuator BaseExpandUnit(dcMotor,ultrasonic,pid);
}

namespace BaseLift{
  inline PCAMotor dcMotor(pwmPCA9685);
  inline HCSR04 ultrasonic;
  inline PID pid(OutGains::pid_base_lift);

  inline LinearActuator BaseLiftUnit(dcMotor,ultrasonic,pid);
}

namespace Hand{
  inline Servo svCatch1, svCatch2, svCatch3;
  inline Stepper stRotate, stExpand;
  inline void attach(const uint8_t svCatchPin[], const uint8_t stRotatePin[], const uint8_t stExpandPin[]){
    svCatch1.attach(svCatchPin[0]);
    svCatch2.attach(svCatchPin[1]);
    svCatch3.attach(svCatchPin[2]);
    stRotate.attach(stRotatePin);
    stExpand.attach(stExpandPin);
  }
}

namespace SortSlide{
  inline PCAMotor dcMotor(pwmPCA9685);
  inline HCSR04 ultrasonic;
  inline PID pid(OutGains::pid_sort_slide);

  inline LinearActuator SortSlideUnit(dcMotor,ultrasonic,pid);
}

namespace SortGate{
  inline Servo svLeft, svRight;
  inline void attach(const uint8_t svGatePin[]){
    svLeft.attach(svGatePin[0]);
    svRight.attach(svGatePin[1]);
  }
}
