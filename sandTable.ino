
#include "inits.h"

// put in math to dynamically change the clock counters?

float path[22][4] = {{5, 10, 4, 6},
                    {10, 20, 4, 6.1},
                    {15, 30, 4, 6.2},
                    {20, 40, 4, 6.3},
                    {25, 50, 4, 6.4},
                    {30, 60, 4, 6.5},
                    {35, 70, 4, 6.6},
                    {40, 80, 4, 6.7},
                    {45, 90, 4, 6.8},
                    {50, 100, 4, 6.9},
                    {55, 110, 4, 7},
                    {50, 100, 4, 6.9},
                    {45, 90, 4, 6.8},
                    {40, 80, 4, 6.7},
                    {35, 70, 4, 6.6},
                    {30, 60, 4, 6.5},
                    {25, 50, 4, 6.4},
                    {20, 40, 4, 6.3},
                    {15, 30, 4, 6.2},
                    {10, 20, 4, 6.1},
                    {5, 10, 4, 6},
                    {0, 0, 4, 6}
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
      buildCurrMove(path[i][0], path[i][1]);
      startMove();
    }
    if (i != 21) {
      //Serial.println("rot: " + String(path[i+1][0]) + "lin: " + String(path[i+1][1]));
      buildNextMove(path[i + 1][0], path[i + 1][1], path[i + 1][2], path[i + 1][3]);
    }
    if (i >= 0) {
      while (moveStarted) {
        Serial.print("");
        if (!moveRot && !moveLin) {
          moveStarted = false;
          //moveStartedRot = false;
          //moveStartedLin = false;
        }
      }
    }
  }
}
