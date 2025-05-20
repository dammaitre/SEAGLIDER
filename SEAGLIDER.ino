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

int step = 0;

void loop() {
    //Remplissage
    if (step <= 200 && ballast->Move()) {
        step++;
        if (step % 2 == 0) {
            ballast->Goto(.9);
        }
        else {
            ballast->Goto(.1);
        }
    }
    else if (step == 200) {
        Serial.println("TEST FINI !");
        step++;
    }
}

