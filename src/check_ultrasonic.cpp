#include <UltraSonic.h>
#include "PinConfig.h"

HCSR04 usSensor(PINs::us_base_expand, 10, 200, 1000);

void setup() {
  Serial.begin(115200);
  usSensor.begin();
  while(!Serial);
  Serial.println("Ultrasonic Sensor Test");
}

void loop() {
  //usSensor.update();
  Serial.print("Distance: ");
  Serial.println(usSensor.getDistance());
  delay(500);
}