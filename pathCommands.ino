void runPath(int _pathNum, bool offsetPattern) {

  if (pNum==0 && !moveRot && !moveLin) { // load in the selected path, learn the timestep, and initialize the first point
    choosePath(_pathNum);
    timeStep = path[1][0] - path[0][0];
    calcNextPoint(pNum, timeStep, path[pNum][2]+currOffset, path[pNum][1], path[pNum][4], path[pNum][3], path[pNum][4], path[pNum][3]);
    pNum=1;
    pNumCompleted=0;
  }
  
  if ((pNum>0) && !moveRot && !moveLin && pNum<=fileLength) { // switch the loaded in next point as the current point, start the move, and tell us the next move has not been built yet. increment the point
    currPoint = nextPoint;
    //Serial.println(String(currPoint.rotSteps)+", "+String(currPoint.linSteps)+", "+String(currPoint.rotCmr)+", "+String(currPoint.linCmr)+", "+String(currPoint.rotAcc)+", "+String(currPoint.linAcc));
    startMove();
    builtNextMove = false;
    pNumCompleted++;
  }

  if (pNum>=1 && !builtNextMove && pNum<fileLength) { // build the next move. Output of this is "nextPoint"
    calcNextPoint(pNum, timeStep, path[pNum][2]+currOffset, path[pNum][1], path[pNum][4], path[pNum][3], path[pNum-1][4], path[pNum-1][3]);
    builtNextMove = true;
    pNum++;
  }
   
  if (pNum==fileLength && pNumCompleted==(fileLength)) { // if the path is done, startover and apply an offset angle if applicable
    pNum = 0;
    if (offsetPattern){
      currOffset = currOffset + offsetAngle;
      if (currOffset>=360){
        currOffset=0;
      }
    }
  }
}

void startMove() { // start the next mvoe! 
  timerAlarmWrite(rotTimer, currPoint.rotCmr, true); // Set the initial counter interrupt, this will be changed for every pulse to account for acceleration
  timerAlarmWrite(linTimer, currPoint.linCmr, true); // 
  setDirections(currPoint.rotSteps,currPoint.linSteps); // the direction of the move given the sign
  currLin = calcActPos(currLin,currPoint.linSteps,distPerStepLin); // figure out what the actual position is given the number of steps
  currRot = calcActPos(currRot,currPoint.rotSteps,distPerStepRot);
  resetTimerVariables();
}

void setDirections(float _stepsRot, float _stepsLin) {  // set direction 
  // Change direction pin output based on sign of position delta
  if (_stepsRot>=0) {digitalWrite(rotDirPin, LOW);}  // counter-clockwise
  else {          digitalWrite(rotDirPin, HIGH);} // clockwise

  if (_stepsLin>=0) {digitalWrite(linDirPin, HIGH);} // towards motor
  else {          digitalWrite(linDirPin, LOW);}  // away motor
}

void runMoveTo() { // used for figuring out the center I'm pretty sure?
  if (manPointNum==1 && !moveLin && !moveRot) {
    moveRelative(0,0,0.06,0.06);
    manPointNum++;
  }
  if (manPointNum==2 && !moveLin && !moveRot) {
    moveRelative(0,720,0.04,200);
    manPointNum++;
  }
}

void moveRelative(float _lPos, float _rPos, float _lVel, float _rVel){
  calcNextPoint(0,1,_rPos,_lPos,_rVel,_lVel,_rVel,_lVel);
  currPoint = nextPoint;
  startMove();
}
