// add handler for when one motor doesn't move

void startMove() {
  stepCountRot = 0;
  stepCountLin = 0;
  moveRot = true;
  moveLin = true;
  moveStartedRot = false;
  moveStartedLin = false;
}

void buildCurrMove(float targRot, float targLin) {
  stepsRot = abs(nextStepsRot);
  stepsLin = abs(nextStepsLin);
  setCmrRot(nextPrescalarRot,nextCmrRot);
  setCmrLin(nextPrescalarLin,nextCmrLin);
  setDirections(nextStepsRot,nextStepsLin);
  
  //printCurr();
  
  currRot = nextActPos(currRot,nextStepsRot,stepsPerDeg);
  currLin = nextActPos(currLin,nextStepsLin,stepsPerMM);
}

float nextActPos(float curr, long numSteps, float distPerStep) {
  float deltAct = numSteps * distPerStep;
  float nextAct = curr + deltAct;
  return nextAct;
}

void setDirections(float nextStepsRot, float nextStepsLin) {
  // Change direction pin output based on sign of position delta
  if (nextStepsRot>0) {digitalWrite(dirPin1, LOW);}  // counter-clockwise
  else {          digitalWrite(dirPin1, HIGH);} // clockwise

  if (nextStepsLin>0) {digitalWrite(dirPin2, HIGH);} // towards motor
  else {          digitalWrite(dirPin2, LOW);}  // away motor
}

static inline int8_t sgn(float val) {
  if (val < 0.0) return -1;
  return 1;
}

void printCurr() {
  Serial.println("Curr parameters:");
  Serial.println("stepsRot: " + String(stepsRot));
  Serial.println("stepsLin: " + String(stepsLin));
  Serial.println("currRot: " + String(currRot));
  Serial.println("currLin: " + String(currLin));
  Serial.println("rot cmr: " + String(nextCmrRot));
  Serial.println("lin cmr: " + String(nextCmrLin));
  Serial.println(" ");
}
