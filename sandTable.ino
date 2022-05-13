hw_timer_t * rotTimer = NULL;
hw_timer_t * linTimer = NULL;

#include "inits.h"

bool runPatt = false;
bool moveToPoint = true;
bool ranPoint = false;
int pNum = 0;

PathPoint currPoint = {0,0,0,0,0,0};
PathPoint nextPoint = {0,0,0,0,0,0};

void IRAM_ATTR linHomed() {
  Serial.println("homed");
}
                  
void setup() {

  for(int i=0;i<2000;i++)
    for(int j=0;j<11;j++)
        path[i][j] = 0;
 
  Serial.begin(115200);
  Serial.setTimeout(1000);
  
  pinMode(linLimitPin, INPUT);
  pinMode(rotDirPin, OUTPUT);
  pinMode(linDirPin, OUTPUT);
  pinMode(rotStepPin, OUTPUT);
  pinMode(linStepPin, OUTPUT);

  attachInterrupt(linLimitPin, linHomed, FALLING);
}

void loop() {

  if (runPatt) {
    runPath(2);
  }

  if (moveToPoint && !ranPoint){
    moveRelative(300,0,0,0);
    while (moveRot && moveLin){
      Serial.println("");
    }
  }
  
}
