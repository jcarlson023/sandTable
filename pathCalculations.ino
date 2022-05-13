
void calcNextPoint(float _pointNum, float _timeStep, float _rotTarg, float _linTarg, float _rotVel, float _linVel, float _prevRotVel, float _prevLinVel) {
  float rotSteps = calcNumSteps(_rotTarg, currRot, stepsPerDeg);
  float linSteps = calcNumSteps(_linTarg, currLin, stepsPerMM);

  float rotStartUs = calcUs(_prevRotVel, distPerStepRot);
  float linStartUs = calcUs(_prevLinVel, distPerStepLin);
  float rotEndUs = calcUs(_rotVel, distPerStepRot);
  float linEndUs = calcUs(_linVel, distPerStepLin);

  float rotStartCmr = calcCmr(rotStartUs);
  float linStartCmr = calcCmr(linStartUs);
  float rotEndCmr = calcCmr(rotEndUs);
  float linEndCmr = calcCmr(linEndUs);

  float rotCmrAcc = (rotStartCmr - rotEndCmr) / _timeStep;
  float linCmrAcc = (linStartCmr - linEndCmr) / _timeStep;

  nextPoint = {rotSteps,linSteps,rotStartCmr,linStartCmr,rotCmrAcc,linCmrAcc};
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
  if (_vel==0) {return stepLengthLimit;}
  else {return round((_distPer/(abs(_vel)/microS))/2);}
}

float calcCmr(float _usStep) {
  long stepHz = microS / _usStep;
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
