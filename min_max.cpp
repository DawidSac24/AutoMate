#include "global.h"

bool verif_dep() {
  Serial.print("colonne_select ");
  Serial.println(colonne_select);
  Serial.print("ligne_select ");
  Serial.println(ligne_select);
  Serial.print("colonne_precedent ");
  Serial.println(colonne_precedent);
  Serial.print("ligne_precedent ");
  Serial.println(ligne_precedent);

  switch (pion_selectionne) {
    case PION_B:
      return pion_blanc();
      break;
    case TOUR_B:
      return verif_tour();
      break;
    case PION_N:
      return pion_noir();
      break;
    case TOUR_N:
      return verif_tour();
      break;
  }
}