#include "accelbrain.h"
#include <Wire.h>
#include <LSM303.h>

#include <math.h>

AccelBrain::AccelBrain() {
    Serial.println(" ===== INITIALISATION CENTRALE INERTIELLE =====");
    Wire.begin();

    this->compass = new LSM303;
    this->compass->init();
    this->compass->enableDefault();

    this->zero = new long int[3];
    this->stdzero = new double[3];

    delay(2000);

    return;
}


void AccelBrain::Calibrate() {
    /// A appeler sur un SEAGLIDER immobile : calcule le zéro positionnel autour duquel équilibrer.

    
    // Calcul des zéros : Espérance et std du signal bruité
    const int stepTime = 50;

    // On calcule simplement E = sum/n puis std = sqrt(E² - sqrdsum/n) 
    // Dans l'ordre de ces deux tableaux : accélérations x, y, z puis angles x, y, z
    long int sum[6] = {0, 0, 0, 0, 0, 0};
    long int sqrdsum[6] = {0, 0, 0, 0, 0, 0};

    Serial.println(" === Calibration de la centrale inertielle ===");

    int N = this->calibrationTime/stepTime; // 100 dans les para normaux

    for (int k = 0; k < N; k++) {
        this->compass->read();

        sum[0] += this->compass->a.x;
        sum[1] += this->compass->a.y;
        sum[2] += this->compass->a.z;
        sum[3] += this->compass->m.x;
        sum[4] += this->compass->m.y;
        sum[5] += this->compass->m.z;

        sqrdsum[0] += this->compass->a.x * this->compass->a.x;
        sqrdsum[1] += this->compass->a.y * this->compass->a.y;
        sqrdsum[2] += this->compass->a.z * this->compass->a.z;
        sqrdsum[3] += this->compass->m.x * this->compass->m.x;
        sqrdsum[4] += this->compass->m.y * this->compass->m.y;
        sqrdsum[5] += this->compass->m.z * this->compass->m.z;

        delay(stepTime);
    }

    for (int i = 0; i < 6; i++) {
        this->zero[i] = sum[i]/N;
        this->stdzero[i] = sqrt( (sqrdsum[i]/N)  - (this->zero[i]*this->zero[i]) );
    }



    // Affichage du tableau
    char report[200];
    snprintf(report, sizeof(report), "A: %d %d %d    M: %d %d %d",
    this->zero[0], this->zero[1], this->zero[2],
    this->zero[3], this->zero[4], this->zero[5]);
    Serial.println(report);


    snprintf(report, sizeof(report), "A: %d %d %d    M: %d %d %d",
    this->stdzero[0], this->stdzero[1], this->stdzero[2],
    this->stdzero[3], this->stdzero[4], this->stdzero[5]);
    Serial.println(report);

    return;
}


int AccelBrain::GetZOrder() {
    /// 1 entier qui détermine ce que le SG doit faire pour suivre l'équilibre
    /// L'équilibre du SG est actuellement uniquement déterminé par Calibrate(), donc pas possible de le faire bouger.
    /// TODO : faire une méthode pour lui demander un nouvel équilibre, contrôlé en position/accélération/vitesse
    /// -1 : DOWN ! 0 : STEADY, 1 : UP !

    return 0;
}

void AccelBrain::ReadAccel() {
    char report[200];
    this->compass->read();

    snprintf(report, sizeof(report), "A: %d %d %d    M: %d %d %d",
      this->compass->a.x, this->compass->a.y, this->compass->a.z,
      this->compass->m.x, this->compass->m.y, this->compass->m.z);
    Serial.println(report);
}