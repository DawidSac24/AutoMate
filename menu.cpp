#include "global.h"

void envoi_ecran_val(String *variable, int *info) {
  // Serial.println("evoi ecran =");
  // Serial.println(*variable);
  // Serial.println(*info);

  mySerial.print(*variable);
  mySerial.print(*info);
  mySerial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
  mySerial.write(0xff);
  mySerial.write(0xff);
}
void envoi_ecran_str(String *variable, String *info) {
  // Serial.println("evoi ecran =");
  // Serial.println(*variable);
  // Serial.println(*info);

  mySerial.print(*variable);
  mySerial.print("\"");
  mySerial.print(*info);
  mySerial.print("\"");
  mySerial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
  mySerial.write(0xff);
  mySerial.write(0xff);
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
    nom_variable = "n0.val=";
    envoi_ecran_val(&nom_variable, &minutes_blanc);
    nom_variable = "n1.val=";
    envoi_ecran_val(&nom_variable, &secondes_blanc);

    nom_variable = "t0.txt=";
    information = "WHITE'S TURN";
    envoi_ecran_str(&nom_variable, &information);

    sequance = JOUEUR_BLANC;
  } else {
    nom_variable = "n0.val=";
    envoi_ecran_val(&nom_variable, &minutes_noir);
    nom_variable = "n1.val=";
    envoi_ecran_val(&nom_variable, &secondes_noir);

    nom_variable = "t0.txt=";
    information = "BLACK'S TURN";
    envoi_ecran_str(&nom_variable, &information);

    sequance = JOUEUR_NOIR;
  }
}

void demarrage_partie() {
  for (int i = 0; i > 8; i++) {
    for (int j = 0; j > 8; j++) {
      planche[i][j] = planche_depart[i][j];
    }
  }
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

  x_precedent = 0;
  y_precedent = 0;

  tour = 0;
  tour_blanc = true;
  pion_selectionne = false;
  sequance = JOUEUR_BLANC;
  calibrate();
  reset_pos();
  Serial.println("sequance = START");
}