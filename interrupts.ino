void buildInterrupts() {
  cli();//stop interrupts

  //set timer0 interrupt at 2kHz
  TCCR0A = 0;                           // set entire TCCR0A register to 0
  TCCR0B = 0;                           // same for TCCR0B
  TCNT0  = 0;                           // initialize counter value to 0
  TCCR0A |= (1 << WGM01);               // turn on CTC mode
  TCCR0B |= (1 << CS02);                // 256 prescaler
  TIMSK0 |= (1 << OCIE0A);              // enable timer compare interrups
  OCR0A = 200;
  
  //set timer1 interrupt at 1Hz
  TCCR1A = 0;                           // set entire TCCR1A register to 0
  TCCR1B = 0;                           // same for TCCR1B
  TCNT1  = 0;                           //initialize counter value to 0
  TCCR1B |= (1 << WGM12);               // turn on CTC mode
  TCCR1B |= (1 << CS12);                // 256 prescaler
  TIMSK1 |= (1 << OCIE1A);              // enable timer compare interrupt
  OCR1A = 200;

  sei();//allow interrupts
}

ISR(TIMER0_COMPA_vect){
  if (moveRot){
    moveStartedRot = true;
    if (moveStartedLin) {
      if (stepPulseRot) {
        PORTD = PORTD | 0x08; // set high, pin 3
        stepPulseRot = false;
      }
      else {
        PORTD = PORTD & 0xF7; // set low, pin 3
        stepPulseRot = true;
        stepCountRot = stepCountRot + 1;
      }
      if (stepCountRot>=stepsRot){
        moveRot = false;
        moveStartedRot = false;
      }
    }
  }
}

ISR(TIMER1_COMPA_vect){

  if (moveLin) {
    moveStartedLin = true;
    if (moveStartedRot) {
      if (stepPulseLin) {
        PORTB = PORTB | 0x02; // set high, pin 8
        stepPulseLin = false;
      }
      else {
        PORTB = PORTB & 0xFD; // set low, pin 8
        stepPulseLin = true;
        stepCountLin = stepCountLin + 1;
      }
      if (stepCountLin>=stepsLin){
        moveLin = false;
        moveStartedLin = false;
      }
    }
  }  
}

void setCmrRot(float prescalar, float cmr) {
  //Serial.println("rot prescalar " + String(prescalar));
  /*
  switch (int(prescalar)) {
    case 1:
      TCCR0B |= (0 << CS02) | (0 << CS01) | (1 << CS00); // 1 prescaler
      break;
    case 8:
      TCCR0B |= (0 << CS02) | (1 << CS01) | (0 << CS00); // 8 prescaler
      break;
    case 64:
      TCCR0B |= (0 << CS02) | (1 << CS01) | (1 << CS00); // 64 prescaler
      break;
    case 256:
      TCCR0B |= (1 << CS02) | (0 << CS01) | (0 << CS00); // 256 prescaler
      break;
    case 1024:
      TCCR0B |= (1 << CS02) | (0 << CS01) | (1 << CS00); // 1024 prescaler
      break;
    default:
      TCCR0B |= (1 << CS02) | (0 << CS01) | (1 << CS00); // 1024 prescaler
      break;
  }*/

  OCR0A = int(cmr);
  
}

void setCmrLin(float prescalar, float cmr) {

  //Serial.println("lin prescalar " + String(prescalar));
  /*
  switch (int(prescalar)) {
    case 1:
      TCCR1B |= (0 << CS12) | (0 << CS11) | (1 << CS10); // 1 prescaler
      break;
    case 8:
      TCCR1B |= (0 << CS12) | (1 << CS11) | (0 << CS10); // 8 prescaler
      break;
    case 64:
      TCCR1B |= (0 << CS12) | (1 << CS11) | (1 << CS10); // 64 prescaler
      break;
    case 256:
      TCCR1B |= (1 << CS12) | (0 << CS11) | (0 << CS10); // 256 prescaler
      break;
    case 1024:
      TCCR1B |= (1 << CS12) | (0 << CS11) | (1 << CS10); // 1024 prescaler
      break;
    default:
      TCCR1B |= (1 << CS12) | (0 << CS11) | (1 << CS10); // 1024 prescaler
      break;
  }*/
  
  OCR1A = int(cmr); 
}
