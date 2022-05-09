// add handler for when one motor doesn't move

void startMove() {
  stepCountRot = 0;
  stepCountLin = 0;
  if (abs(nextStepsRot)>0){
    moveRot = true;
    moveStartedRot = false;
  }
  if (abs(nextStepsLin)>0){
    moveLin = true;
    moveStartedLin = false;
  }
  
}

void buildCurrMove(float targRot, float targLin) {

  if (abs(nextStepsRot)>0){
    stepsRot = abs(nextStepsRot);
    prescalarRot = nextPrescalarRot;
    cmrRot = nextCmrRot;
    setCmrRot(nextPrescalarRot,nextCmrRot);
    cmrRotAcc = nextCmrRotAcc;
    currRot = nextActPos(currRot,nextStepsRot,stepsPerDeg);
  }
  
  if (abs(nextStepsLin)>0){
    stepsLin = abs(nextStepsLin);
    prescalarLin = nextPrescalarLin;
    cmrLin = nextCmrLin;
    setCmrLin(nextPrescalarLin,nextCmrLin);
    cmrLinAcc = nextCmrLinAcc;
    currLin = nextActPos(currLin,nextStepsLin,stepsPerMM);
  }
  
  setDirections(nextStepsRot,nextStepsLin);
  //printCurr();
  
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
