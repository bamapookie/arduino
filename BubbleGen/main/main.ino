#include <Servo.h>
#include <Stepper.h>

// *** Software Configuration ***

// Servo boundry values
const int armOpenPos = 3;
const int armClosedPos = 180;

// Stepper motor settings
const int shelfMotorSpeed = 240;

// *** Hardware Configuration ***

// Configuration for the rh7-1403 stepper
const int shelfStepsPerRevolution = 50;

// Pin Configuration
const int blowerFanPin =   4;  // Pin for controlling the bubble blowing CPU fan
const int armServoPin = 7;  // Pin for controlling the bubble arm servo motor

const int shelfLowerBoundarySwitch =  2; // Input pin for the switch signalling the lower boundary of the shelf
const int shelfUpperBoundarySwitch = 10; // Input pin for the switch signalling the upper boundary of the shelf

// Pins used by the Arduino Motor Shield
// The Motor Shield controlls the stepper motor used for raising and lowering the shelf
const int pwmA =    3;
const int pwmB =   11;
const int brakeA =  9;
const int brakeB =  8;
const int dirA =   12;
const int dirB =   13;

// State values
const int stateResetting = -1; // Stationary
const int stateReset     =  0; // Stationary
const int stateDipping   =  1; // Transition
const int stateDown      =  2; // Stationary
const int stateRaising   =  3; // Transition
const int stateUp        =  4; // Stationary
const int stateOpening   =  5; // Transition
const int stateOpened    =  6; // Stationary
const int stateBlowing   =  7; // Stationary
const int stateClosing   =  8;
const int stateClosed    =  0; // Stationary, same as reset

Stepper shelfStepper = new Stepper(stepsPerRevolution, dirA, dirB);
Servo armServo;
int state = stateReseting;

void setup() {                
  pinMode(blowerFanPin, OUTPUT);
  armServo.attach(armServoPin);
  pinMode(shelfLowerBoundarySwitch, INPUT); 
  pinMode(shelfUpperBoundarySwitch, INPUT); 

  motorShieldSetup();
  shelfStepper.setSpeed(shelfMotorSpeed);
  
  reset();
}

void loop() {
  if (isAutomatic()) {
    autoMode();
  } else {
    manualMode();
  }  
}

void reset() {
  
  digitalWrite(blowerFanPin, LOW);
  while (!digitalRead(shelfUpperBoundarySwitch)) {
    shelfUp();
  }
  armServo.write(armClosedPos);
}

boolean isAutomatic() {
  // TODO Replace this with actual check when manual mode is implemented.
  return true;
}

void autoMode() {
  
}

void manualMode() {
  // TODO Implement this.
}


/*
 * Setup methods.
 */

void motorShieldSetup() {
  // set the PWM and brake pins so that the direction pins can be used to control the motor:
  pinMode(pwmA, OUTPUT);
  pinMode(pwmB, OUTPUT);
  pinMode(brakeA, OUTPUT);
  pinMode(brakeB, OUTPUT);
  digitalWrite(pwmA, LOW);
  digitalWrite(pwmB, LOW);
  digitalWrite(brakeA, LOW);
  digitalWrite(brakeB, LOW);
}

void stepperTest(){
  digitalWrite(pwmA, HIGH);
  digitalWrite(pwmB, HIGH);
  for (int i = 0; i < 100; i++) {
    myStepper.step(2);
  }
  digitalWrite(pwmA, LOW);
  digitalWrite(pwmB, LOW);

  delay(1000);
  digitalWrite(pwmA, HIGH);
  digitalWrite(pwmB, HIGH);
  for (int i = 0; i < 100; i++) {
    myStepper.step(-2);
  }
  digitalWrite(pwmA, LOW);
  digitalWrite(pwmB, LOW);

  delay(1000);
}

