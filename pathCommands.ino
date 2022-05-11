
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
      fileLength = 599;
      for(int i=0;i<fileLength;i++)
        for(int j=0;j<11;j++)
          path[i][j] = myPath3[i][j];
      currLin = path[0][9];
      currRot = path[0][10];
      break;
    case 2:
      fileLength = 599;
      for(int i=0;i<fileLength;i++)
        for(int j=0;j<11;j++)
          path[i][j] = myPath3[i][j];
      currLin = path[0][9];
      currRot = path[0][10];
      break;
    case 3:
      fileLength = 599;
      for(int i=0;i<fileLength;i++)
        for(int j=0;j<11;j++)
          path[i][j] = myPath3[i][j];
      currLin = path[0][9];
      currRot = path[0][10];
      break;
    case 4:
      fileLength = 599;
      for(int i=0;i<fileLength;i++)
        for(int j=0;j<11;j++)
          path[i][j] = myPath3[i][j];
      currLin = path[0][9];
      currRot = path[0][10];
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
    choosePath(4);
    moveTimeNext = 0;
    lTargNext = 0;
    rTargNext = 0;
    lVelNext = 0;
    rVelNext = 0;
  }
  
  if ((i > 0) && !moveRot && !moveLin) {
    buildCurrMove(rTargNext,lTargNext);
    if (!zeroDist) {
      startMove();
    }
    builtNextMove = false;
  }

  if (!builtNextMove || zeroDist) {
    String nextTime = String(myPath3[i+1][0]);
    nextStepsLin = myPath3[i+1][1];
    nextStepsRot = myPath3[i+1][2];
    nextPrescalarLin = myPath3[i+1][3];
    nextPrescalarRot = myPath3[i+1][4];
    nextCmrLin = myPath3[i+1][5];
    nextCmrRot = myPath3[i+1][6];
    nextCmrLinAcc = myPath3[i+1][7];
    nextCmrRotAcc = myPath3[i+1][8];
    nextLinAct = myPath3[i+1][9];
    nextRotAct = myPath3[i+1][10];
    builtNextMove = true;
    i++;
  }
  
  if (i==(fileLength-2)) {
    i = -1;
    builtNextMove = false;
  }
}
