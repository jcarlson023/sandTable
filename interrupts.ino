
void resetTimerVariables() {
  stepCountRot = 0;
  stepCountLin = 0;
  moveStartedRot = false;
  moveStartedLin = false;
  moveRot = true;
  moveLin = true;
}

void runRotStep() {
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
        currPoint.rotCmr = calcAccCmr(currPoint.rotCmr,currPoint.rotAcc);
        timerAlarmWrite(rotTimer, currPoint.rotCmr, true);
      }  
    }
  }
}

void runLinStep() {
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
        currPoint.linCmr = calcAccCmr(currPoint.linCmr,currPoint.linAcc);
        timerAlarmWrite(linTimer, currPoint.linCmr, true);
      }
    }
  }
}

long calcAccCmr(long _cmr, long _cmrAcc) {
  _cmr = _cmr + _cmrAcc*(((_cmr*2)*prescalar)/clockHz);
  if (_cmr>cmrLimit) {_cmr=cmrLimit;}
  if (_cmr<10) {_cmr=10;}
  return _cmr;
}

void runInterrupts() {
  if (rotInterruptCounter>0){
    portENTER_CRITICAL(&rotTimerMux);
    rotInterruptCounter--;
    portEXIT_CRITICAL(&rotTimerMux);
    runRotStep();
  }

  if (linInterruptCounter>0){
    portENTER_CRITICAL(&linTimerMux);
    linInterruptCounter--;
    portEXIT_CRITICAL(&linTimerMux);
    runLinStep();
  }
}

void buildInterrupts() {
  rotTimer = timerBegin(0, 256, true);                        // Use 1st timer of 4 (counted from zero). // Set 80 divider for prescaler
  timerAttachInterrupt(rotTimer, &onRotTimer, true);          // Attach onTimer function to our timer.
  timerAlarmWrite(rotTimer, 1000, true);
  timerAlarmEnable(rotTimer);                                 // Start an alarm

  linTimer = timerBegin(1, 256, true);                        // Use 1st timer of 4 (counted from zero). // Set 80 divider for prescaler
  timerAttachInterrupt(linTimer, &onLinTimer, true);          // Attach onTimer function to our timer.
  timerAlarmWrite(linTimer, 1000, true);
  timerAlarmEnable(linTimer);                                 // Start an alarm
}
