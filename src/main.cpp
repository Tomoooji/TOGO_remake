#include <Arduino.h>

#include "Components.h"
using BaseRotate::BaseRotateUnit;
using BaseExpand::BaseExpandUnit;
using BaseLift::BaseLiftUnit;
using SortSlide::SortSlideUnit;

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