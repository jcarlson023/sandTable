hw_timer_t * rotTimer = NULL;
hw_timer_t * linTimer = NULL;

#include "inits.h"  
#include "lissajousPathA.h"
#include "lissajousPathB.h"
#include "spiralsPath.h"

bool runPatt = true;
bool moveToPoint = false;
bool ranPoint = false;
int i = -1;
                  
void setup() {
  Serial.begin(115200);
  Serial.setTimeout(1000);
  
  pinMode(rotDirPin, OUTPUT);
  pinMode(linDirPin, OUTPUT);
  pinMode(rotStepPin, OUTPUT);
  pinMode(linStepPin, OUTPUT);

}

void loop() {

  if (runPatt) {
    runPattern();
  }

  if (moveToPoint && !ranPoint){
    // linear, rotation, linear vel, rotation vel
    moveRelative(100,180,0,0);
    ranPoint = true;
  }
  
}
