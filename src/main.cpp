#include <Wire.h>
#include <PCA9685.h>
PCA9685 pwmPCA9685(0x40);

#include "Components.h"
#include "LinearActuator.h"
#include "RotaryActuator.h"

BaseRotate BaseRotateComponent;
RotaryActuator BaseRotateUnit(
  BaseRotateComponent.dcMotor,
  BaseRotateComponent.encoder,
  BaseRotateComponent.pid,
  BaseRotateComponent.enPin,
  CONFIGs::pulse2ang_base_rotate
);

BaseExpand BaseExpandComponent;
LinearActuator BaseExpandUnit(
  BaseExpandComponent.dcMotor,
  BaseExpandComponent.ultrasonic,
  BaseExpandComponent.pid,
  CONFIGs::sensor_offset_base_expand
);

BaseLift BaseLiftComponent;
LinearActuator BaseLiftUnit(
  BaseLiftComponent.dcMotor,
  BaseLiftComponent.ultrasonic,
  BaseLiftComponent.pid,
  CONFIGs::sensor_offset_base_lift
);

Hand HandUnit;

SortSlide SortSlideComponent;
LinearActuator SortSlideUnit(
  SortSlideComponent.dcMotor,
  SortSlideComponent.ultrasonic,
  SortSlideComponent.pid,
  CONFIGs::sensor_offset_sort_slide
);

SortGate SortGateUnit;

void setup() {
  pwmPCA9685.begin();
  //pwmPCA9685.setPWMFreq(1000);
  pwmPCA9685.setPWMFreq(50);// サーボも動かすから50Hzにしないといけない
  Wire.setClock(400000);

  BaseRotateUnit.begin();
  BaseExpandUnit.begin();
  BaseLiftUnit.begin();

  HandUnit.begin();

  SortSlideUnit.begin();
  SortGateUnit.begin();
}

void loop() {}