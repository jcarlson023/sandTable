#include "inits.h"
#include "z_lissajousA.h"

bool isHomed = false;
bool runPatt = false;
bool moveToPoint = true;
bool ranPoint = false;
int pNum = 0;
              
void setup() {
  Serial.begin(115200);
  pinMode(linLimitPin, INPUT);
  pinMode(rotDirPin, OUTPUT);
  pinMode(linDirPin, OUTPUT);
  pinMode(rotStepPin, OUTPUT);
  pinMode(linStepPin, OUTPUT);
}

void loop() {

  if (!isHomed) {
    runHoming();
  }

  if (runPatt) {
    runPath(1);
  }

  if (moveToPoint && !ranPoint){
    moveRelative(300,0,10,10);
    while (moveRot && moveLin){
      Serial.println("");
    }
    ranPoint = true;
  }
  
}
