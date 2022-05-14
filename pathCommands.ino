void startMove() {
  timerAlarmWrite(rotTimer, currPoint.rotCmr, true);
  timerAlarmWrite(rotTimer, currPoint.linCmr, true);
  setDirections(currPoint.rotSteps,currPoint.linSteps);
  currLin = calcActPos(currLin,currPoint.linSteps,distPerStepLin);
  currRot = calcActPos(currRot,currPoint.rotSteps,distPerStepRot);
  resetTimerVariables();
}

void runPath(int _pathNum, bool offsetPattern) {

  if (pNum==0 && !moveRot && !moveLin) {
    choosePath(_pathNum);
    timeStep = path[1][0] - path[0][0];
    calcNextPoint(pNum, timeStep, path[pNum][2]+currOffset, path[pNum][1], path[pNum][4], path[pNum][3], path[pNum][4], path[pNum][3]);
    pNum=1;
    pNumCompleted=0;
  }
  
  if ((pNum>0) && !moveRot && !moveLin && pNum<=fileLength) {
    currPoint = nextPoint;
    //Serial.println(String(currPoint.rotSteps)+", "+String(currPoint.linSteps)+", "+String(currPoint.rotCmr)+", "+String(currPoint.linCmr)+", "+String(currPoint.rotAcc)+", "+String(currPoint.linAcc));
    startMove();
    builtNextMove = false;
    pNumCompleted = pNumCompleted + 1;
  }

  if (pNum>=1 && !builtNextMove && pNum<fileLength) {
    calcNextPoint(pNum, timeStep, path[pNum][2]+currOffset, path[pNum][1], path[pNum][4], path[pNum][3], path[pNum-1][4], path[pNum-1][3]);
    builtNextMove = true;
    pNum++;
  }
   
  if (pNum==fileLength && pNumCompleted==(fileLength)) {
    Serial.println("here");
    pNum = 0;
    if (offsetPattern){
      currOffset = currOffset + offsetAngle;
    }
  }
}

void moveRelative(float _lPos, float _rPos, float _lVel, float _rVel){
  calcNextPoint(0,1,_rPos,_lPos,_rVel,_lVel,_rVel,_lVel);
  currPoint = nextPoint;
  startMove();
}
