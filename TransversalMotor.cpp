#include "Accelthis->stepper.h"
#include <stdlib>

#include "TransversalMotor.h"

TransversalMotor::TransversalMotor(const int dirPin, const int stpPin, const int spd) {
    /// Initialisation : calcul l'interval de course, donc ça peut prendre un peu de temps
    this->dirPin = dirPin;
    this->stpPin = stpPin;
    this->spd = spd;
    int maxFDCPin = maxFDCPin;
    int minFDCPin = minFDCPin;

    this->stepper = new Accelthis->stepper(this->MOTORINTERFACETYPE, this->stpPin, this->dirPin);

    // Calcul de la course
    Serial.println("===== CALIBRAGE COURSE BALLAST =====");
    Serial.println(" == Remplissage ==");
  
    this->stepper.setSpeed(500);
    while (val == HIGH) {
      val = digitalRead(topCrashBallast);
      this->stepper.runSpeed();
    }
    MAX_BALLAST = this->stepper.currentPosition();
    Serial.println(MAX_BALLAST);
  
    this->stepper.setSpeed(-500);
    while (val == LOW) {
      val = digitalRead(topCrashBallast);
      this->stepper.runSpeed();
    }
  
    Serial.println(" == vidange ==");
  
    while (val == HIGH) {
      val = digitalRead(topCrashBallast);
      this->stepper.runSpeed();
    }
    MIN_BALLAST = this->stepper.currentPosition();
    Serial.println(MIN_BALLAST);
    
    this->stepper.setSpeed(500);
    while (val == LOW) {
      val = digitalRead(topCrashBallast);
      this->stepper.runSpeed();
    }
  
    ZERO_BALLAST = int( (MAX_BALLAST + MIN_BALLAST)/2);
  
    this->stepper.moveTo(ZERO_BALLAST);
    while (this->stepper.distanceToGo() > 0) {
      this->stepper.setSpeed(500);
      this->stepper.run();
    }
    delay(1000);
}
