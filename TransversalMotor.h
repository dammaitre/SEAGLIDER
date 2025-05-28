/// Classe mère des ballasts et de la masselotte de tangage.

#include "AccelStepper.h"


class TransversalMotor {
public:
    TransversalMotor(int dirPin, int stpPin, int spd,
                    int maxFDCPin, int minFDCPin);

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
    bool estEnTrainDeGalerer;

    const int MOTORINTERFACETYPE = 1;

    AccelStepper* stepper;

    
};