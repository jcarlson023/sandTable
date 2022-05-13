void runPath(int _pathNum) {

  if (pNum==0) {
    choosePath(_pathNum);
    timeStep = path[1][0] - path[0][0];
  }
  
  if ((pNum>0) && !moveRot && !moveLin) {
    currPoint = nextPoint;
    startMove();
    builtNextMove = false;
  }

  if (pNum>=0 && !builtNextMove) {
    calcNextPoint(pNum, timeStep, path[pNum][2], path[pNum][1], path[pNum][4], path[pNum][3], path[pNum+1][4], path[pNum+1][3]);
    builtNextMove = true;
    pNum++;
  }
   
  if (pNum==(fileLength-2)) {
    pNum = 0;
    builtNextMove = false;
  }
}

void moveRelative(float _lPos, float _rPos, float _lVel, float _rVel){
  calcNextPoint(0,1,_rPos,_lPos,_rVel,_lVel,_rVel,_lVel);
  currPoint = nextPoint;
  startMove();
}
