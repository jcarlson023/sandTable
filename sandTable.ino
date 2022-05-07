
#include "inits.h"

// put in math to dynamically change the clock counters?


float path[22][4] = {{5, 10, 4, 9},
                    {10, 20, 4, 9.5},
                    {15, 30, 4, 10},
                    {20, 40, 4, 10.5},
                    {25, 50, 4, 11},
                    {30, 60, 4, 11.5},
                    {35, 70, 4, 12},
                    {60, 80, 4, 12.5},
                    {70, 90, 4, 13},
                    {80, 100, 4,13.5},
                    {90, 140, 4, 20},
                    {80, 100, 4, 13.5},
                    {70, 90, 4, 13},
                    {60, 80, 4, 12.5},
                    {35, 70, 4, 12},
                    {30, 60, 4, 11.5},
                    {25, 50, 4, 11},
                    {20, 40, 4, 10.5},
                    {15, 30, 4, 10},
                    {10, 20, 4, 9.5},
                    {5, 10, 4, 9},
                    {0, 0, 4, 9}
                  };
                  
void setup() {

  buildInterrupts();

  DDRD = 0xFF;
  DDRB = 0xFF;
  PORTD = 0x00;
  PORTB = 0x00;

  pinMode(dirPin1, OUTPUT);
  pinMode(dirPin2, OUTPUT);
  pinMode(enablePin1, OUTPUT);
  digitalWrite(enablePin1, HIGH);

  Serial.begin(9600);
}

void loop() {

  for (int i = -1; i < 22; i++) {
    if (i >= 0) {
      buildCurrMove(path[i][0],path[i][1]);
      startMove();
    }
    if (i != 21) {
      buildNextMove(path[i + 1][0], path[i + 1][1], path[i + 1][2], path[i + 1][3]);
    }
    if (i >= 0) {
      while (moveStarted) {
        Serial.print("");
        if (!moveRot && !moveLin) {
          moveStarted = false;
          moveStartedRot = false;
          moveStartedLin = false;
        }
      }
    }
  }
}
