
#include "inits.h"
//#include <SD.h>

hw_timer_t * rotTimer = NULL;
hw_timer_t * linTimer = NULL;
  
bool runPatt = true;
bool moveToPoint = false;
bool ranPoint = false;
int i = -1;
 
//File myFile;
                  
void setup() {
  Serial.begin(115200);
  Serial.setTimeout(1000);

  //Serial.print("Initializing SD card...");
  //pinMode(2, OUTPUT); //sdCard
  //if (!SD.begin(2)) {
  //  Serial.println("initialization failed!");
  //  return;
  //}
  //Serial.println("initialization done.");

  //DDRD = 0xFF; // set as outputs
  //DDRB = 0xFF; // set as outputs
  //PORTD = 0x00; // set all as low
  //PORTB = 0x00; // set all as low
  
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
