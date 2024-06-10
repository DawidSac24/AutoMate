#include "global.h"

bool pion_blanc() {
  if (colonne_precedent == 1 && colonne_select == 3 && ligne_select == ligne_precedent)  // si le pion n'a pas encore été deplacé, il a avancé de 2 cases et na pas changé de ligne
    return true;                                                                         // on envoi un pour dire que le deplacement est correct
  else if (colonne_select == colonne_precedent + 1) {
    if (ligne_select == ligne_precedent)
      return true;                                                                          // on envoi un pour dire que le deplacement est correct
    else if (ligne_select == ligne_precedent + 1 || ligne_select == ligne_precedent - 1) {  // Si le pion a tué un pion sur ca diagonale (1 case d'ecart)
      elim_pion(colonne_select, ligne_select);                                              // elimination du pion
      return true;
    } else
      return false;  // le deplacement n'est pas correct -> on retourne 0
  } else
    return false;  // le deplacement n'est pas correct -> on retourne 0
}
bool pion_noir() {
  if (colonne_precedent == 6 && colonne_select == 4 && ligne_select == ligne_precedent)  // si le pion n'a pas encore été deplacé, il a avancé de 2 cases et na pas changé de ligne
    return true;                                                                         // on envoi un pour dire que le deplacement est correct
  else if (colonne_select == colonne_precedent - 1) {
    if (ligne_select == ligne_precedent)
      return true;                                                                          // on envoi un pour dire que le deplacement est correct
    else if (ligne_select == ligne_precedent + 1 || ligne_select == ligne_precedent - 1) {  // Si le pion a tué un pion sur ca diagonale (1 case d'ecart)
      elim_pion(colonne_select, ligne_select);                                              // elimination du pion
      return true;
    } else
      return false;  // le deplacement n'est pas correct -> on retourne 0
  } else
    return false;  // le deplacement n'est pas correct -> on retourne 0
}

bool verif_tour() {
  if (ligne_select == ligne_precedent) {
    if (colonne_select > colonne_precedent) {
      for (int colonne_test = colonne_precedent; colonne_test < colonne_select + 1; colonne_test++) {
        if (planche[colonne_test][ligne_select] != 0)
          return false;  // le deplacement n'est pas correct -> on retourne 0
        else {
          if (planche[colonne_select][ligne_select] != 0)
            elim_pion(colonne_select, ligne_select);  // elimination du pion
          return true;
        }
      }
    } else if (colonne_select < colonne_precedent) {
      for (int colonne_test = colonne_precedent; colonne_test > colonne_select - 1; colonne_test--) {
        if (planche[colonne_test][ligne_select] != 0)
          return false;  // le deplacement n'est pas correct -> on retourne 0
        else {
          if (planche[colonne_select][ligne_select] != 0)
            elim_pion(colonne_select, ligne_select);  // elimination du pion
          return true;
        }
      }
    }
  } else if (colonne_select == colonne_precedent) {
    if (ligne_select > ligne_precedent) {
      for (int ligne_test = ligne_precedent; ligne_test < ligne_select + 1; ligne_test++) {
        if (planche[colonne_select][ligne_test] != 0)
          return false;  // le deplacement n'est pas correct -> on retourne 0
        else {
          if (planche[colonne_select][ligne_select] != 0)
            elim_pion(colonne_select, ligne_select);  // elimination du pion
          return true;
        }
      }
    } else if (ligne_select < ligne_precedent) {
      for (int ligne_test = ligne_precedent; ligne_test > ligne_select - 1; ligne_test--) {
        if (planche[colonne_select][ligne_test] != 0)
          return false;  // le deplacement n'est pas correct -> on retourne 0
        else {
          if (planche[colonne_select][ligne_select] != 0)
            elim_pion(colonne_select, ligne_select);  // elimination du pion
          return true;
        }
      }
    }
  } else
    return false;  // le deplacement n'est pas correct -> on retourne 0

  if (planche[colonne_select][ligne_select] != 0) {
    elim_pion(colonne_select, ligne_select);  // elimination du pion
    return true;
  }
