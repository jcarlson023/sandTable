#include "inits.h"
#include "z_lissajousA.h"
#include "z_spiralsA.h"
#include "z_straightTest.h"

bool runPatt = true;
bool moveToPoint = false;

hw_timer_t * rotTimer = NULL;
hw_timer_t * linTimer = NULL;
portMUX_TYPE rotTimerMux = portMUX_INITIALIZER_UNLOCKED;
portMUX_TYPE linTimerMux = portMUX_INITIALIZER_UNLOCKED;
volatile int rotInterruptCounter;
volatile int linInterruptCounter;

void IRAM_ATTR onRotTimer(){
  portENTER_CRITICAL_ISR(&rotTimerMux);
  rotInterruptCounter++;
  portEXIT_CRITICAL_ISR(&rotTimerMux);
}

void IRAM_ATTR onLinTimer(){
  portENTER_CRITICAL_ISR(&linTimerMux);
  linInterruptCounter++;
  portEXIT_CRITICAL_ISR(&linTimerMux);
}

void IRAM_ATTR linHomed() {
  if (!isHomed){
    setHome();
  }
}
              
void setup() {
  Serial.begin(115200);
  Serial.setTimeout(1000);

  buildInterrupts ();
  
  pinMode(linLimitPin, INPUT);
  pinMode(rotDirPin, OUTPUT);
  pinMode(linDirPin, OUTPUT);
  pinMode(rotStepPin, OUTPUT);
  pinMode(linStepPin, OUTPUT);      
}

void loop() {
  
  homingRoutine();

  if (runPatt && isHomed) {
    runPath(3,true);
  }

  if (moveToPoint && isHomed){
    if (manPointNum==1 && !moveLin && !moveRot) {
      moveRelative(0,0,0.06,0.06);
      manPointNum++;
    }
    if (manPointNum==2 && !moveLin && !moveRot) {
      moveRelative(0,720,0.04,200);
      manPointNum++;
    }
  }

  if (moveLin || moveRot) {
    runInterrupts();
  }
  
}
