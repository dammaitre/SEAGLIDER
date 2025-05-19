/* Test : plusieurs vidanges/remplissages du ballast*/

#include "TransversalMotor.h"

TransversalMotor* ballast;

void setup() {
    Serial.begin(9600);
    while (!Serial) {
        delay(10);
    }

    delay(800);
    Serial.println("SEAGLIDER OPERATIONNEL");

    ballast = new TransversalMotor(2, 3, 400, 5, 4);
    ballast->Goto(.9);
  }

void loop() {
    //Remplissage
    ballast->Move();
}

