/* Test : plusieurs vidanges/remplissages du ballast*/
#include <Wire.h>
#include <LSM303.h>


#include "TransversalMotor.h"
#include "tools_electrovanne.h"

TransversalMotor* ballast;
TransversalMotor* mslttTangage;

void setup() {
    Serial.begin(9600);
    while (!Serial) {
        delay(10);
    }

    delay(800);
    Serial.println("SEAGLIDER OPERATIONNEL");

    // Initialisation du ballast
    ballast = new TransversalMotor(2, 3, 200, 5, 4);
    ballast->Goto(.9);

    // Initialisation de la masselotte de tangage
    mslttTangage = new TransversalMotor(0, 0, 100, 0, 0);

    // Initialisation de la vanne
    setupElectrovanne();

    // 

}

int step = 0;

void loop() {
    //Remplissage
    if (step <= 200 && ballast->Move()) {
        Serial.print("step : ");
        Serial.println(step);
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

