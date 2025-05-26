#ifndef TOOLS_electrovanne_H
#define TOOLS_electrovanne_H

const int RELAY_PIN = 4; // pin de commande du relai de la vanne
extern bool bool_ballast;

void Vanne(bool etat);
void setupElectrovanne();

#endif