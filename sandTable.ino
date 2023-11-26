// Library imports
#include "inits.h"
#include "z_lissajousA.h"
#include "z_spiralsB.h"
#include "z_straightTest.h"
#include "z_lissajousSlow.h"

// Variable initializtion
bool runPatt = true;         //
bool moveToPoint = false;    //

hw_timer_t * rotTimer = NULL;                              // Internet told me to do it
hw_timer_t * linTimer = NULL;                              // Internet told me to do it
portMUX_TYPE rotTimerMux = portMUX_INITIALIZER_UNLOCKED;   // Internet told me to do it
portMUX_TYPE linTimerMux = portMUX_INITIALIZER_UNLOCKED;   // Internet told me to do it
volatile int rotInterruptCounter;                          // Internet told me to do it
volatile int linInterruptCounter;                          // Internet told me to do it

// Interrupt timer for rotation axis function
void IRAM_ATTR onRotTimer() {
  portENTER_CRITICAL_ISR(&rotTimerMux);
  rotInterruptCounter++;
  portEXIT_CRITICAL_ISR(&rotTimerMux);
}

// Interrupt timer for linear axis function
void IRAM_ATTR onLinTimer() {
  portENTER_CRITICAL_ISR(&linTimerMux);
  linInterruptCounter++;
  portEXIT_CRITICAL_ISR(&linTimerMux);
}

// Interrupt timer for linear axis home function
void IRAM_ATTR linHomed() {
  if (!isHomed) {
    homedFlag = true;
  }
}

void setup() {
  Serial.begin(115200);            // Begin serial printouts
  Serial.setTimeout(1000);

  buildInterrupts();               // Initialize the interrupts

  pinMode(linLimitPin, INPUT);     // Set the output pins
  pinMode(rotDirPin, OUTPUT);      //
  pinMode(linDirPin, OUTPUT);      //
  pinMode(rotStepPin, OUTPUT);     //
  pinMode(linStepPin, OUTPUT);     //
}

void loop() {

  if (!isHomed) {                  // If the table is not homed, home it. Only happens at first boot
    homingRoutine();
  }

  if (runPatt && isHomed) {        // Set a pattern to run, does the move calculations
    runPath(4, false);
  }

  if (moveToPoint && isHomed) {    // Not a pattern, just a move-to command if I want to use it. I think I was using this to find the middle?
    runMoveTo();
  }

  if (moveLin || moveRot) {        // This actually initiates the move
    runInterrupts();
  }

}
