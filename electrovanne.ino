#include "tools_electrovanne.h"

void setup() {
  setupElectrovanne();  // initialiser la vanne correctement
}

void loop() {
  bool_ballast = true;
  Vanne(bool_ballast);
  delay(5000);
  
  bool_ballast = false;
  Vanne(bool_ballast);
  delay(5000);
}