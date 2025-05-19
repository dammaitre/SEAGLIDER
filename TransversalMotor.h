/// Classe mère des ballasts et de la masselotte de tangage.

#include "AccelStepper.h"
#include <stdlib>


class TransversalMotor {
public:
    TransversalMotor(const int dirPin, const int stpPin, const int spd,
                    const int maxFDCPin, const int minFDCPin);

    bool Goto(float d);

    bool Move();

    int GetStatus();

    float GetCurrentRelativePos();

private:
    float posMin;
    float posMax;
    float posZero;

    int spd;
    int cruisespd;

    int dirPin;
    int stpPin;

    int maxFDCPin;
    int minFDCPin;

    int status;
    // 0: Sleeping, 1: Moving up, -1: Moving down

    const int MOTORINTERFACETYPE = 1;

    AccelStepper* stepper;

    
}