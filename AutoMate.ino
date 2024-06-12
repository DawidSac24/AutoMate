//  Automate_1.0.ino
//  Projet SIPS 2023-2024 : Auto-Mate
//  Sac Dawid 6ème éléctronique INRACI
/*  Hardware : Arduino Nano, moteur pas à pas Nema 17, driveur moteur - Pololu - A4988, éléctro-aimant, écran graphique Nextion
    transistor Darlington - TIP 120, capteurs à aimants, Multiplexeur - CD74HC4067, button d'arcade, fin de course  */
// 24.02.2024
//*****************************************************************************************************************************

//********************************************** LIBRAIRIES *******************************************************************
#include "global.h"
//**********************************************************  VARIABLES GLOBALES *********************************************************************************
//******************************************* PLANCHE DE DEPART ***************************************************************
const int planche_depart[8][8] = {
  { TOUR_B, CHEVAL_B, FOU_B, DAME_B, ROI_B, FOU_B, CHEVAL_B, TOUR_B },
  { PION_B, PION_B, PION_B, PION_B, PION_B, PION_B, PION_B, PION_B },
  {},
  {},
  {},
  {},
  { PION_N, PION_N, PION_N, PION_N, PION_N, PION_N, PION_N, PION_N },
  { TOUR_N, CHEVAL_N, FOU_N, DAME_N, ROI_N, FOU_N, CHEVAL_N, TOUR_N },
};
//******************************************* PLANCHE  ************************************************************************
int planche[8][8];
int planche_precedent[8][8];
int pion_tempo;
//***************************** VARIABLES POUR LE DEPLACEMENT ************************************************************
int case_x[8] = { 0, 200, 400, 600, 800, 1000, 1200, 1400 };
int case_y[8] = { 1400, 1200, 1000, 800, 600, 400, 200, 0 };
int x_precedent;
int y_precedent;
int x_dep;
int y_dep;
int colonne_select;
int ligne_select;
int colonne_precedent;
int ligne_precedent;
bool pion_selectionne = false;
bool demonstration = false;

int vit_dep = 1000;  // milisecondesc
int nmbre_pas = 50;
int dir_moteur = 1;
int dir2;

int pos_x;
int pos_y;
//***************************** VARIABLES POUR Les multiplexeurs ************************************************************
int reed_sensor_status[8][8];
int reed_sensor_record[8][8];
int reed_sensor_status_memory[8][8];
const byte MUX_OUTPUT(12);
const byte MUX_ADDR[4] = { A3, A2, A1, A0 };  // A3 -> LSB A0 -> MSB
const byte MUX_SELECT[4] = { 9, 8, 7, 13 };

const byte MUX_CHANNEL[16][4] = {
  { 0, 0, 0, 0 },
  { 1, 0, 0, 0 },
  { 0, 1, 0, 0 },
  { 1, 1, 0, 0 },
  { 0, 0, 1, 0 },
  { 1, 0, 1, 0 },
  { 0, 1, 1, 0 },
  { 1, 1, 1, 0 },
  { 0, 0, 0, 1 },
  { 1, 0, 0, 1 },
  { 0, 1, 0, 1 },
  { 1, 1, 0, 1 },
  { 0, 0, 1, 1 },
  { 1, 0, 1, 1 },
  { 0, 1, 1, 1 },
  { 1, 1, 1, 1 }
};
//***************************** VARIABLES POUR LE MENU ************************************************************
int data[7];  // Déclaration d'un tableau d'entier
byte sequance;
int i;
int x = 100;
int page;
int id_bouton;
byte difficulty = 0;  // 0 => difficulté = facile
bool joueur_vs_joeur = true;
byte j1_choix_pion;  // si j1_choix_pion = 0 => couleur des pions du J1  = pas definie ; si 1 => couleur = blancs ; si 2 => couleur = noir
String nom_variable;
String information;
//***************************** VARIABLES POUR L'ETAT DE LA PARTIE ************************************************************
bool tour_blanc = true;
byte tour = 0;
//***************************** VARIABLES POUR LE TIMER ************************************************************
int timer_select = 3;
unsigned long t;
int minutes_blanc = 10;
int secondes_blanc = 1;
int minutes_noir = 10;
int secondes_noir = 1;
int minutes = 10;
int secondes = 1;
//***************************** VARIABLES AUTRES************************************************************
int sigval;
SoftwareSerial mySerial = SoftwareSerial(RXPIN, TXPIN);

//******************************************************************************************************************************
void setup() {
  Serial.begin(9600);    //   Initialise the Serial port at 2400 baud.
  mySerial.begin(9600);  //   Initialise the mySerial object at 9600 baud rate.
  pinMode(RXPIN, INPUT);
  pinMode(TXPIN, OUTPUT);

  pinMode(STEP1, OUTPUT);
  pinMode(DIR1, OUTPUT);
  pinMode(STEP2, OUTPUT);
  pinMode(DIR2, OUTPUT);

  pinMode(FCA, INPUT_PULLUP);
  pinMode(FCB, INPUT_PULLUP);

  pinMode(AIMANT, OUTPUT);

  pinMode(SIG, INPUT_PULLUP);
  pinMode(EN1, OUTPUT);
  digitalWrite(EN1, 0);

  while (!Serial) {}
  for (byte i = 0; i < 4; i++) {  // INITIALISATION des multiplexeurs
    pinMode(MUX_ADDR[i], OUTPUT);
    digitalWrite(MUX_ADDR[i], LOW);
    pinMode(MUX_SELECT[i], OUTPUT);
    digitalWrite(MUX_SELECT[i], HIGH);
  }
  pinMode(MUX_OUTPUT, INPUT_PULLUP);
  for (byte i = 2; i < 6; i++) {
    for (byte j = 0; j < 8; j++) {
      reed_sensor_status[i][j] = 1;
      reed_sensor_status_memory[i][j] = 1;
    }
  }

  reset_pos();

  Serial.println("ready to start");
  t = millis;
}

void loop() {
  if (mySerial.available() > 0) {
    for (i = 0; i < 7; i++) {
      data[i] = mySerial.read();
      Serial.println(data[i]);
    }
    page = data[1];
    id_bouton = data[2];
    switch (page) {
      //**********************************************************  PAGE : Menu principal *********************************************************************************
      case 0:
        if (id_bouton == 1) {  // Appui du bouton PLAY
          demarrage_partie();
        }
        break;
      //**********************************************************  PAGE : Menu principal *********************************************************************************
      case 1:
        if (id_bouton == 2)
          demo();
        break;
      //**********************************************************  PAGE : Choix de la difficulté de la partie ************************************************************
      case 3:
        switch (id_bouton) {
          case 4:
            if (difficulty < HARD)
              difficulty++;
            break;
          case 8:
            if (difficulty > EASY)
              difficulty--;
            break;
        }
        Serial.print("difficulté = ");
        Serial.println(difficulty);
        break;
      //**********************************************************  PAGE : Choix du temps de la partie ********************************************************************
      case 4:
        switch (id_bouton) {
          case 4:
            if (timer_select < 5)
              timer_select++;
            Serial.println(timer_select);
            break;
          case 7:
            if (timer_select > 1)
              timer_select--;
            Serial.println(timer_select);
            break;
        }
        break;
      //**********************************************************  PAGE : Choix de la couleur de pion ********************************************************************
      case 5:
        switch (id_bouton) {
          case 1:  // CHOIX DE COULEUR DE PION : Blanc
            j1_choix_pion = 1;
            break;
          case 2:  // CHOIX DE COULEUR DE PION : Noire
            j1_choix_pion = 2;
            break;
          case 3:  // CHOIX DE COULEUR DE PION : Aleatoire
            j1_choix_pion = random(1, 3);
            break;
        }
        Serial.print("Tour du joueur 1 = ");
        Serial.println(j1_choix_pion);
        break;
      //**********************************************************  PAGE : Debug ******************************************************************************************
      case 6:
        Serial.println("Page Debug");
        reset_pos();
        ligne_select = 7;
        colonne_select = 0;
        x_precedent = 0;
        y_precedent = 0;
        break;
      //**********************************************************  PAGE : Play, choix de ligne ***************************************************************************
      case 8:
        if (id_bouton == 10 || id_bouton == 11) {
        }  // bouton actionné : retour OU paramètres
        else {
          Serial.print("ligne = ");
          ligne_select = id_bouton - 2;
          Serial.println(ligne_select);
          calibrate();
        }
        break;
      //**********************************************************  PAGE : Play, choix de colonne *************************************************************************
      case 9:
        if (id_bouton > 1 && id_bouton < 10) {  // un des boutons pour le choix de la colonne à été actionné
          if (tour >= 1) {
            tour_blanc = !tour_blanc;
            if (sequance == JOUEUR_BLANC)
              sequance = JOUEUR_NOIR;
            else
              sequance = JOUEUR_BLANC;
            tour = 0;
          } else
            tour++;

          Serial.print("tour ");
          Serial.println(tour);
          Serial.print("tour_blanc ");
          Serial.println(tour_blanc);

          calibrate();

          // Serial.print("colonne = ");
          colonne_select = id_bouton - 2;
          // Serial.println(colonne_select);

          dep_pion();


        } else if (id_bouton == 11) {
        }                            // bouton actionné : paramètres
        else if (id_bouton == 14) {  // bouton actionné : retours
          tour--;
          calibrate();
        }
        break;
      //**********************************************************  PAGE : Paramètres durent la parie *********************************************************************
      case 10:
        if (data[2] == 1)
          calibrate();
        if (data[2] == 2) {
          reset_pos();
          x_precedent = 0;
          y_precedent = 0;
        }
        break;
    }
  }
  switch (sequance) {
    case JOUEUR_BLANC:
      if (millis() - t > 995) {  // Display the white player clock
        decompte();
        // Serial.println("JOUEUR_BLANC");
        nom_variable = "n0.val=";
        envoi_ecran_val(&nom_variable, &minutes_blanc);
        nom_variable = "n1.val=";
        envoi_ecran_val(&nom_variable, &secondes_blanc);
        affichage_planche();
        affichage_aimants();
      }
      break;

      break;
    case JOUEUR_NOIR:
      if (millis() - t > 995) {  // Display the black player clock
        decompte();
        // Serial.println("JOUEUR_NOIR");
        nom_variable = "n0.val=";
        envoi_ecran_val(&nom_variable, &minutes_noir);
        nom_variable = "n1.val=";
        envoi_ecran_val(&nom_variable, &secondes_noir);
        affichage_planche();
        affichage_aimants();
      }
      break;
  }
}
