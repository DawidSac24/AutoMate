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
  // dep vers l'arriere
  vit_dep = 1000;

  nmbre_pas = 50;
  dir_moteur = 1;
  dep_vertical(&vit_dep, &nmbre_pas, &dir_moteur);

  // dep vers la gauche
  nmbre_pas = 80;
  dep_horizontal(&vit_dep, &nmbre_pas, 1);

  // aimant va vers l'avant
  dir_moteur = 2;
  digitalWrite(DIR1, dir_moteur);
  digitalWrite(DIR2, !dir_moteur);
  while (digitalRead(FCA)) {
    digitalWrite(STEP1, 1);
    digitalWrite(STEP2, 1);
    delayMicroseconds(vit_dep);
    digitalWrite(STEP1, 0);
    digitalWrite(STEP2, 0);
    delayMicroseconds(vit_dep);
  }

  // aimant va a droite
  dir_moteur = 2;
  digitalWrite(DIR1, dir_moteur);
  digitalWrite(DIR2, dir_moteur);
  while (digitalRead(FCB)) {
    digitalWrite(STEP1, 1);
    digitalWrite(STEP2, 1);
    delayMicroseconds(vit_dep);

    digitalWrite(STEP1, 0);
    digitalWrite(STEP2, 0);
    delayMicroseconds(vit_dep);
  }
  nmbre_pas = 50;  //                              deplacement vers la case H1
  dir_moteur = 1;
  dep_vertical(&vit_dep, &nmbre_pas, &dir_moteur);
  nmbre_pas = 40;
  dep_horizontal(&vit_dep, &nmbre_pas, 2);
}

void dep_pion() {

  x_dep = case_x[colonne_select] - x_precedent;
  y_dep = case_y[ligne_select] - y_precedent;

  Serial.print("x dep = ");
  Serial.println(x_dep);
  Serial.print("y dep = ");
  Serial.println(y_dep);

  if (pion_selectionne == false) {
    vit_dep = 1000;

    Serial.println("selection de pion");

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

  } else if (pion_selectionne == true) {
    digitalWrite(AIMANT, 1);

    vit_dep = 1800;

    Serial.println("deplacement de pion");

    if (x_dep > 0) {
      Serial.println("100 gauche");
      x_dep = x_dep - 100;

      Serial.print("x dep = ");
      Serial.println(x_dep);

      dep_horizontal(&vit_dep, &x, 1);
    } else if (x_dep < 0) {
      Serial.println("100 droite");
      x_dep = x_dep + 100;

      Serial.print("x dep = ");
      Serial.println(x_dep);

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
      Serial.println("bas");
      dir_moteur = 1;
      y_dep = y_dep - 100;

      dep_vertical(&vit_dep, &y_dep, &dir_moteur);
    } else if (y_dep < 0) {
      Serial.println("haut");
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
      Serial.println("gauche");

      Serial.print("x dep = ");
      Serial.println(x_dep);

      dep_horizontal(&vit_dep, &x_dep, 1);
    } else if (x_dep < 0) {
      Serial.println("droite");

      Serial.print("x dep = ");
      Serial.println(x_dep);

      x_dep = x_dep * -1;
      dep_horizontal(&vit_dep, &x_dep, 2);
      x_dep = x_dep * -1;
    }

    if (y_dep > 0) {
      Serial.println("100 gauche");
      dir_moteur = 1;
      y_dep = 0;
      dep_vertical(&vit_dep, &x, &dir_moteur);
    } else if (y_dep < 0) {
      Serial.println("100 droite");
      dir_moteur = 2;
      y_dep = 0;
      dep_vertical(&vit_dep, &x, &dir_moteur);
    }
  }
  digitalWrite(AIMANT, 0);

  x_precedent = case_x[colonne_select];
  y_precedent = case_y[ligne_select];

  pion_selectionne = !pion_selectionne;
}

void demo() {
  reset_pos();
  // e2 -> e4
  pion_selectionne = false;
  ligne_select = 4;
  colonne_select = 1;
  dep_pion();

  ligne_select = 4;
  colonne_select = 3;
  dep_pion();

  // e7 -> e5
  ligne_select = 4;
  colonne_select = 6;
  dep_pion();

  ligne_select = 4;
  colonne_select = 4;
  dep_pion();

  // g1 -> f3
  ligne_select = 6;
  colonne_select = 0;
  dep_pion();

  ligne_select = 5;
  colonne_select = 2;
  dep_pion();

  // b8 -> c6
  ligne_select = 0;
  colonne_select = 7;
  dep_pion();

  ligne_select = 2;
  colonne_select = 5;
  dep_pion();

  // d2 -> d4
  ligne_select = 3;
  colonne_select = 1;
  dep_pion();

  ligne_select = 3;
  colonne_select = 3;
  dep_pion();


// *************************************************** ELIM PION ************************************************
  // d4 -> mort 4
  ligne_select = 3;
  colonne_select = 3;
  dep_pion();
// *************************************************** ELIM PION ************************************************
}