#include <Arduino.h>
#include <Wire.h>
#include "PCA9685.h"
PCA9685 pwmPCA9685(0x40);

#include "Components.h"

BaseRotate BaseRotateComponent;
RotaryActuator BaseRotateUnit(
  BaseRotateComponent.dcMotor, 
  BaseRotateComponent.encoder, 
  BaseRotateComponent.pid
);

BaseExpand BaseExpandComponent;
LinearActuator BaseExpandUnit(
  BaseExpandComponent.dcMotor,
  BaseExpandComponent.ultrasonic,
  BaseExpandComponent.pid
);

BaseLift BaseLiftComponent;
LinearActuator BaseLiftUnit(
  BaseLiftComponent.dcMotor,
  BaseLiftComponent.ultrasonic,
  BaseLiftComponent.pid
);

Hand HandUnit;

SortSlide SortSlideComponent;
LinearActuator SortSlideUnit(
  SortSlideComponent.dcMotor,
  SortSlideComponent.ultrasonic,
  SortSlideComponent.pid
);

SortGate SortGateUnit;

void setup(){
  pwmPCA9685.begin();
  pwmPCA9685.setPWMFreq(1000);
  Wire.setClock(400000);
  
  BaseRotateUnit.begin(Chanels::dc_base_rotate,PINs::en_base_rotate);
  BaseExpandUnit.begin(Chanels::dc_base_expand,PINs::us_base_expand);
  BaseLiftUnit.begin(Chanels::dc_base_lift,PINs::us_base_lift);
  
  HandUnit.attach(Chanels::sv_hand_catchs, PINs::st_hand_rotate, PINs::st_hand_expand);
  
  SortSlideUnit.begin(Chanels::dc_sort_slide,PINs::us_sort_slide);
  SortGateUnit.attach(Chanels::sv_sort_gates);
}

void loop(){

}