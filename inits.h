struct PathPoint {    // Definition of each point in a pattern's path
  float rotSteps;     // number of rotational steps
  float linSteps;     // number of linear steps
  float rotCmr;       // rotation interrupt CMR value
  float linCmr;       // linear interrupt CMR value
  float rotAcc;       // rotational acceleration 
  float linAcc;       // linear acceleration
};

PathPoint currPoint = {0,0,100000,100000,0,0};  // initialize current and next points
PathPoint nextPoint = {0,0,100000,100000,0,0};  //

// Position variables
float currLin = 0;            // current linear position
float currRot = 0;            // current rotational position
float currOffset = 0;         // current offset factor
bool isHomed = false;         // whether or not homing has been done
bool homedFlag = false;       // whether or not home has been found
bool homingStarted = false;   // whether or not homing is in progress

int manPointNum = 1;          //
int pNum = 0;                 //
int pNumCompleted = 0;        //

// file variables 
float path[2000][5];          // empty array to insert the next path in to
long fileLength;              // number of points in the path
int offsetAngle = 0;          // angle to offset the path by each time

// next move planning
bool builtNextMove = false;   // whether or not the next move has been successfully built
bool moveRot = false;         // whether or not to move the rotational axis yet
bool moveLin = false;         // whether or not to move the linear axis yet 
bool moveStartedRot;          // whether or not the rotational axis move is in progress
bool moveStartedLin;          // whether or not the linear axis move is in progress 
float timeStep;               // the amount of time the next point is supposed to take for its move

// Timing variables  
const long clockHz = 80000000;                                                  // frequency of the processory
const long microS = 1000000;                                                    // how many microseconds for Something
const long prescalar = 256;                                                     // CMR prescalar
const long stepLengthLimit = 15000;                                             // maximum length of the step interrupt
const long cmrLimit = round(clockHz/(prescalar*(microS / stepLengthLimit)))-1;  // how high the interrupt can count
bool stepPulseRot = true;                                                       // Toggle flag for step pulses, always starts high at the beginning of a move
bool stepPulseLin = true;                                                       //
long stepCountRot;                                                              // Counter for the number of pulses for that move
long stepCountLin;                                                              //

// Motion parameters
const long microStep = 16;                                                      // all of this is pretty self explanatory
const long pulleyTeeth = 126;                                                   //
const long motorTeeth = 20;                                                     //
const float pulleyRatio = pulleyTeeth / motorTeeth;                             //
const float stepsPerRev = 200 * pulleyRatio * microStep;                        //
const float rotCorrectionFactor = 1.052;                                        //
const float stepsPerDeg = (stepsPerRev / 360.0) * rotCorrectionFactor;          //
const float linCorrectionFactor = 200.0/214.3;                                  //
const float stepsPerMM = (5.0 * float(microStep)) * linCorrectionFactor;        //
//const float stepsPerMM = 74;                                                  //
const float distPerStepRot = 1.0 / stepsPerDeg;                                 //
const float distPerStepLin = 1.0 / stepsPerMM;                                  //

// Pin Defs
const int rotDirPin = 13;                                                       // port PC6 PORTD // changed to 5 from 4
const int rotStepPin = 14;                                                      // port PF5 PORTD // changed to 18 from 3
const int linDirPin = 12;                                                       // port PA0 PORTD
const int linStepPin = 27;                                                      // port PB0 PORTB //changed from 15
const int linLimitPin = 26;
