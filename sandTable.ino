
#include "inits.h"
#include <SD.h>
 
File myFile;

// put in math to dynamically change the clock counters?
float spd = 40;
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
  Serial.begin(9600);

  Serial.print("Initializing SD card...");
  pinMode(10, OUTPUT); //sdCard
  if (!SD.begin(10)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
  myFile = SD.open("path.csv");

  buildInterrupts();

  DDRD = 0xFF;
  DDRB = 0xFF;
  PORTD = 0x00;
  PORTB = 0x00;

  pinMode(dirPin1, OUTPUT);
  pinMode(dirPin2, OUTPUT);
  pinMode(enablePin1, OUTPUT);
  digitalWrite(enablePin1, HIGH);
}

void loop() {
  
  myFile = SD.open("path.csv");
  
  float moveTimeNext = 0;
  float lTargNext = 0;
  float rTargNext = 0;
  float lVelNext = 0;
  float rVelNext = 0;
  int i = -1;
  
  while (myFile.available()) {
    if (i >= 0) {
      buildCurrMove(rTargNext,lTargNext);
      startMove();
    }
    moveTimeNext = (myFile.readStringUntil(',')).toFloat();
    lTargNext = (myFile.readStringUntil(',')).toFloat()*1000;
    rTargNext = (myFile.readStringUntil(',')).toFloat();
    lVelNext = ((myFile.readStringUntil(',')).toFloat()*1000);
    rVelNext = ((myFile.readStringUntil('\n')).toFloat());
    //Serial.print(String(moveTimeNext) + ", ");
    //Serial.print(String(lTargNext) + ", ");
    //Serial.print(String(rTargNext) + ", ");
    //Serial.print(String(abs(lVelNext)) + ", ");
    //Serial.println(String(abs(rVelNext)));
    buildNextMove(rTargNext,lTargNext,abs(rVelNext),abs(lVelNext));
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
    i = i + 1;
  }

  myFile.close();
}
