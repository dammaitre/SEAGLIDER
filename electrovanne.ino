#include "tools.h.ino"
#include "itools.cpp.ino"

bool bool_ballast = true //vrai pour ouvrir la vanne

void setup() {
  // initialize digital pin D4 as an output.
  pinMode(RELAY_PIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  Vanne(bool_ballast)
}