//********************************************** LIBRAIRIES *******************************************************************
#include "global.h"

bool verif_dep() {
  switch (pion_selectionne) {
    case PION_B:
      if (colonne_precedent == 2) {                     // si le pion n'a pas encore été deplacé
        if (colonne_select == colonne_precedent + 2) {  // Si le pion a avancé de 2
          if (ligne_select == ligne_precedent)
            return true;
        }  // on envoi un pour dire que le deplacement est correct
      } else {
        if (colonne_select == colonne_precedent + 1) {  // Si le pion a avancé de 1
          if (ligne_select == ligne_precedent)
            return true;                                                                     // on envoi un pour dire que le deplacement est correct
          if (ligne_select == ligne_precedent + 1 || ligne_select == ligne_precedent - 1) {  // Si le pion a tué pion a sur ca diagonale (1 case d'ecart)
            elim_pion(colonne_select, ligne_select);                                         // elimination du pion
            return true;                                                                     // on envoi un pour dire que le deplacement est correct
          } else                                                                             // le deplacement n'est pas correct -> on retourne 0
            return false;
        } else  // le deplacement n'est pas correct -> on retourne 0
          return false;
      }
      break;
    case PION_N:
      if (colonne_precedent == 2) {                     // si le pion n'a pas encore été deplacé
        if (colonne_select == colonne_precedent - 2) {  // Si le pion a avancé de 2
          if (ligne_select == ligne_precedent)
            return true;
        }  // on envoi un pour dire que le deplacement est correct
      } else {
        if (colonne_select == colonne_precedent - 1) {  // Si le pion a avancé de 1
          if (ligne_select == ligne_precedent)
            return true;                                                                     // on envoi un pour dire que le deplacement est correct
          if (ligne_select == ligne_precedent + 1 || ligne_select == ligne_precedent - 1) {  // Si le pion a tué pion a sur ca diagonale (1 case d'ecart)
            elim_pion(colonne_select, ligne_select);                                         // elimination du pion
            return true;                                                                     // on envoi un pour dire que le deplacement est correct
          } else                                                                             // le deplacement n'est pas correct -> on retourne 0
            return false;
        } else  // le deplacement n'est pas correct -> on retourne 0
          return false;
      }
      break;
  }
}