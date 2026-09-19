#include "Components.h"

Hand HandUnit;

int makeAngleZigzag(){
  static int angle = 0;
  static int direction = 1; // 1 for increasing, -1 for decreasing
  direction = (angle >= 180) ? -1 : (angle <= 0) ? 1 : direction;
  return angle += 10 * direction;
}

int makeExpandStep(){
  static unsigned long timestamp = millis();
  static int state = 0;
  if (millis() - timestamp > 1000) { // 1 second
    timestamp = millis();
    state = state == 0 ? 1 : 0; // Toggle state between 0 and 1
  }
  return state; // Return the current state
}

void setup() {
  HandUnit.begin();
}

void loop() {
  // Example usage of the HandUnit
  HandUnit.svLeft.write(HandUnit.svLeft.setAngle(GAINs::pos_hand_catch.Open));
  HandUnit.svMiddle.write(HandUnit.svMiddle.setAngle(GAINs::pos_hand_catch.Close));
  HandUnit.svRight.write(HandUnit.svRight.setAngle(GAINs::pos_hand_catch.Grab));

  HandUnit.stRotate.moveTo(makeAngleZigzag(), 1); // Move to a new angle every loop iteration (increments by 10 degrees, resets after 180 degrees)
  
  int state = makeExpandStep();
  HandUnit.stExpand.setTargetAngle(GAINs::pos_hand_expand.all[state]); // Toggle between Catch and Shoot positions
  HandUnit.stExpand.moveStep();
  delay(1); // Wait for a second before repeating
}