// add handler for when one motor doesn't move

void startMove() {
  stepCountRot = 0;
  stepCountLin = 0;
  moveRot = true;
  moveLin = true;
  moveStarted = true;
}

void buildCurrMove2(float targRot, float targLin, int cmrr, int cmrl) {
  stepsRot = nextStepsRot;
  stepsLin = nextStepsLin;
  setCmrRot(nextPrescalarRot,cmrr);
  setCmrLin(nextPrescalarLin,cmrl);
  setDirections(targRot,targLin,currRot,currLin);

  //printCurr();

  currRot = targRot; //nextActPos(targRot,currRot,stepsRot,distPerStepRot);
  currLin = targLin; //nextActPos(targLin,currLin,stepsLin,distPerStepLin);
}

void buildCurrMove(float targRot, float targLin) {
  stepsRot = nextStepsRot;
  stepsLin = nextStepsLin;
  setCmrRot(nextPrescalarRot,nextCmrRot);
  setCmrLin(nextPrescalarLin,nextCmrLin);
  setDirections(targRot,targLin,currRot,currLin);
  
  //printCurr();
  
  currRot = targRot; //nextActPos(targRot,currRot,stepsRot,distPerStepRot);
  currLin = targLin; //nextActPos(targLin,currLin,stepsLin,distPerStepLin);
}

void buildNextMove(float targRot, float targLin, float velRot, float velLin) {
  nextStepsRot = nextNumSteps(targRot,currRot,stepsPerDeg);
  nextStepsLin = nextNumSteps(targLin,currLin,stepsPerMM);
  long nextMoveTime = calcMoveTime(targRot,targLin,currRot,currLin,velRot,velLin);
  long nextUsRot = round(abs((nextMoveTime / nextStepsRot) / 2));
  long nextUsLin = round(abs((nextMoveTime / nextStepsLin) / 2));
  nextPrescalarRot = calcPrescalar(nextUsRot);
  nextPrescalarLin = calcPrescalar(nextUsLin);
  nextCmrRot = calcCmr(nextUsRot,nextPrescalarRot);
  nextCmrLin = calcCmr(nextUsLin,nextPrescalarLin);

  //printNext(nextMoveTime,nextUsRot,nextUsLin);
}

long nextNumSteps(float targ, float curr, long stepsPer) {
  float delta = targ - curr;
  long nextSteps  = round(abs(delta) * stepsPer);
  return nextSteps;
}

float nextActPos(float targ, float curr, long numSteps, float distPerStep) {
  float delta = targ - curr;
  float deltAct = numSteps * distPerStep;
  float nextAct = curr + (deltAct * sgn(delta));
  return nextAct;
}

void setDirections(float targRot, float targLin, float currRot, float currLin) {
  // ??? add condition for shortest distance move
  float deltRot = targRot - currRot;
  float deltLin = targLin - currLin;
  
  // Change direction pin output based on sign of position delta
  if (deltRot>0) {digitalWrite(dirPin1, LOW);}  // counter-clockwise
  else {          digitalWrite(dirPin1, HIGH);} // clockwise

  if (deltLin>0) {digitalWrite(dirPin2, HIGH);} // towards motor
  else {          digitalWrite(dirPin2, LOW);}  // away motor
}

// handle for when linear delta is 0
long calcMoveTime(float targRot, float targLin, float currRot, float currLin, float velRot, float velLin){
  float deltRot = targRot - currRot;
  float deltLin = targLin - currLin;
  long moveTimeUs = round((abs(deltLin)/velLin) * microS);
  return moveTimeUs;
}

long calcPrescalar(long usStep) {
  float stepHz = microS / usStep;
  long prescalars[5] = {1,8,64,256,1024};
  long prescalar;

  for (int i=0; i<5; i++) {
    long cmr = round(clockHz/(prescalars[i]*stepHz))-1;
    if (cmr < 240) {
      prescalar = prescalars[i];
      break;
    }
  }
  return prescalar;
}

long calcCmr(float usStep, float prescalar) {
  float stepHz = microS / usStep;
  long cmr = round(clockHz/(prescalar*stepHz))-1;
  return cmr;
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
  Serial.println(" ");
}

void printNext(long moveTime,long nusRot,long nusLin) {
  Serial.println("Next parameters:");
  Serial.println("stepsRot: " + String(nextStepsRot));
  Serial.println("stepsLin: " + String(nextStepsLin));
  Serial.println("moveTime: " + String(moveTime));
  Serial.println("usRot: " + String(nusRot));
  Serial.println("usLin: " + String(nusLin));
  Serial.println("prescalarRot: " + String(nextPrescalarRot));
  Serial.println("prescalarLin: " + String(nextPrescalarLin));
  //Serial.println("cmrRot: " + String(nextCmrRot));
  //Serial.println("cmrLin: " + String(nextCmrLin));
  Serial.println("currRot: " + String(currRot));
  Serial.println("currLin: " + String(currLin));
  Serial.println(" ");
}
