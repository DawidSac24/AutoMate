//********************************************** LIBRAIRIES *******************************************************************
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

  switch (sequance) {
    case JOUEUR_BLANC:
      switch (pion_selectionne) {
        case PION_B:
          if (colonne_precedent == 1 && colonne_select == 3 && ligne_select == ligne_precedent)  // si le pion n'a pas encore été deplacé, il a avancé de 2 cases et na pas changé de ligne
            return true;                                                                         // on envoi un pour dire que le deplacement est correct
          else if (colonne_select == colonne_precedent + 1) {
            if (ligne_select == ligne_precedent)
              return true;                                                                          // on envoi un pour dire que le deplacement est correct
            else if (ligne_select == ligne_precedent + 1 || ligne_select == ligne_precedent - 1) {  // Si le pion a tué un pion sur ca diagonale (1 case d'ecart)
              if (elim_pion(colonne_select, ligne_select) == true)                                  // elimination du pion
                return true;
            } else
              return false;  // le deplacement n'est pas correct -> on retourne 0
          } else
            return false;  // le deplacement n'est pas correct -> on retourne 0
          break;
        case TOUR_B:
          if (ligne_select == ligne_precedent) {
            if (colonne_select > colonne_precedent) {
              for (colonne_test = colonne_precedent; colonne_test < colonne_select; colonne_test++) {
                if (planche[colonne_select][ligne_select] != 0)
                  return false;  // le deplacement n'est pas correct -> on retourne 0
              }
            } else if (colonne_select < colonne_precedent) {
              for (colonne_test = colonne_precedent; colonne_test > colonne_select; colonne_test--) {
              }
            }
            if (planche[colonne_select][ligne_select] != 0) {
              if (elim_pion(colonne_select, ligne_select) == true)  // elimination du pion
                return true;
              else
                return false;  // le deplacement n'est pas correct -> on retourne 0
            }
          }
      }
      break;

    case JOUEUR_NOIR:
      switch (pion_selectionne) {
        case PION_N:
          if (colonne_precedent == 6 && colonne_select == 4 && ligne_select == ligne_precedent)  // si le pion n'a pas encore été deplacé, il a avancé de 2 cases et na pas changé de ligne
            return true;                                                                         // on envoi un pour dire que le deplacement est correct
          else if (colonne_select == colonne_precedent - 1) {
            if (ligne_select == ligne_precedent)
              return true;                                                                          // on envoi un pour dire que le deplacement est correct
            else if (ligne_select == ligne_precedent + 1 || ligne_select == ligne_precedent - 1) {  // Si le pion a tué un pion sur ca diagonale (1 case d'ecart)
              if (elim_pion(colonne_select, ligne_select) == true)                                  // elimination du pion
                return true;
              else
                return false;  // le deplacement n'est pas correct -> on retourne 0
            } else
              return false;  // le deplacement n'est pas correct -> on retourne 0
          } else
            return false;  // le deplacement n'est pas correct -> on retourne 0
          break;
      }
      break;
  }
}