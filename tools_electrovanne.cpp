#include <Arduino.h>
#include "tools_electrovanne.h"

bool bool_ballast = false;  // initialisation

void setupElectrovanne() {
    pinMode(RELAY_PIN, OUTPUT);
}

void Vanne(bool etat) {
    if (etat) {
        digitalWrite(RELAY_PIN, HIGH);
    } else {
        digitalWrite(RELAY_PIN, LOW);
    }
}