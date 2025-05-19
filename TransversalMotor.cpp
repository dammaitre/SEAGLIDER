#include "AccelStepper.h"

#include "TransversalMotor.h"


TransversalMotor::TransversalMotor(const int dirPin, const int stpPin, const int spd, const int maxFDCPin, const int minFDCPin) {
    /// Initialisation : calcul l'interval de course, donc ça peut prendre un peu de temps
    /// dirPin & stpPin : pins de controle du driver ; maxFDCPin et minFDCPin : capteurs de fin de course

    this->dirPin = dirPin;
    this->stpPin = stpPin;   

    this->cruisespd = spd;

    this->maxFDCPin = maxFDCPin;
    this->minFDCPin = minFDCPin;
    pinMode(this->maxFDCPin, INPUT);
    pinMode(this->minFDCPin, INPUT);

    this->stepper = new AccelStepper(this->MOTORINTERFACETYPE, this->stpPin, this->dirPin);
    stepper->setMaxSpeed(1000);
    // Calcul de la course
    Serial.println("===== CALIBRAGE COURSE BALLAST =====");
    Serial.println("\t== Remplissage ==");
  
    this->stepper->setSpeed(this->cruisespd);
    int val = digitalRead(this->maxFDCPin);
    while (val == HIGH) {
      val = digitalRead(this->maxFDCPin);
      this->stepper->runSpeed();
    }
    this->posMax = (float) this->stepper->currentPosition();
    Serial.println(this->posMax);
  
        //de-bouncing
    this->stepper->setSpeed(-this->cruisespd);
    while (val == LOW) {
      val = digitalRead(this->maxFDCPin);
      this->stepper->runSpeed();
    }
  
    Serial.println("\t== vidange ==");
  
    while (val == HIGH) {
      val = digitalRead(this->minFDCPin);
      this->stepper->runSpeed();
    }
    this->posMin = (float) this->stepper->currentPosition();
    Serial.println(this->posMin);
    
        //de-boucning dans l'autre sens
    this->stepper->setSpeed(this->cruisespd);
    while (val == LOW) {
      val = digitalRead(this->minFDCPin);
      this->stepper->runSpeed();
    }
  
    this->posZero = (float) (this->posMax + this->posMin)/2;
  
    this->stepper->moveTo(this->posZero);
    while (this->stepper->distanceToGo() > 0) {
      this->stepper->setSpeed(500);
      this->stepper->run();
    }

    Serial.println("===== fin calibrage =====\n");
    this->status = 0;

    return;
}


bool TransversalMotor::Goto(float d){
    /// d entre 0 et 1.
    /// Utilisation : \n \t mtr->Goto(0.5); \n \t mtr->move(); //dans la loop
    if (d < 0 || d > 1) {
        Serial.println("\t\tERREUR : chef 0<=d<=1");
        return false;
    }

    if (d < this->GetCurrentRelativePos()) {
        this->status = -1;
    }
    else {
        this->status = 1;
    }
    this->spd = this->cruisespd * this->status;

    this->stepper->moveTo( int(this->posMin + d*(this->posMax - this->posMin) ));
    Serial.println("\tBallast : commandé");
    Serial.println(int(this->posMin + d*(this->posMax - this->posMin) ));
    return true;
}


bool TransversalMotor::Move() {
    /// A appeler systématiquement dans le loop. Renvoie true quand la position est atteinte.
    if (this->status == 0) {
        return true;
    }
    else {
        this->stepper->setSpeed(this->spd);
        this->stepper->run();

        if (this->stepper->distanceToGo() == 0) {
            this->status = 0;
            this->spd = 0;

            Serial.println("STOP");

            return true;
        }

        return false;
    }

}

float TransversalMotor::GetCurrentRelativePos() {
    return ((float) this->stepper->currentPosition()-this->posMax)/(this->posMin - this-> posMax);
}


