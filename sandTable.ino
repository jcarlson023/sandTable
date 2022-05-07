
#include "inits.h"
#include "path.h"

// put in math to dynamically change the clock counters?
int spd = 40;
float path[22][4] = {{5, 10, 4, spd},
                    {10, 20, 4, spd},
                    {15, 30, 4, spd},
                    {20, 40, 4, spd},
                    {25, 50, 4, spd},
                    {30, 60, 4, spd},
                    {35, 70, 4, spd},
                    {40, 80, 4, spd},
                    {45, 90, 4, spd},
                    {50, 100, 4,spd},
                    {55, 110, 4, spd},
                    {50, 100, 4, spd},
                    {45, 90, 4, spd},
                    {40, 80, 4, spd},
                    {35, 70, 4, spd},
                    {30, 60, 4, spd},
                    {25, 50, 4, spd},
                    {20, 40, 4, spd},
                    {15, 30, 4, spd},
                    {10, 20, 4, spd},
                    {5, 10, 4, spd},
                    {0, 0, 4, spd}};
                  
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
      //buildCurrMove(coolPath[i][2],coolPath[i][1]);
      startMove();
    }
    if (i != 21) {
      buildNextMove(path[i+1][0],path[i+1][1],path[i+1][2],path[i+1][3]);
      //buildNextMove(coolPath[i+1][2],coolPath[i+1][1],coolPath[i+1][4],coolPath[i+1][3]);
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
