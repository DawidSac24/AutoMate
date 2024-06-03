#include "Automate.h"

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
void envoi_ecran() {
  mySerial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
  mySerial.write(0xff);
  mySerial.write(0xff);
}

void envoi_ecran1(String *variable, int *info) {
  Serial.println("evoi ecran =");
  Serial.println(*variable);
  Serial.println(*info);

  mySerial.print(*variable);
  mySerial.print(*info);
  mySerial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
  mySerial.write(0xff);
  mySerial.write(0xff);
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

void decompte() {  //
  //  Set the time of the current player
  if (tour_blanc == true) {
    minutes = secondes_blanc;
    minutes = minutes_blanc;
  } else if (tour_blanc == true) {
    secondes = secondes_noir;
    minutes = minutes_noir;
  }

  t = millis();
  // Serial.println(secondes);
  secondes--;
  if (secondes <= 0) {
    minutes--;
    secondes = 60;
  }
  // Serial.println(minutes);

  //  Record the white player time
  if (tour_blanc == true) {
    secondes_blanc = secondes;
    minutes_blanc = minutes;
  }
  //  Record the black player time
  else {
    secondes_noir = secondes;
    minutes_noir = minutes;
  }
}

void calibrate() {

  Serial.println("sequance = CALIBRATE");

  if (tour_blanc == true) {
    variable = "n0.val=";
    envoi_ecran1(&variable, &minutes_blanc);
    variable = "n1.val=";
    envoi_ecran1(&variable, &secondes_blanc);

    mySerial.print("t0.txt=");  // envoi des minutes et secondes ==> calibrer le 2 decomptes (Arduino et Nextion)
    mySerial.print("\"");
    mySerial.print("WHITE'S TURN");
    mySerial.print("\"");
    envoi_ecran();
    sequance = JOUEUR_BLANC;
  } else {
    variable = "n0.val=";
    envoi_ecran1(&variable, &minutes_noir);
    variable = "n1.val=";
    envoi_ecran1(&variable, &secondes_noir);

    mySerial.print("t0.txt=");  // envoi des minutes et secondes ==> calibrer le 2 decomptes (Arduino et Nextion)
    mySerial.print("\"");
    mySerial.print("BLACK'S TURN");
    mySerial.print("\"");
    envoi_ecran();
    sequance = JOUEUR_NOIR;
  }
}

void demarrage_partie() {

  switch (timer_select) {
    case 1:
      minutes = 2;
      break;
    case 2:
      minutes = 4;
      break;
    case 3:
      minutes = 9;
      break;
    case 4:
      minutes = 29;
      break;
    case 5:
      minutes = 59;
      break;
  }
  secondes = 60;

  secondes_blanc = 60;
  secondes_noir = 60;

  secondes_blanc = secondes;
  minutes_blanc = minutes;
  secondes_noir = secondes;
  minutes_noir = minutes;

  tour = 0;
  tour_blanc = true;
  pion_selectionne = false;

  calibrate();

  reset_pos();
  Serial.println("sequance = START");
}

void dep_pion() {

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
}
