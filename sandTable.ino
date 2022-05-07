
#include "inits.h"

// put in math to dynamically change the clock counters?

float path[22][4] = {{5,10,0,6},
                  {10,20,0,6.1},
                  {15,30,0,6.2},
                  {20,40,0,6.3},
                  {25,50,0,6.4},
                  {30,60,0,6.5},
                  {35,70,0,6.6},
                  {40,80,0,6.7},
                  {45,90,0,6.8},
                  {50,100,0,6.9},
                  {55,110,0,7},
                  {50,100,0,6.9},
                  {45,90,0,6.8},
                  {40,80,0,6.7},
                  {35,70,0,6.6},
                  {30,60,0,6.5},
                  {25,50,0,6.4},
                  {20,40,0,6.3},
                  {15,30,0,6.2},
                  {10,20,0,6.1},
                  {5,10,0,6},
                  {0,0,0,6}};

void setup() {

  buildInterrupts();

  pinMode(stepPin1, OUTPUT);
  pinMode(dirPin1, OUTPUT);
  pinMode(stepPin2, OUTPUT);
  pinMode(dirPin2, OUTPUT);
  pinMode(enablePin1, OUTPUT);
  digitalWrite(enablePin1,HIGH);

  Serial.begin(9600);
}

void loop() {
  
  for (int i=-1; i<22; i++){
    if (i>=0){
      buildCurrMove(path[i][0],path[i][1]);
      startMove();
    }
    if (i!=21) {
        //Serial.println("rot: " + String(path[i+1][0]) + "lin: " + String(path[i+1][1]));
        buildNextMove(path[i+1][0],path[i+1][1],path[i+1][2],path[i+1][3]);
    }
    if (i>=0) {
      while (moveStarted){
        Serial.print("");
        if (!moveRot && !moveLin){
          moveStarted = false;
        }  
      }
    }
  }
}
