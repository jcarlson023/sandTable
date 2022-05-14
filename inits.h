struct PathPoint {
  float rotSteps;
  float linSteps;
  float rotCmr;
  float linCmr;
  float rotAcc;
  float linAcc;
};

PathPoint currPoint = {0,0,100000,100000,0,0};
PathPoint nextPoint = {0,0,100000,100000,0,0};

// Position variables
float currLin = 0;
float currRot = 0;
float currOffset = 0;
bool isHomed = false;
bool homingStarted = false;

int manPointNum = 1;
int pNum = 0;
int pNumCompleted = 0;

// file variables
float path[2000][5];
String fileName;
int fileLength;
int offsetAngle = 0;

// next move planning
bool builtNextMove = false;
bool moveRot = false;
bool moveLin = false;
bool moveStartedRot;
bool moveStartedLin;
float timeStep;

// Timing variables  
const long clockHz = 80000000;
const long microS = 1000000;
const long prescalar = 256;
const long stepLengthLimit = 6000;
const long cmrLimit = round(clockHz/(prescalar*(microS / stepLengthLimit)))-1;
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
const float rotCorrectionFactor = 1.052;
const float stepsPerDeg = (stepsPerRev / 360.0) * rotCorrectionFactor;
const float linCorrectionFactor = 200.0/214.3;
const float stepsPerMM = (5.0 * float(microStep)) * linCorrectionFactor;
//const float stepsPerMM = 74;
const float distPerStepRot = 1.0 / stepsPerDeg;
const float distPerStepLin = 1.0 / stepsPerMM;

// Pin Defs
const int rotDirPin = 13; // port PC6 PORTD // changed to 5 from 4
const int rotStepPin = 14; // port PF5 PORTD // changed to 18 from 3
const int linDirPin = 12; // port PA0 PORTD
const int linStepPin = 27; // port PB0 PORTB //changed from 15
const int linLimitPin = 26;
