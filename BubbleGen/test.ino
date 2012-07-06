#include <Servo.h>
#include <Stepper.h>

/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
#define fanPin 4
#define servoPin 7

#define pwmA 3
#define pwmB 11
#define brakeA 9
#define brakeB 8
#define dirA 12
#define dirB 13

// Servo boundry values
const int arm_open_pos = 3;
const int arm_closed_pos = 180;

const int stepsPerRevolution = 50;  // change this to fit the number of steps per revolution
                                    // for your motor
 
Stepper myStepper(stepsPerRevolution, dirA, dirB);
Servo bubbleArm;

void setup() {                
  // initialize the digital pin as an output.
  // Pin 13 has an LED connected on most Arduino boards:
  pinMode(fanPin, OUTPUT);
  bubbleArm.attach(servoPin);  
  bubbleArm.write(arm_closed_pos);

 // set the PWM and brake pins so that the direction pins  // can be used to control the motor:
 pinMode(pwmA, OUTPUT);
 pinMode(pwmB, OUTPUT);
 pinMode(brakeA, OUTPUT);
 pinMode(brakeB, OUTPUT);
 digitalWrite(pwmA, LOW);
 digitalWrite(pwmB, LOW);
 digitalWrite(brakeA, LOW);
 digitalWrite(brakeB, LOW);
 
 // initialize the serial port:
 Serial.begin(9600);
 // set the motor speed (for multiple steps only):
 myStepper.setSpeed(240);
}

void loop() {
//  Stepper Test
stepperTest();

//  Fan Test
//  fanTest();

//  Servo Test
//  servoTest();
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
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  digitalWrite(pwmA, LOW);
  digitalWrite(pwmB, LOW);

  delay(1000);
}

