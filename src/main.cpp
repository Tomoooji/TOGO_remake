#include <Wire.h>
#include <PCA9685_tmj.h>
PCA9685 pwmPCA9685(0x40);

#include "PinConfig.h"
#include "GainConfig.h"

#include "Components.h"
#include "LinearActuator.h"
#include "RotaryActuator.h"


RotaryActuator BaseRotateUnit{
  PCAMotor(pwmPCA9685, Channels::dc_base_rotate),
  ESP32Encoder(),
  PID(Gains::pid_base_rotate, Gains::default_integral_limit),
  Pins::en_base_rotate,
  Configs::pulse2ang_base_rotate
};

LinearActuator BaseExpandUnit{
  PCAMotor(pwmPCA9685, Channels::dc_base_expand),
  HCSR04(Pins::us_base_expand, 10, 200, 1000),
  PID(Gains::pid_base_expand, Gains::default_integral_limit),
  Configs::sensor_offset_base_expand
};

LinearActuator BaseLiftUnit{
  PCAMotor(pwmPCA9685, Channels::dc_base_lift),
  HCSR04(Pins::us_base_lift, 10, 200, 1000),
  PID(Gains::pid_base_lift, Gains::default_integral_limit),
  Configs::sensor_offset_base_lift
};

Hand HandUnit;

LinearActuator SortSlideUnit{
  PCAMotor(pwmPCA9685, Channels::dc_sort_slide),
  HCSR04(Pins::us_sort_slide, 10, 200, 1000),
  PID(Gains::pid_sort_slide, Gains::default_integral_limit),
  Configs::sensor_offset_sort_slide
};

SortGate SortGateUnit;

void setup() {
  pwmPCA9685.begin();
  //pwmPCA9685.setPWMFreq(1000);
  pwmPCA9685.setPWMFreq(50);// サーボも動かすから50Hzにしないといけない
  Wire.setClock(400000);

  BaseRotateUnit.begin();
  BaseExpandUnit.begin();
  BaseLiftUnit.begin();

  HandUnit.stExpand.begin();
  HandUnit.stRotate.begin();

  SortSlideUnit.begin();
}

void loop() {}