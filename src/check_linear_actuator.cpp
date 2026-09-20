#include <Wire.h>
#include <PCA9685.h>
PCA9685 pwmPCA9685(0x40);

#include "Components.h"
#include "LinearActuator.h"

BaseExpand BaseExpandComponent;
LinearActuator BaseExpandUnit(
  BaseExpandComponent.dcMotor,
  BaseExpandComponent.ultrasonic,
  BaseExpandComponent.pid,
  CONFIGs::sensor_offset_base_expand
);

int makeDistanceStep(){
  static int distance = 0;
  static int direction = 1; // 1 for increasing, -1 for decreasing
  static unsigned long timestamp = millis();
  if(millis() - timestamp > 1000){
    timestamp = millis();
    distance += 5 * direction;
    if(distance > 20) {
      direction = -1;
      distance = 20;
    } else if(distance < 0) {
      direction = 1;
      distance = 0;
    }
  }
  return distance;
}

void setup() {
  Serial.begin(115200);
  
  pwmPCA9685.begin();
  //pwmPCA9685.setPWMFreq(1000);
  pwmPCA9685.setPWMFreq(50);// サーボも動かすから50Hzにしないといけない
  Wire.setClock(400000);

  BaseExpandUnit.begin();
  BaseExpandUnit.setTargetDistance(0); // Set initial target distance to 0

  while(!Serial);
  Serial.println("Linear Actuator Test");
}

void loop() {
  BaseExpandUnit.setTargetDistance(makeDistanceStep()); // Set target distance to a new value every second (increments by 10, resets after 100)

  BaseExpandUnit.update(); // Update the actuator to move towards the target distance

  Serial.print("Current Distance: ");
  Serial.println(BaseExpandUnit.getCurrentDistance()); // Print the current distance from the ultrasonic sensor

  Serial.print("Target Distance: ");
  Serial.println(BaseExpandUnit.getTargetDistance()); // Print the target distance

  Serial.println();

  delay(1); // Delay for 1ms before the next update
}