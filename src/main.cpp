#include <Arduino.h>

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
  pwmPCA9685.setPWMFreq(50);
  
  BaseRotateUnit.begin(Chanels::dcBaseRotate,PINs::enBaseRotate);
  BaseExpandUnit.begin(Chanels::dcBaseExpand,PINs::usBaseExpand);
  BaseLiftUnit.begin(Chanels::dcBaseLift,PINs::usBaseLift);
  
  Hand::attach( PINs::svHandCatchs, PINs::stHandRotate, PINs::stHandExpand);
  
  SortSlideUnit.begin(Chanels::dcSortSlide,PINs::usSortSlide);
  SortGate::attach(PINs::svSortGates);
}

void loop(){

}