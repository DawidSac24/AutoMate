#include "global.h"

void dep_horizontal(int *temps, int *pas, int *dir) {  // dir 1 = gauche et dir 2 = droite
  digitalWrite(DIR1, *dir);
  digitalWrite(DIR2, *dir);
  for (int x = 0; x < *pas; x++) {
    digitalWrite(STEP1, 1);
    digitalWrite(STEP2, 1);
    delayMicroseconds(*temps);
    digitalWrite(STEP1, 0);
    digitalWrite(STEP2, 0);
    delayMicroseconds(*temps);
  }
}

void dep_vertical(int *temps, int *pas, int *dir) {  // dir 1 = haut dir 2 = bas
  if (*dir == 1) {
    digitalWrite(DIR1, !*dir);
    digitalWrite(DIR2, *dir);
  } else {
    digitalWrite(DIR1, *dir);
    digitalWrite(DIR2, !*dir);
  }
  for (int x = 0; x < *pas; x++) {
    digitalWrite(STEP1, 1);
    digitalWrite(STEP2, 1);
    delayMicroseconds(*temps);

    digitalWrite(STEP1, 0);
    digitalWrite(STEP2, 0);
    delayMicroseconds(*temps);
  }
}

void reset_pos() {
  // // dep vers l'arriere
  // vit_dep = 1000;

  // nmbre_pas = 50;
  // dir_moteur = 1;
  // dep_vertical(&vit_dep, &nmbre_pas, &dir_moteur);

  // // dep vers la gauche
  // nmbre_pas = 80;
  // dep_horizontal(&vit_dep, &nmbre_pas, 1);

  // // aimant va vers l'avant
  // dir_moteur = 2;
  // digitalWrite(DIR1, dir_moteur);
  // digitalWrite(DIR2, !dir_moteur);
  // while (digitalRead(FCA)) {
  //   digitalWrite(STEP1, 1);
  //   digitalWrite(STEP2, 1);
  //   delayMicroseconds(vit_dep);
  //   digitalWrite(STEP1, 0);
  //   digitalWrite(STEP2, 0);
  //   delayMicroseconds(vit_dep);
  // }

  // // aimant va a droite
  // dir_moteur = 2;
  // digitalWrite(DIR1, dir_moteur);
  // digitalWrite(DIR2, dir_moteur);
  // while (digitalRead(FCB)) {
  //   digitalWrite(STEP1, 1);
  //   digitalWrite(STEP2, 1);
  //   delayMicroseconds(vit_dep);

  //   digitalWrite(STEP1, 0);
  //   digitalWrite(STEP2, 0);
  //   delayMicroseconds(vit_dep);
  // }
  // nmbre_pas = 50;  //                              deplacement vers la case H1
  // dir_moteur = 1;
  // dep_vertical(&vit_dep, &nmbre_pas, &dir_moteur);
  // nmbre_pas = 40;
  // dep_horizontal(&vit_dep, &nmbre_pas, 2);
}

void dep_pion() {
  if (tour >= 1) {
    tour_blanc = !tour_blanc;
    sequance = !sequance;
    tour = 0;
  } else {
    tour++;
  }
  calibrate();

  x_dep = case_x[colonne_select] - x_precedent;
  y_dep = case_y[ligne_select] - y_precedent;


  if (pion_selectionne == false) {
    vit_dep = 1000;

    if (x_dep > 0) {
      dep_horizontal(&vit_dep, &x_dep, 1);
    } else {
      x_dep = x_dep * -1;
      dep_horizontal(&vit_dep, &x_dep, 2);
    }
    if (y_dep > 0) {
      dir_moteur = 1;
      dep_vertical(&vit_dep, &y_dep, &dir_moteur);
    } else {
      y_dep = y_dep * -1;
      dir_moteur = 2;
      dep_vertical(&vit_dep, &y_dep, &dir_moteur);
    }
  } else {

    verif_dep();
    if (verif_dep() == true) {
      Serial.println("dep veriie");
      planche[colonne_select][ligne_select] = planche[colonne_precedent][ligne_precedent];
      planche[colonne_precedent][ligne_precedent] = 0;

      digitalWrite(AIMANT, 1);
      vit_dep = 4000;
      if (x_dep > 0) {
        x_dep = x_dep - 100;
        dep_horizontal(&vit_dep, &x, 1);
      } else if (x_dep < 0) {
        x_dep = x_dep + 100;
        dep_horizontal(&vit_dep, &x, 2);
      } else if (x_dep == 0) {
        if (ligne_select == 7) {
          x_dep = -100;
          dep_horizontal(&vit_dep, &x, 1);
        } else {
          x_dep = 100;
          dep_horizontal(&vit_dep, &x, 2);
        }
      }
      if (y_dep > 0) {
        dir_moteur = 1;
        y_dep = y_dep - 100;

        dep_vertical(&vit_dep, &y_dep, &dir_moteur);
      } else if (y_dep < 0) {
        dir_moteur = 2;
        y_dep = y_dep + 100;

        y_dep = y_dep * -1;

        dep_vertical(&vit_dep, &y_dep, &dir_moteur);
        y_dep = y_dep * -1;
      } else if (y_dep == 0) {
        dir_moteur = 1;
        y_dep = -100;
        dep_vertical(&vit_dep, &x, &dir_moteur);
      }

      if (x_dep > 0) {
        dep_horizontal(&vit_dep, &x_dep, 1);
      } else if (x_dep < 0) {
        x_dep = x_dep * -1;
        dep_horizontal(&vit_dep, &x_dep, 2);
        x_dep = x_dep * -1;
      }

      if (y_dep > 0) {
        dir_moteur = 1;
        y_dep = 0;
        dep_vertical(&vit_dep, &x, &dir_moteur);
      } else if (y_dep < 0) {
        dir_moteur = 2;
        y_dep = 0;
        dep_vertical(&vit_dep, &x, &dir_moteur);
      }

      digitalWrite(AIMANT, 0);

    } else {

      if (tour == 0) {
        tour_blanc = !tour_blanc;
        sequance = !sequance;
        tour = 2;
      } else
        tour--;

      nom_variable = "t0.txt=";
      information = "DEPLACEMENT FAUX";
      envoi_ecran_str(&nom_variable, &information);
    }
  }


  x_precedent = case_x[colonne_select];
  y_precedent = case_y[ligne_select];
  colonne_precedent = colonne_select;
  ligne_precedent = ligne_select;

  pion_selectionne = !pion_selectionne;
}

bool elim_pion(int colonne, int ligne) {
  if (planche[colonne][ligne] != 0) {
    if (pions_elimines == 7) {
      nom_variable = "";
      information = "page 13";
      envoi_ecran_str(&nom_variable, &information);
    } else {
      x_dep = case_x[colonne] - x_precedent;
      y_dep = case_y[ligne_select] - y_precedent;
     
     dep_pion();
    }
  } else
    return false;
}
