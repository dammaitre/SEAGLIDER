#include <Wire.h>
#include <LSM303.h>

class AccelBrain {
    /// Centrale inertielle du prototype
public:
    AccelBrain();

    void Calibrate();

    int GetZOrder();

    void ReadAccel();

private:
    LSM303* compass;

    const int calibrationTime = 5000;

    long int* zero;
    double* stdzero;
};