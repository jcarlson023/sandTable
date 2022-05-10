void buildInterrupts () {
  //hw_timer_t * rotTimer = NULL;
  rotTimer = timerBegin(0, 5 * prescalarRot, true);  // Use 1st timer of 4 (counted from zero). // Set 80 divider for prescaler
  timerAttachInterrupt(rotTimer, &onRotTimer, true); // Attach onTimer function to our timer.
  timerAlarmWrite(rotTimer, cmrRot, true);           // Set alarm to call onTimer function every second (value in microseconds). // Repeat the alarm (third parameter)
  timerAlarmEnable(rotTimer);                        // Start an alarm

  //hw_timer_t * linTimer = NULL;
  linTimer = timerBegin(1, 5 * prescalarLin , true); // Use 1st timer of 4 (counted from zero). // Set 80 divider for prescaler
  timerAttachInterrupt(linTimer, &onLinTimer, true); // Attach onTimer function to our timer.
  timerAlarmWrite(linTimer, cmrLin, true);           // Set alarm to call onTimer function every second (value in microseconds). // Repeat the alarm (third parameter)
  timerAlarmEnable(linTimer);                        // Start an alarm
}

void ARDUINO_ISR_ATTR onRotTimer(){
  if (moveRot){
    moveStartedRot = true;
    if (moveStartedLin) {
      if (stepPulseRot) {
        //PORTD = PORTD | 0x08; // set high, pin 3
        digitalWrite(rotStepPin, HIGH);
        stepPulseRot = false;
      }
      else {
        //PORTD = PORTD & 0xF7; // set low, pin 3
        digitalWrite(rotStepPin, LOW);
        stepPulseRot = true;
        stepCountRot = stepCountRot + 1;
        cmrRot = cmrRot + cmrRotAcc*((cmrRot*prescalarRot)/clockHz);
        if (cmrRot>255) {cmrRot = 255;}
        if (cmrRot<10) {cmrRot = 10;}
        timerAlarmWrite(rotTimer, cmrRot, true);
      }
      if (stepCountRot>=stepsRot){
        moveRot = false;
      }
    }
  }
}

void ARDUINO_ISR_ATTR onLinTimer(){
  if (moveLin) {
    moveStartedLin = true;
    if (moveStartedRot) {
      if (stepPulseLin) {
        //PORTB = PORTB | 0x02; // set high, pin 8
        digitalWrite(linStepPin, HIGH);
        stepPulseLin = false;
      }
      else {
        //PORTB = PORTB & 0xFD; // set low, pin 8
        digitalWrite(linStepPin, LOW);
        stepPulseLin = true;
        stepCountLin = stepCountLin + 1;
        cmrLin = cmrLin + cmrLinAcc*((cmrLin*prescalarLin)/clockHz);
        if (cmrLin>255) {cmrLin=255;}
        if (cmrLin<10) {cmrLin=10;}
        timerAlarmWrite(linTimer, cmrLin, true);
      }
      if (stepCountLin>=stepsLin){
        moveLin = false;
      }
    }
  }  
}
