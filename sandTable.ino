
#include "inits.h"
#include <SD.h>

int fileLength = 449;
float currRot = 0.0;
//float currLin = 0.0;
float currLin = 160.0;
 
File myFile;
                  
void setup() {
  Serial.begin(9600);
  Serial.setTimeout(1000);

  Serial.print("Initializing SD card...");
  pinMode(10, OUTPUT); //sdCard
  if (!SD.begin(10)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
  //myFile = SD.open("path.csv");

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
  
  myFile = SD.open("spirals2.csv");
  
  float moveTimeNext = 0;
  float lTargNext = 0;
  float rTargNext = 0;
  float lVelNext = 0;
  float rVelNext = 0;
  
  for (int i=-1; i<fileLength-2; i++) {
    if (i >= 0) {
      buildCurrMove(rTargNext,lTargNext);
      startMove();
    }
    if (myFile.available()) {moveTimeNext = (myFile.readStringUntil(',')).toFloat();} else {break;}
    if (myFile.available()) {lTargNext = (myFile.readStringUntil(',')).toFloat()*1000;} else {break;}
    if (myFile.available()) {rTargNext = (myFile.readStringUntil(',')).toFloat();} else {break;}
    if (myFile.available()) {lVelNext = ((myFile.readStringUntil(',')).toFloat()*1000);} else {break;}
    if (myFile.available()) {rVelNext = ((myFile.readStringUntil('\n')).toFloat());} else {break;}
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
  }

  myFile.close();
}
