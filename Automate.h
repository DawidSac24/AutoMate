//********************************************** LIBRAIRIES *******************************************************************
#include <Arduino.h>
#include <SoftwareSerial.h>  // SoftwareSerial Library
//********************************************** CONSTANTES *******************************************************************
#define lignes 8
#define colonnes 8
//****************** Constantes pour la communication en Rx Tx avec SoftwareSerial *************
#define RXPIN 18  // A4
#define TXPIN 19  // A5
#define FCA 11    // fin de course A
#define FCB 10    // fin de course B
//****************** Constantes pour les moteurs pas à pas *************************************
#define STEP1 5
#define DIR1 4
#define STEP2 3
#define DIR2 2
//****************** Constantes pour l'électro-aimant ******************************************
#define AIMANT 6
//****************** Constantes pour le multiplexeur *******************************************
#define SIG 12
#define EN1 9
#define EN2 8
#define EN3 7
#define EN4 13
//****************** Constantes pour le choix de sequances *******************************************
#define START 1
#define CALIBRATE 2
#define PARAMETRES 3
#define JOUEUR_BLANC 4
#define JOUEUR_NOIR 5
//****************** Constantes pour la sequance de deplacement *******************************************
#define CHOIX_PION 0
#define DEPLACEMENT_PION 1
//****************** Constantes pour le choix de difficulté *******************************************
#define EASY 1
#define NORMAL 2
#define HARD 3
//**********************************************************  VARIABLES GLOBALES *********************************************************************************
//***************************** VARIABLES POUR LE DEPLACEMENT ************************************************************
extern int case_x[8];
extern int case_y[8];
extern int x_precedent;
extern int y_precedent;
extern int x_dep;
extern int y_dep;
extern int colonne_select;
extern int ligne_select;
extern bool pion_selectionne;

extern int vit_dep;  // milisecondesc
extern int nmbre_pas;
extern int dir_moteur;
extern int dir2;

extern int pos_x;
extern int pos_y;

//***************************** VARIABLES POUR LE MENU ************************************************************
extern int data[7];  // Déclaration d'un tableau d'entier
extern byte sequance;
extern int i;
extern int x;
extern int page;
extern int id_bouton;
extern byte difficulty;  // 0 => difficulté = facile
extern bool joueur_vs_joeur;
extern byte j1_choix_pion;  // si j1_choix_pion = 0 => couleur des pions du J1  = pas definie ; si 1 => couleur = blancs ; si 2 => couleur = noir
//***************************** VARIABLES POUR L'ETAT DE LA PARTIE ************************************************************
extern bool tour_blanc;
extern bool case_choisie;
extern byte tour;
//***************************** VARIABLES POUR LE TIMER ************************************************************
extern int timer_select;
extern unsigned long t;
extern int minutes_blanc;
extern int secondes_blanc;
extern int minutes_noir;
extern int secondes_noir;
extern int minutes;
extern int secondes;
//***************************** VARIABLES AUTRES************************************************************
extern int sigval;
extern SoftwareSerial mySerial;
//********************************************** FONCTIONS ***********************************************************************

void dep_vertical(int *temps, int *pas, int *dir);
void dep_horizontal(int *temps, int *pas, int *dir);
void reset_pos();
void decompte();
void envoi_ecran();
void calibrate();
void demarrage_partie();
void joueur_blanc();
void joueur_noir();
void dep_pion();