// add handler for when one motor doesn't move
/***
void startMove() {
  stepCountRot = 0;
  stepCountLin = 0;
  moveRot = true;
  moveLin = true;
  moveStartedRot = false;
  moveStartedLin = false;
}

void buildCurrMove(float targRot, float targLin) {
  stepsRot = nextStepsRot;
  stepsLin = nextStepsLin;
  //Serial.println(String(nextPrescalarRot) + ", " + String(nextCmrRot));
  setCmrRot(nextPrescalarRot,nextCmrRot);
  setCmrLin(nextPrescalarLin,nextCmrLin);
  setDirections(targRot,targLin,currRot,currLin);
  
  //printCurr();
  
  currRot = nextRotAct; //targRot; //nextActPos(targRot,currRot,stepsRot,distPerStepRot);
  currLin = nextLinAct; //targLin; //nextActPos(targLin,currLin,stepsLin,distPerStepLin);
}

void buildNextMove(float targRot, float targLin, float velRot, float velLin) {
  nextStepsRot = nextNumSteps(targRot,currRot,stepsPerDeg);
  nextStepsLin = nextNumSteps(targLin,currLin,stepsPerMM);
  if (nextStepsRot<30 || nextStepsLin<30) {
    zeroDist = true;
  } else {zeroDist = false;}
  long nextMoveTime = calcMoveTime(targRot,targLin,currRot,currLin,velRot,velLin);
  if (nextMoveTime < 200000) {
    nextMoveTime = 200000;
  }
  long nextUsRot = round(abs((nextMoveTime / nextStepsRot) / 2));
  long nextUsLin = round(abs((nextMoveTime / nextStepsLin) / 2));
  nextPrescalarRot = calcPrescalar(nextUsRot);
  nextPrescalarLin = calcPrescalar(nextUsLin);
  nextCmrRot = calcCmr(nextUsRot,nextPrescalarRot);
  nextCmrLin = calcCmr(nextUsLin,nextPrescalarLin);
  nextRotAct = nextActPos(targRot,currRot,nextStepsRot,distPerStepRot);
  nextLinAct = nextActPos(targLin,currLin,nextStepsLin,distPerStepLin);

  //printNextLine(nextMoveTime,nextUsRot,nextUsLin,targRot,targLin);
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
  if (velLin<1) {
    velLin = 1;
  }
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

void printNext(long moveTime,long nusRot,long nusLin,float targR,float targL) {
  Serial.println("Next parameters:");
  Serial.println("stepsRot: " + String(nextStepsRot));
  Serial.println("stepsLin: " + String(nextStepsLin));
  Serial.println("moveTime: " + String(moveTime));
  Serial.println("usRot: " + String(nusRot));
  Serial.println("usLin: " + String(nusLin));
  Serial.println("prescalarRot: " + String(nextPrescalarRot));
  Serial.println("prescalarLin: " + String(nextPrescalarLin));
  Serial.println("cmrRot: " + String(nextCmrRot));
  Serial.println("cmrLin: " + String(nextCmrLin));
  Serial.println("currRot: " + String(currRot));
  Serial.println("currLin: " + String(currLin));
  Serial.println("targRot: " + String(targR));
  Serial.println("targLin: " + String(targL));
  Serial.println("nextRot: " + String(nextRotAct));
  Serial.println("nextLin: " + String(nextLinAct));
  Serial.println(" ");
}

void printNextLine(long moveTime,long nusRot,long nusLin,float targR,float targL) {
  Serial.print(String(nextStepsRot)+",");
  Serial.print(String(nextStepsLin)+",");
  Serial.print(String(moveTime)+",");
  Serial.print(String(nusRot)+",");
  Serial.print(String(nusLin)+",");
  Serial.print(String(nextPrescalarRot)+",");
  Serial.print(String(nextPrescalarLin)+",");
  Serial.print(String(nextCmrRot)+",");
  Serial.print(String(nextCmrLin)+",");
  Serial.print(String(currRot)+",");
  Serial.print(String(currLin)+",");
  Serial.print(String(targR)+",");
  Serial.print(String(targL)+",");
  Serial.print(String(nextRotAct)+",");
  Serial.println(String(nextLinAct));
}

**/
