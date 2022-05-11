
String fileName;
float currLin;
float currRot;
int fileLength;
float path[2000][11];


// next move planning
long nextStepsRot;
long nextStepsLin;
float nextRotAct;
float nextLinAct;
long nextCmrRot;
long nextCmrLin;
long nextCmrRotAcc;
long nextCmrLinAcc;
long nextPrescalarRot;
long nextPrescalarLin;
bool moveStartedRot;
bool moveStartedLin;
float moveTimeNext = 0;
float lTargNext = 0;
float rTargNext = 0;
float lVelNext = 0;
float rVelNext = 0;
bool zeroDist = false;
bool builtNextMove = false;

// curr move planning
long stepsRot;
long stepsLin;
long stepCountRot;
long stepCountLin;
long prescalarRot;
long prescalarLin;
long cmrRot;
long cmrLin;
long cmrRotAcc;
long cmrLinAcc;
bool moveRot = false;
bool moveLin = false;

// Timing variables
// compare match register = [16,000,000 / (prescaler * time delay) ] -1
const long clockHz = 80000000;
const long microS = 1000000;
long preSclr = 256;
bool stepPulseRot = true;
bool stepPulseLin = true;

// Motion parameters
const long microStep = 16;
const long pulleyTeeth = 126;
const long motorTeeth = 20;
const float pulleyRatio = pulleyTeeth / motorTeeth;
const long stepsPerRev = 200 * pulleyRatio * microStep;
const long stepsPerDeg = stepsPerRev / 360;
const float stepsPerMM = (5.0 * microStep) / 2;
const float distPerStepRot = 1.0 / stepsPerDeg;
const float distPerStepLin = 1.0 / stepsPerMM;

// Pin Defs
const int rotDirPin = 13; // port PC6 PORTD // changed to 5 from 4
const int rotStepPin = 14; // port PF5 PORTD // changed to 18 from 3
const int linDirPin = 12; // port PA0 PORTD
const int linStepPin = 27; // port PB0 PORTB //changed from 15
