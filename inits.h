
struct PathPoint {
  float rotSteps;
  float linSteps;
  float rotCmr;
  float linCmr;
  float rotAcc;
  float linAcc;
};

PathPoint currPoint = {0,0,0,0,0,0};
PathPoint nextPoint = {0,0,0,0,0,0};

float currLin = 0;
float currRot = 0;

// file variables
float path[2000][5];
String fileName;
int fileLength;

// next move planning
bool builtNextMove = false;
bool moveRot = false;
bool moveLin = false;
bool moveStartedRot;
bool moveStartedLin;
float timeStep;

// Timing variables
hw_timer_t * rotTimer = NULL;
hw_timer_t * linTimer = NULL;
const long stepLengthLimit = 200000;
const long clockHz = 80000000;
const long microS = 1000000;
const long prescalar = 256;
bool stepPulseRot = true;
bool stepPulseLin = true;
long stepCountRot;
long stepCountLin;

// Motion parameters
const long microStep = 16;
const long pulleyTeeth = 126;
const long motorTeeth = 20;
const float pulleyRatio = pulleyTeeth / motorTeeth;
const float stepsPerRev = 200 * pulleyRatio * microStep;
const float stepsPerDeg = stepsPerRev / 360;
const float stepsPerMM = (5.0 * microStep);
const float distPerStepRot = 1.0 / stepsPerDeg;
const float distPerStepLin = 1.0 / stepsPerMM;

// Pin Defs
const int rotDirPin = 13; // port PC6 PORTD // changed to 5 from 4
const int rotStepPin = 14; // port PF5 PORTD // changed to 18 from 3
const int linDirPin = 12; // port PA0 PORTD
const int linStepPin = 27; // port PB0 PORTB //changed from 15
const int linLimitPin = 26;
