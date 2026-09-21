#include <Wire.h>
#include <PCA9685.h>
PCA9685 pwmPCA9685(0x40);

#include <Components.h>
#include "RotaryActuator.h"

BaseRotate BaseRotateComponent;
RotaryActuator BaseRotateUnit(
  BaseRotateComponent.dcMotor, 
  BaseRotateComponent.encoder, 
  BaseRotateComponent.pid,
  BaseRotateComponent.enPin,
  Configs::pulse2ang_base_rotate
);

int makeAngleStep(){
  static int angle = 0;
  static int direction = 1; // 1 for increasing, -1 for decreasing
  static unsigned long timestamp = millis();
  if(millis() - timestamp > 1000){
    timestamp = millis();
    angle += 10 * direction;
    if(angle > 180){
      direction = -1;
      angle = 180;
    } else if(angle < 0){
      direction = 1;
      angle = 0;
    }
  }
  return angle;
}

void setup() {
  Serial.begin(115200);
  
  pwmPCA9685.begin();
  //pwmPCA9685.setPWMFreq(1000);
  pwmPCA9685.setPWMFreq(50);// サーボも動かすから50Hzにしないといけない
  Wire.setClock(400000);

  BaseRotateUnit.begin();
  BaseRotateUnit.setTargetAngle(0); // Set initial target angle to 0 degrees

  while(!Serial);
  Serial.println("Rotary Actuator Test");
}

void loop() {
  BaseRotateUnit.setTargetAngle(makeAngleStep()); // Set target angle to a new value every second (increments by 10 degrees, resets after 180 degrees)
  BaseRotateUnit.update(); // Update the actuator to move towards the target angle

  Serial.print("Current Angle: ");
  Serial.println(BaseRotateUnit.getCurrentAngle()); // Print the current encoder count (angle)

  Serial.print("Target Angle: ");
  Serial.println(BaseRotateUnit.getTargetAngle()); // Print the target angle

  Serial.println();
  
  delay(1); // Delay for 1ms before the next update
}