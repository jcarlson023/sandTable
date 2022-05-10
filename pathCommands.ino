
void moveRelative(float lPos, float rPos, float lVel, float rVel){
  currLin = 0;
  currRot = 0;
  stepsRot = round(abs(rPos*stepsPerDeg));
  stepsLin = round(abs(lPos*stepsPerMM));
  prescalarRot = 256;
  prescalarLin = 256;
  cmrRot = 20;
  cmrLin = 50;
  cmrRotAcc = 0;
  cmrLinAcc = 0;
  setDirections(lPos,rPos);
  startMove();
}

void choosePath(int pathNum) {
  switch (pathNum) {
    case 1:
      //fileName = "path.csv";
      fileLength = 267;
      currLin = 0.0;
      currRot = 0.0;
      break;
    case 2:
      //fileName = "spirals2.csv";
      fileLength = 449;
      currLin = 160.0;
      currRot = 0.0;
      break;
    case 3:
      //fileName = "refactor.csv";
      fileLength = 1068;
      currLin = 0;
      currRot = 0.0;
      break;
    default:
      break;
  }
}

void startMove() {
  buildInterrupts();
  stepCountRot = 0;
  stepCountLin = 0;
  if (abs(stepsRot)>0){
    moveRot = true;
    moveStartedRot = false;
  }
  if (abs(stepsLin)>0){
    moveLin = true;
    moveStartedLin = false;
  }
}

void runPattern() {
  if (i==-1) {
    choosePath(3);
    //myFile = SD.open(fileName);
    moveTimeNext = 0;
    lTargNext = 0;
    rTargNext = 0;
    lVelNext = 0;
    rVelNext = 0;
  }
  
  if ((i >= 0) && !moveRot && !moveLin) {
    buildCurrMove(rTargNext,lTargNext);
    if (!zeroDist) {
      startMove();
    }
    builtNextMove = false;
  }

  if (!builtNextMove || zeroDist) {
    String nextTime = String(myPath[i+1][0]);
    nextStepsLin = myPath[i+1][1];
    nextStepsRot = myPath[i+1][2];
    nextPrescalarLin = myPath[i+1][3];
    nextPrescalarRot = myPath[i+1][4];
    nextCmrLin = myPath[i+1][5];
    nextCmrRot = myPath[i+1][6];
    nextCmrLinAcc = myPath[i+1][7];
    nextCmrRotAcc = myPath[i+1][8];
    builtNextMove = true;
    i++;
    //printFileReads();
  }
  
  if (i==(fileLength-2)) {
    //myFile.close();
    i = -1;
    builtNextMove = false;
  }
}

void printFileReads() {
  Serial.print(String(nextStepsLin) + ", ");
  Serial.print(String(nextStepsRot) + ", ");
  Serial.print(String(nextPrescalarLin) + ", ");
  Serial.print(String(nextPrescalarRot) + ", ");
  Serial.print(String(nextCmrLin) + ", ");
  Serial.println(String(nextCmrRot));
}
