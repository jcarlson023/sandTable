void runHoming() {
  attachInterrupt(linLimitPin, linHomed, FALLING);
  moveRelative(300,0,10,10);
  while (moveRot && moveLin){
    Serial.println("");
  }
  isHomed = true;
}
