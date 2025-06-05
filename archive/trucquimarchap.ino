/* Test : plusieurs vidanges/remplissages du ballast*/
#include <Wire.h>
#include <LSM303.h>


#include "TransversalMotor.h"
#include "accelbrain.h"
#include "tools_electrovanne.h"

TransversalMotor* ballast;
TransversalMotor* mslttTangage;
AccelBrain* pilot;

void setup() {
    
    Serial.begin(9600);
    while (!Serial) {
        delay(10);
    }

    delay(800);
    Serial.println("SEAGLIDER OPERATIONNEL");

    Serial.println("Entrée dans setup");
    
    // Initialisation du ballast
    ballast = new TransversalMotor(2, 3, 400, 5, 4);
    ballast->Goto(.9);

    // Initialisation de la masselotte de tangage
    //mslttTangage = new TransversalMotor(6, 7, 600, 8, 9);
    //mslttTangage->Goto(.9);



    //pilot = new AccelBrain();
    //pilot->Calibrate();

}

bool whatballast = true;
bool whatmsslt = true;
int step = 0;

void loop() {
    Serial.println("Entré dans la loop");
    // Remplissage
    step++;

    if (ballast->Move()) {
        if (whatballast) {
            ballast->Goto(.9);
        }
        else {
            ballast->Goto(.1);
        }
        whatballast = !whatballast;
    }

    if (mslttTangage->Move()) {
        if (whatmsslt) {
            mslttTangage->Goto(.9);
        }
        else {
            mslttTangage->Goto(.1);
        }

        whatmsslt = !whatmsslt;
    }

}

