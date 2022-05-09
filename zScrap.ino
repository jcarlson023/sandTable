/**
#include "inits.h"
#include <SD.h>

float moveTimeNext = 0;
float lTargNext = 0;
float rTargNext = 0;
float lVelNext = 0;
float rVelNext = 0;
bool builtNextMove = false;

int path = 3;

int i = -1;
 
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

  buildInterrupts();

  DDRD = 0xFF;
  DDRB = 0xFF;
  PORTD = 0x00;
  PORTB = 0x00;

  pinMode(dirPin1, OUTPUT);
  pinMode(dirPin2, OUTPUT);
  pinMode(enablePin1, OUTPUT);
  digitalWrite(enablePin1, HIGH);

  switch (path) {
    case 1:
      fileName = "path.csv";
      fileLength = 267;
      currLin = 0.0;
      currRot = 0.0;
      break;
    case 2:
      fileName = "spirals2.csv";
      fileLength = 449;
      currLin = 160.0;
      currRot = 0.0;
      break;
    case 3:
      fileName = "slowPath.csv";
      fileLength = 1068;
      currLin = 0;
      currRot = 0.0;
      break;
    default:
      break;
  }
}

void loop() {
  
  if (i==-1) {
    myFile = SD.open(fileName);
    
    moveTimeNext = 0;
    lTargNext = 0;
    rTargNext = 0;
    lVelNext = 0;
    rVelNext = 0;
  }
  
  if ((i >= 0) && !moveRot && !moveLin) {
    cli();//stop interrupts
    buildCurrMove(rTargNext,lTargNext);
    if (!zeroDist) {
      startMove();
    }
    builtNextMove = false;
    sei();//allow interrupts
  }

  if (!builtNextMove || zeroDist) {
    moveTimeNext = (myFile.readStringUntil(',')).toFloat();
    lTargNext = (myFile.readStringUntil(',')).toFloat()*1000;
    rTargNext = (myFile.readStringUntil(',')).toFloat();
    lVelNext = ((myFile.readStringUntil(',')).toFloat()*1000);
    rVelNext = ((myFile.readStringUntil('\n')).toFloat());
    buildNextMove(rTargNext,lTargNext,abs(rVelNext),abs(lVelNext));
    builtNextMove = true;
    i++;
    //printFileReads();
  }
  

  
  if (i==(fileLength-2)) {
    myFile.close();
    i = -1;
    builtNextMove = false;
  }
  
}

void printFileReads() {
  Serial.print(String(moveTimeNext) + ", ");
  Serial.print(String(lTargNext) + ", ");
  Serial.print(String(rTargNext) + ", ");
  Serial.print(String(abs(lVelNext)) + ", ");
  Serial.println(String(abs(rVelNext)));
}
**/
