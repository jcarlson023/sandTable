
void homingRoutine() {
  if (!isHomed && !homingStarted && !moveLin && !moveRot) {
    attachInterrupt(linLimitPin, linHomed, HIGH);
    moveRelative(-0.01,0,0.03,0.03);
    homingStarted = true;
  }
  if (!isHomed && homingStarted && !moveLin && !moveRot) {
    moveRelative(1,0,0.03,0.03);
  }
  if (isHomed && homingStarted) {
    detachInterrupt(linLimitPin);
    homingStarted = false;
  }
}

void setHome() {
  currLin = 142;
  currRot = 0;
  moveLin = false;
  moveRot = false;
  isHomed = true;
  Serial.println("homed");
}
