void buildInterrupts() {
  rotTimer = timerBegin(0, 256, true);                        // Use 1st timer of 4 (counted from zero). // Set 256 divider for prescaler
  timerAttachInterrupt(rotTimer, &onRotTimer, true);          // Attach onTimer function to our timer.
  timerAlarmWrite(rotTimer, 1000, true);
  timerAlarmEnable(rotTimer);                                 // Start an alarm

  linTimer = timerBegin(1, 256, true);                        // Use 2nd timer of 4 (counted from zero). // Set 246 divider for prescaler
  timerAttachInterrupt(linTimer, &onLinTimer, true);          // Attach onTimer function to our timer.
  timerAlarmWrite(linTimer, 1000, true);
  timerAlarmEnable(linTimer);                                 // Start an alarm
}

void resetTimerVariables() { // Just resets everything at the start of every point. This is called from startMove()
  stepCountRot = 0;
  stepCountLin = 0;
  moveStartedRot = false;
  moveStartedLin = false;
  moveRot = true;
  moveLin = true;
}

void runInterrupts() {                         // Function block to carry out the timer interrupts
  if (rotInterruptCounter>0){                  // When greater than 0, theres still steps to carry out
    portENTER_CRITICAL(&rotTimerMux);          // Not entirely sure, internet told me to do it
    rotInterruptCounter--;                     // Not entirely sure TBH, I think its for the timer interrupt itself?
    portEXIT_CRITICAL(&rotTimerMux);           // Not entirely sure, internet told me to do it
    runRotStep();                              // Run that step (controls the pulses, acceleration, step counting)
  }

  if (linInterruptCounter>0){                  // When greater than 0, theres still steps to carry out
    portENTER_CRITICAL(&linTimerMux);          // Not entirely sure, internet told me to do it
    linInterruptCounter--;                     // Not entirely sure TBH, I think its for the timer interrupt itself?
    portEXIT_CRITICAL(&linTimerMux);           // Not entirely sure, internet told me to do it
    runLinStep();                              // Run that step (controls the pulses, acceleration, step counting)
  }
}

void runRotStep() {                                                           // Run the rotational axis steps
  if (stepCountRot>=abs(currPoint.rotSteps)){                                 // if the number of steps is equal to or greater to the number of steps for that move, stop moving!
    moveStartedRot = true;                                                    // I forget why moveStartedRot needs to be set true here? It's set false at the start of the move
    moveRot = false;
  }
  
  if (moveRot){
    moveStartedRot = true;                                                    // Tell is we've started the rotational move succesfully, wait until the linear move says the same
    if (moveStartedLin) {                                                     
      if (stepPulseRot) {                                                     // Flip flop flag to switch between high and low pulses on the stepper
        digitalWrite(rotStepPin, HIGH);                                       // write the stepper pin
        stepPulseRot = false;                                                 // flop that flip flag
      }
      else {
        digitalWrite(rotStepPin, LOW);                                        // same as the other block, just the opposite. also increment the steps. also re-calc the new CMR based on the ACC
        stepPulseRot = true;
        stepCountRot = stepCountRot + 1;
        currPoint.rotCmr = calcAccCmr(currPoint.rotCmr,currPoint.rotAcc);
        timerAlarmWrite(rotTimer, currPoint.rotCmr, true);
      }  
    }
  }
}

void runLinStep() {  // RE: runRotStep, just for the linear axis
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
 
long calcAccCmr(long _cmr, long _cmrAcc) {                // Calculate the changing CMR interrupt value based off of the calculated accelration of the move
  _cmr = _cmr + _cmrAcc*(((_cmr*2)*prescalar)/clockHz);   // v1 = v0 + a*t, essentially 
  if (_cmr>cmrLimit) {_cmr=cmrLimit;}                     // control the extents to what the CMR can be
  if (_cmr<10) {_cmr=10;}
  return _cmr;
}
