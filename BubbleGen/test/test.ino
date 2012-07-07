#include <Servo.h>
#include <Stepper.h>

const int fanPin =   4;  // Pin for controlling the bubble blowing CPU fan
const int servoPin = 7;  // Pin for controlling the bubble arm servo motor

const int lowerBoundrySwitch =  2; // Input pin for the switch signalling the lower boundary of the shelf
const int upperBoundrySwitch = 10; // Input pin for the switch signalling the upper boundary of the shelf

// Pins used by the Arduino Motor Shield
// The Motor Shield controlls the stepper motor used for raising and lowering the shelf
const int pwmA =    3;
const int pwmB =   11;
const int brakeA =  9;
const int brakeB =  8;
const int dirA =   12;
const int dirB =   13;

// Servo boundry values
const int arm_open_pos = 3;
const int arm_closed_pos = 180;

const int stepsPerRevolution = 50;  // change this to fit the number of steps per revolution
                                    // for your motor
 
Stepper myStepper(stepsPerRevolution, dirA, dirB);
Servo bubbleArm;

void setup() {                
  pinMode(fanPin, OUTPUT);
  bubbleArm.attach(servoPin);  
  bubbleArm.write(arm_closed_pos);

  motorShieldSetup();
 
  // set the motor speed (for multiple steps only):
  myStepper.setSpeed(240);
}

void loop() {
  // Stepper Test
  stepperTest();

  // Fan Test
  // fanTest();

  // Servo Test
  // servoTest();
}

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
void fanTest(){
  digitalWrite(fanPin, HIGH);   // set the LED on
  delay(5000);              // wait for a second
  digitalWrite(fanPin, LOW);    // set the LED off
  delay(5000);              // wait for a second
}

void servoTest(){
  int pos;
  for (pos = arm_closed_pos; pos > 180; pos += 1) {
    bubbleArm.write(pos);
    delay(30);
  }
  delay(2000);
  for (pos = 180; pos > arm_closed_pos; pos -= 1) {
    bubbleArm.write(pos);
    delay(30);
  }
  delay(2000);
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

