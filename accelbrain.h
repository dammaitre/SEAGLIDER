#include <Wire.h>
#include <LSM303.h>

class AccelBrain {
    /// Centrale inertielle du prototype
public:
    AccelBrain();

    void Calibrate();

private:
    LSM303* compass;

    const int calibrationTime = 1000;

    float* zero;
    float* stdzero;
}