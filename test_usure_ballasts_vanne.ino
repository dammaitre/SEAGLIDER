/* Test : plusieurs vidanges/remplissages du ballast*/

#include "TransversalMotor.h"

TransversalMotor* ballast;

void setup() {
    Serial.begin(9600);
    while (!Serial) {
        delay(10);
    }

    delay(800);
    Serial.println("SEAGLIDER OPERATIONNEL")

    ballast = new TransversalMotor(8, 9, 500, 5, 4);
  }

  

