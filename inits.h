
String fileName;
float currLin;
float currRot;
int fileLength;

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
long cmrRotAcc;
long cmrLinAcc;
bool moveRot = false;
bool moveLin = false;

// Timing variables
// compare match register = [16,000,000 / (prescaler * time delay) ] -1
long clockHz = 16000000;
long microS = 1000000;
long preSclr = 256;
long cmrRot;
long cmrLin;
bool stepPulseRot = true;
bool stepPulseLin = true;

// Motion parameters
long microStep = 16;
long pulleyTeeth = 126;
long motorTeeth = 20;
float pulleyRatio = pulleyTeeth / motorTeeth;
long stepsPerRev = 200 * pulleyRatio * microStep;
long stepsPerDeg = stepsPerRev / 360;
float stepsPerMM = (5.0 * microStep) / 2;
float distPerStepRot = 1.0 / stepsPerDeg;
float distPerStepLin = 1.0 / stepsPerMM;

// Pin Defs

int dirPin1 = 4; // port PC6 PORTD
int stepPin1 = 3; // port PF5 PORTD
int dirPin2 = 2; // port PA0 PORTD
int stepPin2 = 9; // port PB0 PORTB
int enablePin1 = 8; // port PE3 PORTB
