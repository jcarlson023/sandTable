
// next move planning
long nextStepsRot;
long nextStepsLin;
float nextRotAct;
float nextLinAct;
long nextCmrRot;
long nextCmrLin;
long nextPrescalarRot;
long nextPrescalarLin;

// curr move planning
long stepsRot;
long stepsLin;
long stepCountRot;
long stepCountLin;
bool moveRot = false;
bool moveLin = false;
bool moveStarted = false;
float currRot;
float currLin;

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
float microStep = 16.0;
float pulleyTeeth = 126.0;
float motorTeeth = 20.0;
float pulleyRatio = pulleyTeeth / motorTeeth;
float stepsPerRev = 200.0 * pulleyRatio * microStep;
float stepsPerDeg = stepsPerRev / 360.0;
float stepsPerMM = 5.0 * microStep;
float distPerStepRot = 1.0 / stepsPerDeg;
float distPerStepLin = 1.0 / stepsPerMM;

// Pin Defs
int dirPin1 = 4;
int stepPin1 = 3;
int dirPin2 = 2;
int stepPin2 = 9;
int enablePin1 = 8;
