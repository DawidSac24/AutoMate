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

  x_dep = case_x[colonne_select] - x_precedent;
  y_dep = case_y[ligne_select] - y_precedent;

  // Serial.print("x dep = ");
  // Serial.println(x_dep);
  // Serial.print("y dep = ");
  // Serial.println(y_dep);

  if (pion_selectionne == false) {
    vit_dep = 1000;

    // Serial.println("selection de pion");

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

    // Serial.println("deplacement de pion");

    if (x_dep > 0) {
      // Serial.println("100 gauche");
      x_dep = x_dep - 100;

      // Serial.print("x dep = ");
      // Serial.println(x_dep);

      dep_horizontal(&vit_dep, &x, 1);
    } else if (x_dep < 0) {
      // Serial.println("100 droite");
      x_dep = x_dep + 100;

      // Serial.print("x dep = ");
      // Serial.println(x_dep);

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
      // Serial.println("bas");
      dir_moteur = 1;
      y_dep = y_dep - 100;

      dep_vertical(&vit_dep, &y_dep, &dir_moteur);
    } else if (y_dep < 0) {
      // Serial.println("haut");
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
      // Serial.println("gauche");

      // Serial.print("x dep = ");
      // Serial.println(x_dep);

      dep_horizontal(&vit_dep, &x_dep, 1);
    } else if (x_dep < 0) {
      // Serial.println("droite");

      // Serial.print("x dep = ");
      // Serial.println(x_dep);

      x_dep = x_dep * -1;
      dep_horizontal(&vit_dep, &x_dep, 2);
      x_dep = x_dep * -1;
    }

    if (y_dep > 0) {
      // Serial.println("100 gauche");
      dir_moteur = 1;
      y_dep = 0;
      dep_vertical(&vit_dep, &x, &dir_moteur);
    } else if (y_dep < 0) {
      // Serial.println("100 droite");
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
  pion_selectionne = false;

  // d2 -> d4
  Serial.println("d2 -> d4");
  ligne_select = 3;
  colonne_select = 1;
  dep_pion();
  delay(500);

  ligne_select = 3;
  colonne_select = 3;
  dep_pion();
  delay(500);

  // g8 -> f6
  Serial.println("g8 -> f6");
  ligne_select = 6;
  colonne_select = 7;
  dep_pion();
  delay(500);

  ligne_select = 5;
  colonne_select = 5;
  dep_pion();
  delay(500);

  // b1 -> d2
  Serial.println("b1 -> d2");
  ligne_select = 1;
  colonne_select = 0;
  dep_pion();
  delay(500);

  ligne_select = 3;
  colonne_select = 1;
  dep_pion();
  delay(500);

  // e7 -> e5
  Serial.println("e7 -> e5");
  ligne_select = 4;
  colonne_select = 6;
  dep_pion();
  delay(500);

  ligne_select = 4;
  colonne_select = 4;
  dep_pion();
  delay(500);

  // *************************************************** ELIM PION ************************************************
  // e5 -> mort
  Serial.println("e5 -> mort");
  ligne_select = 4;
  colonne_select = 4;
  dep_pion();
  delay(500);

  digitalWrite(AIMANT, 1);
  vit_dep = 1800;
  dir_moteur = 2;
  y_dep = 700;
  dep_vertical(&vit_dep, &y_dep, &dir_moteur);
  pion_selectionne = false;
  digitalWrite(AIMANT, 0);
  delay(500);

  reset_pos();
  x_precedent = 0;
  y_precedent = 0;
  // *************************************************** ELIM PION ************************************************

  // d4 -> e5
  Serial.println("d4 -> e5");
  ligne_select = 3;
  colonne_select = 3;
  dep_pion();
  delay(500);

  ligne_select = 4;
  colonne_select = 4;
  dep_pion();
  delay(500);

  // f6 -> g4
  Serial.println("f6 -> g4");
  ligne_select = 5;
  colonne_select = 5;
  dep_pion();
  delay(500);

  ligne_select = 6;
  colonne_select = 3;
  dep_pion();
  delay(500);

  // h2 -> h3
  Serial.println("h2 -> h3");
  ligne_select = 7;
  colonne_select = 1;
  dep_pion();
  delay(500);

  ligne_select = 7;
  colonne_select = 2;
  dep_pion();
  delay(500);

  // g4 -> e3
  Serial.println("g4 -> e3");
  ligne_select = 6;
  colonne_select = 3;
  dep_pion();
  delay(500);

  ligne_select = 4;
  colonne_select = 2;
  dep_pion();
  delay(500);

  mySerial.print("page 12");
  mySerial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
  mySerial.write(0xff);
  mySerial.write(0xff);
}