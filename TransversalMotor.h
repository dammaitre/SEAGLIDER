// Classe mère des ballasts et de la masselotte de tangage.

#include "AccelStepper.h"
#include <stdlib>


class TransversalMotor {
public:
    TransversalMotor(const int dirPin, const int stpPin, const int spd,
                    const int maxFDCPin, const int minFDCPin);

    bool Goto(float d);

    void Move();

    int GetStatus();

private:
    int posMin;
    int posMax;

    int spd;

    int dirPin;
    int stpPin;

    int maxFDCPin;
    int minFDCPin;

    const int MOTORINTERFACETYPE = 1;

    AccelStepper* stepper;

    void ForceMove();
}