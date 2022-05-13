void startMove() {
  buildInterrupts();
  setDirections(currPoint.rotSteps,currPoint.linSteps);
  //currLin = calcActPos(currLin,currPoint.linSteps,distPerStepLin);
  //currRot = calcActPos(currRot,currPoint.rotSteps,distPerStepRot);
  resetTimerVariables();
}

void resetTimerVariables() {
  stepCountRot = 0;
  stepCountLin = 0;
  moveStartedRot = false;
  moveStartedLin = false;
  moveRot = true;
  moveLin = true;
}

void buildInterrupts () {
  rotTimer = timerBegin(0, (1* prescalar), true);    // Use 1st timer of 4 (counted from zero). // Set 80 divider for prescaler
  timerAttachInterrupt(rotTimer, &onRotTimer, true); // Attach onTimer function to our timer.
  timerAlarmWrite(rotTimer, currPoint.rotCmr, true); // Set alarm to call onTimer function every second (value in microseconds). // Repeat the alarm (third parameter)
  timerAlarmEnable(rotTimer);                        // Start an alarm

  linTimer = timerBegin(1, (1* prescalar), true);    // Use 1st timer of 4 (counted from zero). // Set 80 divider for prescaler
  timerAttachInterrupt(linTimer, &onLinTimer, true); // Attach onTimer function to our timer.
  timerAlarmWrite(linTimer, currPoint.linCmr, true); // Set alarm to call onTimer function every second (value in microseconds). // Repeat the alarm (third parameter)
  timerAlarmEnable(linTimer);                        // Start an alarm
}

void ARDUINO_ISR_ATTR linHomed() {
  currLin = -140;
  currRot = 0;
  moveLin = false;
  moveRot = false;
  Serial.println("homed");
}

void ARDUINO_ISR_ATTR onRotTimer(){
  if (stepCountRot>=abs(currPoint.rotSteps)){
    moveStartedRot = true;
    moveRot = false;
  }
  
  if (moveRot){
    moveStartedRot = true;
    if (moveStartedLin) {
      if (stepPulseRot) {
        digitalWrite(rotStepPin, HIGH);
        stepPulseRot = false;
      }
      else {
        digitalWrite(rotStepPin, LOW);
        stepPulseRot = true;
        stepCountRot = stepCountRot + 1;
        currRot = currRot + (distPerStepRot*sgn(currPoint.rotSteps));
        currPoint.rotCmr = calcAccCmr(currPoint.rotCmr,currPoint.rotAcc);
        timerAlarmWrite(rotTimer, currPoint.rotCmr, true);
      }  
    }
  }
}

void ARDUINO_ISR_ATTR onLinTimer(){
  if (stepCountLin>=abs(currPoint.linSteps)){
    moveStartedLin = true;
    moveLin = false;
  }
  
  if (moveLin) {
    moveStartedLin = true;
    if (moveStartedRot) {
      if (stepPulseLin) {
        digitalWrite(linStepPin, HIGH);
        stepPulseLin = false;
      }
      else {
        digitalWrite(linStepPin, LOW);
        stepPulseLin = true;
        stepCountLin = stepCountLin + 1;
        currLin = currLin + (distPerStepLin*sgn(currPoint.linSteps));
        currPoint.linCmr = calcAccCmr(currPoint.linCmr,currPoint.linAcc);
        timerAlarmWrite(linTimer, currPoint.linCmr, true);
      }
    }
  }  
}

long calcAccCmr(long _cmr, long _cmrAcc) {
  _cmr = _cmr + _cmrAcc*(((_cmr*2)*prescalar)/clockHz);
  if (_cmr>500000) {_cmr=500000;}
  if (_cmr<10) {_cmr=10;}
  return _cmr;
}
