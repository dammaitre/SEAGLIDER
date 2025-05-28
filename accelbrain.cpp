#include "accelbrain.h"
#include <Wire.h>
#include <LSM303.h>

#include <math.h>

AccelBrain::AccelBrain() {
    Serial.prinln(" ===== INITIALISATION CENTRALE INERTIELLE =====");
    Wire.begin();

    this->compass = new LSM303;
    this->compass->init();
    this->compass->enableDefault();

    this->zeroA = new float[3];
    this->stdzeroA = new float[3];

    this->zeroM = new float[3];
    this->stdzeroM = new float[3];

    this->Calibrate();

    return;
}


void AccelBrain::Calibrate() {
    /// A appeler sur un SEAGLIDER immobile : calcule le zéro positionnel autour duquel équilibrer.

    
    // Calcul des zéros : Espérance et std du signal bruité
    const int stepTime = 10;

    // On calcule simplement E = sum/n puis std = sqrt(E² - sqrdsum/n) 
    // Dans l'ordre de ces deux tableaux : accélérations x, y, z puis angles x, y, z
    float* sum = {0., 0., 0., 0., 0., 0.};
    float* sqrdsum = {0., 0., 0., 0., 0., 0.};

    Serial.println(" === Calibration de la centrale inertielle ===")

    int N = this->calibrationTime/stepTime; // 100 dans les para normaux

    for (int _ = 0; _ < this->N; _++) {
        this->compass.read();

        sum[0] += this->compass.a.x;
        sum[1] += this->compass.a.y;
        sum[2] += this->compass.a.z;
        sum[3] += this->compass.m.x;
        sum[4] += this->compass.m.y;
        sum[5] += this->compass.m.z;

        sqrdsum[0] += this->compass.a.x * this->compass.a.x;
        sqrdsum[1] += this->compass.a.y * this->compass.a.y;
        sqrdsum[2] += this->compass.a.z * this->compass.a.z;
        sqrdsum[3] += this->compass.m.x * this->compass.m.x;
        sqrdsum[4] += this->compass.m.y * this->compass.m.y;
        sqrdsum[5] += this->compass.m.z * this->compass.m.z;

        delay(stepTime);
    }

    for (int i = 0; i < 6; i++) {
        this->zero[i] = sum[i]/N;
        this->stdzero[i] = sqrt( mean[i]*mean[i] - (sqrdsum[i]/N) );
    }

    // Affichage du tableau
    char report[80];
    snprintf(report, sizeof(report), "A: %6d %6d %6d    M: %6d %6d %6d",
    this->zero[0], this->zero[1], this->zero[2],
    this->zero[3], this->zero[4], this->zero[5]);
    Serial.println(report);

    return;
}
