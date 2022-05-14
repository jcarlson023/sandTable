void calcNextPoint(float _pointNum, float _timeStep, float _rotTarg, float _linTarg, float _rotVel, float _linVel, float _prevRotVel, float _prevLinVel) {
  _linTarg = _linTarg * 1000.0;
  _linVel = _linVel * 1000.0;
  _prevLinVel = _prevLinVel * 1000.0;
  
  float _rotSteps = calcNumSteps(_rotTarg, currRot, stepsPerDeg);
  float _linSteps = calcNumSteps(_linTarg, currLin, stepsPerMM);

  float _rotStartUs = calcUs(_prevRotVel, distPerStepRot);
  float _linStartUs = calcUs(_prevLinVel, distPerStepLin);
  float _rotEndUs = calcUs(_rotVel, distPerStepRot);
  float _linEndUs = calcUs(_linVel, distPerStepLin);

  float _rotStartCmr = calcCmr(_rotStartUs);
  float _linStartCmr = calcCmr(_linStartUs);
  float _rotEndCmr = calcCmr(_rotEndUs);
  float _linEndCmr = calcCmr(_linEndUs);

  float _rotCmrAcc = (_rotStartCmr - _rotEndCmr) / _timeStep;
  float _linCmrAcc = (_linStartCmr - _linEndCmr) / _timeStep;

  nextPoint = {_rotSteps,_linSteps,_rotStartCmr,_linStartCmr,_rotCmrAcc,_linCmrAcc};
}

float calcNumSteps(float _targ, float _curr, float _stepsPer) {
  return round((_targ-_curr) * _stepsPer);
}

float calcActPos(float _targ, float _curr, float _numSteps, float _distPer) {
  long delta = _targ - _curr;
  long deltaAct = _numSteps * _distPer;
  return _curr + (deltaAct * sgn(delta));
}

float calcUs(float _vel, float _distPer) {
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

float calcCmr(float _usStep) {
  float stepHz = microS / _usStep;
  return round(clockHz/(prescalar*stepHz))-1;
}

void setDirections(float _stepsRot, float _stepsLin) {
  // Change direction pin output based on sign of position delta
  if (_stepsRot>=0) {digitalWrite(rotDirPin, LOW);}  // counter-clockwise
  else {          digitalWrite(rotDirPin, HIGH);} // clockwise

  if (_stepsLin>=0) {digitalWrite(linDirPin, HIGH);} // towards motor
  else {          digitalWrite(linDirPin, LOW);}  // away motor
}

float calcActPos(float _curr, long _numSteps, float _distPerStep) {
  float deltAct = _numSteps * _distPerStep;
  return _curr + deltAct;;
}

static inline int8_t sgn(float _val) {
  if (_val < 0.0) return -1;
  return 1;
}
