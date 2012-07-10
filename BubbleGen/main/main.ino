#include <Servo.h>
#include <Stepper.h>

// *** Software Configuration ***

// Servo boundry values
const int armOpenPos = 80; // These should change.  Open position must be less than closed position, or the logic in the open and close methods needs to change.
const int armClosedPos = 100;

// Stepper motor settings
const int shelfMotorSpeed = 240;

// Bubble settings
const int bubblesPerCycle = 3;

// *** Hardware Configuration ***

// Max and min positions of the servo
const int armMinPos = 3;
const int armMaxPos = 180;

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
const int stateResetting = -1; // Transition
const int stateReset     =  0; // Stationary
const int stateDipping   =  1; // Transition
const int stateDown      =  2; // Stationary
const int stateRaising   =  3; // Transition
const int stateUp        =  4; // Stationary
const int stateOpening   =  5; // Transition
const int stateOpen      =  6; // Stationary
const int stateBlowing   =  7; // Stationary
const int stateClosing   =  8;
const int stateClosed    =  0; // Stationary, same as reset

Stepper shelfStepper(shelfStepsPerRevolution, dirA, dirB);
Servo armServo;
int state = stateResetting;
int bubbleCount = 0;

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
  state = stateResetting;
  digitalWrite(blowerFanPin, LOW);
  while (shelfUp()) {}
  state = stateReset;
}

boolean isAutomatic() {
  // TODO Replace this with actual check when manual mode is implemented.
  return true;
}

void autoMode() {
  while(isAutomatic()) {
    switch(state) {
      case stateResetting:
        reset();
        break;
      case stateReset:
        delay(500);
        state = stateDipping;
        break;
      case stateDipping:
        shelfDown();
        break;
      case stateDown:
        delay(3000);
        state = stateRaising;
        break;
      case stateRaising:
        shelfUp();
        break;
      case stateUp:
        delay(500);
        state = stateOpening;
        break;
      case stateOpening:
        armOpen();
        bubbleCount = 0;
        break;
      case stateOpen:
        delay(500);
        bubbleCount++;
        if (bubbleCount > bubblesPerCycle) {
          state = stateClosing;
        } else {
          state = stateBlowing;
        }
        break;
      case stateBlowing:
        fanOn();
        delay(500);
        fanOff();
        delay(500);
        break;
      case stateClosing:
        armClose();
        break;
      default:
      // Error
        break;
    }
  }
}

void manualMode() {
  // TODO Implement this.
}

/*
 * Movement methods
 */

boolean shelfUp() {
  if (digitalRead(shelfUpperBoundarySwitch)) {
    digitalWrite(pwmA, LOW);
    digitalWrite(pwmB, LOW);
    state = stateUp;
    return false;
  } else {
    digitalWrite(pwmA, HIGH);
    digitalWrite(pwmB, HIGH);
    shelfStepper.step(1);
    return true;
  }
}

boolean shelfDown() {
  if (digitalRead(shelfLowerBoundarySwitch)) {
    digitalWrite(pwmA, LOW);
    digitalWrite(pwmB, LOW);
    state = stateDown;
    return false;
  } else {
    digitalWrite(pwmA, HIGH);
    digitalWrite(pwmB, HIGH);
    shelfStepper.step(-1);
    return true;
  }
}

void armOpen() {
  if (armServo.read() <= armOpenPos) {
    state = stateOpen;
  } else {
    state = stateOpening;
    armServo.write(armOpenPos);
  }
}

void armClose() {
  if (armServo.read() >= armClosedPos) {
    state = stateClosing;
  } else {
    state = stateClosed;
    armServo.write(armClosedPos);
  }
}

void fanOn() {
  state = stateBlowing;
  digitalWrite(blowerFanPin, HIGH);
}

void fanOff() {
  digitalWrite(blowerFanPin, LOW);
  state = stateOpen;
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

