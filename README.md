# AutoMate
[![Static Badge](https://img.shields.io/badge/README-IN_ENGLISH-purple)](https://github.com/DawidSac24/AutoMate/blob/main/README.md)
[![Static Badge](https://img.shields.io/badge/Linked-in-blue)](https://www.linkedin.com/in/dawid-sac/)
[![Static Badge](https://img.shields.io/badge/easy-EDA-blue)](https://oshwlab.com/ivaninraci/auto-mate)

> © INRACI

![Image](https://github.com/DawidSac24/AutoMate/assets/171250080/feb73961-88cd-448d-83f6-739fa6a3914a)
## Video 



https://github.com/DawidSac24/AutoMate/assets/171250080/86d8ad7e-6ad9-42c3-80ba-5ba671484344

## Sommaire

- [Source du project](#Source-du-project)
- [Introduction](#Introduction)
- [Le schéma bloc](#Le-schéma-bloc) 
- [Characteristiques](#Characteristiques)
- [Librairies utilisées](#Librairies-utilisées)
- [Mon programme](#Mon-programme)
- [Les schémas de principes](#Les-schémas-de-principes)
  - [Le schéma de principe sans connecteurs](#Le-schéma-de-principe-sans-connecteurs)
  - [Le schéma de principe avec connecteurs](#Le-schéma-de-principe-avec-connecteurs)
- [Le PCB](#Le-PCB) 
- [Liste des pièces](#Liste-des-pièces) 
  - [Table XY](#Table-XY)
  - [Transmission](#Transmission)
  - [Electronique](#Electronique)
  - [Boitier](#Boitier)
  - [Visserie](#Visserie)

## Source du project
Je tiens à remercier sincèrement l'auteur du site dont je me suis inspiré :
[instructables.com/Automated-Chessboard](https://www.instructables.com/Automated-Chessboard/)

## Introduction
J’ai le plaisir de vous présenter mon projet passionnant : Auto-Mate qui est un jeu d’échecs automatisé dont le but est de donner une nouvelle dimension à ce jeu. Grâce à un déplacement de pions à distance, je crée la possibilité d’amener le jeu d’échecs en ligne ou contre un robot sur un échiquier. Pour cela, j’ai réalisé un boitier s’occupant du déplacement des pions. Auto-mate est équipé d’un écran, permettent de piloter le déplacement automatique des pions. Il est aussi possible de les déplacer manuellement, au moyen des capteurs se trouvent en dessous de la planche.
J’ai décidé de choisir ce projet, car j’apprécie jouer aux échecs. Ce dernier m’a permis de retrouver les sensations d’un vrai jeu d’échecs sur échiquier tout en ayant la possibilité de jouer contre un adversaire en ligne ou un robot. Cela m'a permis d'apprendre de nombreuses nouvelles choses en électronique et en programmation. Auto-Mate est encore en développement (principalement le code). Je vous invite à consulter mon travail dans le dossier [TFE](TFE), où se trouve une documentation plus détaillée de mon projet. Je tiens également à ajouter que je suis encore un jeune étudiant. Mon travail et mon code sont loin d'être parfaits et contiennent de nombreuses erreurs. Mon objectif, avant tout, est de présenter mon travail et peut-être d'inspirer certaines personnes.

## Le schéma bloc

![Schema bloc](https://github.com/DawidSac24/AutoMate/assets/171250080/c1ea0b3d-b250-44f0-b621-0e71598915d2)
### Le microprocesseur 
C’est le cerveau du montage, il permet de piloter chaque composant (les moteurs, les drivers-moteurs, l’électro-aimant, les multiplexeurs et l’écran tactile) et lire les données nécessaires (les fins de courses, les boutons, les capteurs à aimant et l’écran tactile). 
### L’écran tactile 
Il offre la possibilité de naviguer dans les menus pour changer la difficulté de l’IA, affichage du minuteur, modifier les paramètres de la partie ou sélectionner le mode de jeu. Il communique avec l’UART, un bus série asynchrone. 
### Les drivers-moteurs A et B 
Ils pilotent les bobines des moteurs pas à pas et fournissent le courant nécessaire pour faire fonctionner ces derniers. 
### Les moteurs A et B 
Ils sont associés à un système de courroie, ils déplacent l’électro-aimant sur les 2 axes, x et y. 
### L’électro-aimant 
Il sera placé en dessous du damier et sert déplacer les pièces aimantées sur le damier. 
### Le multiplexeur 
Il lit successivement le signal des 8 capteurs et envoi la donnée au microprocesseur. 
### Les capteurs à aimant 
Ils déterminent la présence des pièces d’échecs. 
### Les fins de course x et y 
Ils localisent l’emplacement de l’électro-aimant en faisant une remise à zéro lors du démarrage de la partie. Ils permettent de calibrer la position de ce dernier, permettent de contourner les potentielles dérégulations lors de son déplacement. 

## Characteristiques
### Generales :
- Écran graphique de couleur tactile, résistif, 320×240 pixels 
- 2 boutons d’arcade 
- 32 pions aimantés 
- Mode de fonctionnement : 1/2 joueurs 
- Déplacement automatique des pièces 
- Détection automatique des pièces 
- Zone pour pions éliminés 
### Electroniques :
- Alimentation 12V, 2A 
### Mechaniques :
- Dimensions : 496 mm x 496 mm x 100 mm  
- 6 faces en contre-plaqué 
- Poids : 4 kg

## Librairies utilisées
Je voulais utuliser la  [librairie Nextion](https://docs.arduino.cc/learn/built-in-libraries/software-serial/) pour le code de mon écran tactile mais, j'ai accidentellement connecté mon écran aux mauvaises bornes de mon microcontrôleur et j'ai dû utiliser mon écran tactile manuellement avec la [librairie SoftwareSerial](https://docs.arduino.cc/learn/built-in-libraries/software-serial/).

## Mon programme
Je voulais ajouter un algorithme qui serait utilisé pour un robot ennemi. Malheureusement, je n'ai pas fini de faire la vérification des déplacements autorisés pour les pions, ce qui est nécessaire pour l'algorithme. Si vous souhaitez voir le développement de ce-dernier, vous devrez attendre les prochaines mises à jour. Pour compenser, voici ce que je prévois de faire pour l'algorithmed du robot ennemi :
![obraz_2024-06-16_125101164](https://github.com/DawidSac24/AutoMate/assets/171250080/89d0b882-404a-4c24-a282-328a4100314f)

C'est ce qu'on appelle l'algorithme Min-Max, et j'utiliserai l'élagage Alpha-Beta, qui évalue les calculs inutiles et ignore les possibilités non souhaitées. Je vous invite à chercher de la documentation sur Min-Max et Alpha-Beta, qui est très intéressante. Voici une vidéo qui explique très bien l'algorithme :
https://www.youtube.com/watch?v=l-hh51ncgDI&t=48s

## Les schémas de principes
### Le schéma de principe sans connecteurs
![Schematic_Auto-Mate_Scema_sans_borniers_Dawid_2024-05-30](https://github.com/DawidSac24/AutoMate/assets/171250080/d2962a78-1aa2-455f-b27d-5ef20a18f260)
### Le schéma de principe avec connecteurs
![Schematic_Auto-Mate_dawid1_2024-06-16](https://github.com/DawidSac24/AutoMate/assets/171250080/a8f469b7-b881-42df-bde1-92fe47a32006)
## Le PCB
![PCB_PCB_Auto-Mate_2024-06-16](https://github.com/DawidSac24/AutoMate/assets/171250080/69b1cbf8-4836-43d2-8acc-4d27aa3df8c1)
![PCB_PCB_Auto-Mate_2024-06-16 (4)](https://github.com/DawidSac24/AutoMate/assets/171250080/37777ca2-a9b3-404c-a269-da8f828d9885)

## Parts list
### XY table
- 2 x V slot 20x20 linear rail, Length = 375 mm
- 1 x V slot 20x20 linear rail, Length = 350 mm
- 1 x V slot 20x20 linear rail, Length = 315 mm
- 1 x V slot 20x20 linear rail, Length = 395 mm
- 10 x 90 degree Corner Bracket
### Transmission
- 2 x GT2 Pulley, 20 teeth, 5mm bore
- 8 x GT2 Toothless pulley
- 3.5m x GT2 Belt
### Electronics
- 1 x Arduino Nano 
- 2 x Moteur pas à pas – Adafruit – Nema 17 200 pas/tr, 12V 350 mA 
- 2 x Driveurs moteur pas à pas – Pololu – A4988 
- 1 x Écran graphique Nextion 
- 1 x Électro-aimant – force de maintien de 5Kg 
- 1 x Diode de roue libre – 1N4007 
- 1 x Transistor Darlington TIP120 
- 2 x Fins de courses 
- 64 x Reed Switch – 2 x 14.5 mm 
- 1 x résistance de 1KΩ 
- 4 x Multiplexeur – CD74HC4067 
- 1 x connecteur femelle - DC Jack 
- Barrettes sécables femelles  
### Box
- 2 x Face 470 x 470 x 10 mm 
- 2 x Face 450 x 85 x 10 mm 
- 2 x Face 470 x 85 x 10 mm 
### Bolting
- 8 x Nini roue en V 
- 4 x Entretoise en aluminium - ID : 5 mm - Hauteur : 6 mm 
- 4 x entretoise excentrique - M5 
- 4 x hexagonaux. Écrou de blocage - M5 
- 4 x hexagonaux fins. Écrou - M5 
- 8 x Mini Cale de Précision - OD : 8 mm - ID : 5 mm - Epaisseur : 1 mm 
- 26 x écrous en T - M5 
- 14 x hexagonaux. Vis à tête cylindrique à six pans creux - M5 x 8 mm 
- 12 x hexagonaux. Vis à tête cylindrique à six pans creux - M5 x 12 mm 
- 2 x hexagonaux. Vis à tête cylindrique à six pans creux - M5 x 35 mm 
- 2 x hexagonaux. Vis à tête cylindrique à six pans creux - M5 x 30 mm 
- 2 x hexagonaux. Vis à tête cylindrique à six pans creux - M5 x 25 mm 
- 8 x hexagonaux. Vis à tête cylindrique à six pans creux - M5 x 15 mm 
- 4 x vis à tête fendue - M2 x 15 mm 
- 4 x écrou - M2 
- 8 x hexagonaux. Vis à tête creuse - M3 x 10 mm 
- 1 x hexagonal. Vis à tête creuse - M4 x 15 mm 
- 4 x vis à tête fraisée fendue - M5 x 20 mm 
- 4 x écrou - M5
- 128 x vis en laiton – M2 x 12mm 
