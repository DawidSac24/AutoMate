#ifndef global_h
#define global_h
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
#define JOUEUR_BLANC 0
#define JOUEUR_NOIR 1
//****************** Constantes pour la sequance de deplacement *******************************************
//****************** Constantes pour le choix de difficulté *******************************************
#define EASY 1
#define NORMAL 2
#define HARD 3
//******************************************* VALEURS DES PIONS ***************************************************************
#define ROI_B 6
#define ROI_N -6
#define DAME_B 5
#define DAME_N -5
#define TOUR_B 4
#define TOUR_N -4
#define FOU_B 3
#define FOU_N -3
#define CHEVAL_B 2
#define CHEVAL_N -2
#define PION_B 1
#define PION_N -1
//**********************************************************  VARIABLES GLOBALES *********************************************************************************
//******************************************* PLANCHE DE DEPART ***************************************************************
extern const int planche_depart[8][8];
//******************************************* PLANCHE  ************************************************************************
extern int planche[8][8];
extern int planche_precedent[8][8];
extern int pion_tempo;
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
extern int colonne_precedent;
extern int ligne_precedent;
extern bool demonstration;

extern int vit_dep;  // milisecondesc
extern int nmbre_pas;
extern int dir_moteur;
extern int dir2;

extern int pos_x;
extern int pos_y;
//***************************** VARIABLES POUR Les multiplexeurs ************************************************************
extern int reed_sensor_status[8][8];
extern int reed_sensor_record[8][8];
extern int reed_sensor_status_memory[8][8];
extern const byte MUX_OUTPUT;
extern const byte MUX_ADDR[4];  // A3 -> LSB A0 -> MSB
extern const byte MUX_SELECT[4];

extern const byte MUX_CHANNEL[16][4];
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
extern String nom_variable;
extern String information;
//***************************** VARIABLES POUR L'ETAT DE LA PARTIE ************************************************************
extern bool tour_blanc;
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
void decompte();
void envoi_ecran();
void envoi_ecran_val(String *variable, int *info);
void envoi_ecran_str(String *variable, String *info);
void calibrate();
void demarrage_partie();
bool verif_dep();
bool pion_blanc();
bool pion_noir();
bool verif_tour();
void lecture_aimants();
void affichage_aimants();
void affichage_planche();
//********************************************** CLASSES ***********************************************************************
class Dep {
public:
  Dep();
  void init();
  void vertical(int *temps, int *pas, int *dir);
  void horizontal(int *temps, int *pas, int *dir);
  void reset();
  void pion();
  void demo();
};

#endif