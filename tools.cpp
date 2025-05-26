#include "tools.h.ino"

void Vanne::Vanne(bool bool_ballast){
  while bool_ballast {
    digitalWrite(RELAY_PIN, HIGH);
    delay(5000); //à ajuster pour que les ballastes fonctionnent
    digitalWrite(RELAY_PIN, LOW);
  }
}