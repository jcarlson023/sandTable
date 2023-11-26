void calcNextPoint(float _pointNum, float _timeStep, float _rotTarg, float _linTarg, float _rotVel, float _linVel, float _prevRotVel, float _prevLinVel) {  // Used to calculate the next move while the current one is going
  _linTarg = _linTarg * 1000.0;             // convert the path point from m to mm
  _linVel = _linVel * 1000.0;               // convert the path vel from m/s to mm/s
  _prevLinVel = _prevLinVel * 1000.0;       // convert the path vel from m/s to mm/s
  
  float _rotSteps = calcNumSteps(_rotTarg, currRot, stepsPerDeg);  // calculate the number of steps required to get to the next position
  float _linSteps = calcNumSteps(_linTarg, currLin, stepsPerMM);

  float _rotStartUs = calcUs(_prevRotVel, distPerStepRot); // calculate the number of us between steps for the requested starting velocity, and the distance travelled per step
  float _linStartUs = calcUs(_prevLinVel, distPerStepLin);
  float _rotEndUs = calcUs(_rotVel, distPerStepRot); // calculate the ending us between steps for the requested ending velocity, and the distance travelled per step
  float _linEndUs = calcUs(_linVel, distPerStepLin);

  float _rotStartCmr = calcCmr(_rotStartUs); // calculate the required starting and ending CMR interrupt vale for lin and rot axis given the requested us step duration
  float _linStartCmr = calcCmr(_linStartUs);
  float _rotEndCmr = calcCmr(_rotEndUs);
  float _linEndCmr = calcCmr(_linEndUs);

  float _rotCmrAcc = (_rotStartCmr - _rotEndCmr) / _timeStep; // calculate the requested acceleration for the lin and rot axis, give the starting and end velocities
  float _linCmrAcc = (_linStartCmr - _linEndCmr) / _timeStep;

  nextPoint = {_rotSteps,_linSteps,_rotStartCmr,_linStartCmr,_rotCmrAcc,_linCmrAcc}; // store these values to be used at the beginning of the next move
}

float calcNumSteps(float _targ, float _curr, float _stepsPer) {  // calculate the number of steps needed to get to the next location
  return round((_targ-_curr) * _stepsPer);
}

/** I don't think this one should be used?
float calcActPos(float _targ, float _curr, float _numSteps, float _distPer) { // given the target, and the actual distance that can be covered given the step size, calculate the actual ending position (it will be slightly off of theo)
  long delta = _targ - _curr;
  long deltaAct = _numSteps * _distPer;
  return _curr + (deltaAct * sgn(delta));
} **/

float calcUs(float _vel, float _distPer) {  // calculate the number of us between steps for the requested velocity
  if (_vel==0) {
    return stepLengthLimit;}
  else {
    float _calcUs = round((_distPer/(abs(_vel)/microS))/2);
    if (_calcUs>=stepLengthLimit){
      return stepLengthLimit;
    } else {
      return _calcUs;
    }
  }
}

float calcCmr(float _usStep) {  // calculate the requested CMR size (essentially a timer that will time out in the requested number of us)
  float stepHz = microS / _usStep;
  return round(clockHz/(prescalar*stepHz))-1;
}


float calcActPos(float _curr, long _numSteps, float _distPerStep) {
  float deltAct = _numSteps * _distPerStep;
  return _curr + deltAct;
}

static inline int8_t sgn(float _val) {  // calculate the sign of the direcitonwe're trying to move
  if (_val < 0.0) return -1;
  return 1;
}
