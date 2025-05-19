/*
  Example sketch to control a stepper motor with A4988 stepper motor driver, 
  AccelStepper library and Arduino: continuous rotation. 
  More info: https://www.makerguides.com 
*/

// Include the AccelStepper library:
#include "AccelStepper.h"

// Define stepper motor connections and motor interface type. 
// Motor interface type must be set to 1 when using a driver
#define dirPin 8
#define stepPin 9
#define motorInterfaceType 1

#define topCrashBallast 5


int ZERO_BALLAST;
int MAX_BALLAST;
int MIN_BALLAST;

// Create a new instance of the AccelStepper class:
AccelStepper stepper = AccelStepper(motorInterfaceType, stepPin, dirPin);

int spd;

void setupBall() {
  int val = digitalRead(topCrashBallast);
  Serial.println(" ==== CALIBRAGE COURSE BALLASTS ====");

  Serial.println(" == plein ==");
  Serial.println(stepper.currentPosition());

  stepper.setSpeed(500);
  while (val == HIGH) {
    val = digitalRead(topCrashBallast);
    stepper.runSpeed();
  }
  MAX_BALLAST = stepper.currentPosition();
  Serial.println(MAX_BALLAST);

  stepper.setSpeed(-500);
  while (val == LOW) {
    val = digitalRead(topCrashBallast);
    stepper.runSpeed();
  }

  Serial.println(" == vidange ==");

  while (val == HIGH) {
    val = digitalRead(topCrashBallast);
    stepper.runSpeed();
  }
  MIN_BALLAST = stepper.currentPosition();
  Serial.println(MIN_BALLAST);
  
  stepper.setSpeed(500);
  while (val == LOW) {
    val = digitalRead(topCrashBallast);
    stepper.runSpeed();
  }

  ZERO_BALLAST = int( (MAX_BALLAST + MIN_BALLAST)/2);

  stepper.moveTo(ZERO_BALLAST);
  while (stepper.distanceToGo() > 0) {
    stepper.setSpeed(500);
    stepper.run();
  }
  delay(1000);


}

void setup() {
  // Set the maximum speed in steps per second:
  stepper.setMaxSpeed(1000);
  Serial.begin(9600);
  pinMode(topCrashBallast, INPUT);

  setupBall();
}


void loop() {
  // Set the speed in steps per second:
  //stepper.setSpeed(spd);
  // Step the motor with a constant speed as set by setSpeed():
  //stepper.runSpeed();

    // read input value
  /* if (val == LOW) {          
    Serial.println("Switch Pressed!");      // check if the input is HIGH   // turn LED OFF
    spd = -spd;
    delay(100);
  } */
}