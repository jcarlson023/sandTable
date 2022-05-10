
void buildCurrMove(float targRot, float targLin) {
  stepsRot = abs(nextStepsRot);
  stepsLin = abs(nextStepsLin);
  
  if (abs(nextStepsRot)>0){
    stepsRot = abs(nextStepsRot);
    prescalarRot = nextPrescalarRot;
    cmrRot = nextCmrRot;
    cmrRotAcc = nextCmrRotAcc;
    currRot = nextRotAct;
  }
  
  if (abs(nextStepsLin)>0){
    stepsLin = abs(nextStepsLin);
    prescalarLin = nextPrescalarLin;
    cmrLin = nextCmrLin;
    cmrLinAcc = nextCmrLinAcc;
    currLin = nextLinAct;
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
  if (nextStepsRot>0) {digitalWrite(rotDirPin, LOW);}  // counter-clockwise
  else {          digitalWrite(rotDirPin, HIGH);} // clockwise

  if (nextStepsLin>0) {digitalWrite(linDirPin, HIGH);} // towards motor
  else {          digitalWrite(linDirPin, LOW);}  // away motor
}

static inline int8_t sgn(float val) {
  if (val < 0.0) return -1;
  return 1;
}
