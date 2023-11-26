
void homingRoutine() {
  if (homedFlag){ // If homed, stop moving and set the home position
    setHome();
  }
  if (!isHomed && !homingStarted && !moveLin && !moveRot) { // begin a relative move away from the limit switch 
    moveRelative(-0.01,0,0.03,0.03);
    homingStarted = true;
  }
  if (!isHomed && homingStarted && !moveLin && !moveRot) { // begin finding the limit switch
    attachInterrupt(linLimitPin, linHomed, HIGH); // attach the limit switch pin as an interrupt trigger, using the lin homed interrupt function
    moveRelative(1,0,0.03,0.03); // move towards the limit switch
  }
  if (isHomed && homingStarted) { // if the home position is hit, remove the limit interrupt and finish homing
    detachInterrupt(linLimitPin);
    homingStarted = false;
  }
}

void setHome() {
  currLin = 142;               // set linear axis home position 
  currRot = 0;                 // set rotational axis home position
  moveLin = false;             // stop moving the linear axis
  moveRot = false;             // stop moving the rotational axis
  isHomed = true;              // I am homed
  Serial.println("homed");
}
