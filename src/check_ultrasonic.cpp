#include <Arduino.h>
#include <PinConfig.h>
#include "UltraSonic.h"

HCSR04 usSensor;

void setup() {
  Serial.begin(115200);
  usSensor.begin(PINs::us_base_expand);
  while(!Serial);
  Serial.println("Ultrasonic Sensor Test");
}

void loop() {
  //usSensor.update();
  Serial.print("Distance: ");
  Serial.println(usSensor.getDistance());
  delay(500);
}