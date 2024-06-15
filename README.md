# AutoMate
![Image (8)](https://github.com/DawidSac24/AutoMate/assets/171250080/2e45e442-d7ad-42c4-8633-2ada9f801d8c)
## Video 

https://github.com/DawidSac24/AutoMate/assets/171250080/86d8ad7e-6ad9-42c3-80ba-5ba671484344

## Summary

- [Project source](#Project-source)
- [Introduction](#Introduction)
- [The block diagram](#The-block-diagram) 
- [Characteristics](#Characteristics)
- [Parts list](#Parts-list) 
  - [XY table](#XY-table)
  - [Transmission](#Transmission)
  - [Electronics](#Electronics)
  - [Box](#Box)
  - [Bolting](#Bolting)

- [The principle diagram](#The-principle-diagram)
- [PCB routing and screen printing](#PCB-routing-and-screen-printing)
- [Used libraries](#Used-libraries)  
- [Partie mécanique](#Partie-mécanique)

## Project source
I would like to sincerely thank the author of the site from which I drew inspiration :
[instructables.com/Automated-Chessboard](https://www.instructables.com/Automated-Chessboard/)

## Introduction
I am pleased to present my exciting project: Auto-Mate, an automated chess game designed to give a new dimension to this game. By enabling remote movement of pieces, I create the possibility of bringing chess online or against a robot on a chessboard. To achieve this, I have developed a case that handles the movement of the pieces. Auto-Mate is equipped with a screen, allowing for the automatic movement of pieces. It is also possible to move them manually using sensors located beneath the board. I made this project because I enjoy playing chess. It has allowed me to learn many new things in electronics and programming. Auto-mate is still in developpement (mostly the code).

## The block diagram

![Schema bloc](https://github.com/DawidSac24/AutoMate/assets/171250080/c1ea0b3d-b250-44f0-b621-0e71598915d2)

#### The Microprocessor
It is the brain of the setup, allowing control of each component (motors, motor drivers, electromagnet, multiplexers, and touchscreen) and reading the necessary data (limit switches, buttons, magnetic sensors, and touchscreen).

The Touchscreen
It provides the ability to navigate through menus to change the AI difficulty, display the timer, modify game settings, or select the game mode. It communicates with the UART, an asynchronous serial bus.

Motor Drivers A and B
They control the coils of the stepper motors and provide the necessary current to operate them.

Motors A and B
They are connected to a belt system, moving the electromagnet on the x and y axes.

The Electromagnet
It is placed underneath the board and is used to move the magnetized pieces on the board.

The Multiplexer
It successively reads the signals from the 8 sensors and sends the data to the microprocessor.

Magnetic Sensors
They determine the presence of the chess pieces.

x and y Limit Switches
They locate the position of the electromagnet by resetting at the start of the game. They allow for calibration of its position and help avoid potential misalignments during movement.

## Characteristics


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
- 2 x Stepper Motor - Adafruit - Nema 17 size - 200 steps/rev, 12V 350mA
- 2 x Stepper Motor Driver Carrier - Pololu - A4988
- 1 x LCD Module - I2C Serial - 2.6“
- 2 x Arcade button - Bore hole 23.5 mm
- 1 x Electromagnet - 5Kg Holding Force
- 1 x Freewheeling diode - 1N4001
- 1 x Power Transistor - TIP 120
- 2 x Micro Limit switch roller
- 64 x Reed Switch - Dia 2 x 14.5 mm
- 1 x Resistor - 1K ohm
- 4 x MUX breakout - SparkFun - CD74HC4067
- 1 x Terminal Block - DC Jack
- Female Headers
- 10 x Screw Terminal
- 3 x Prototyping Board - 50 x 100 mm
- 4 x HE10 Connectors
- 8 x Ribbon Cable - 8

### Box

- 2 x plywood - 470 x 470 x 10 mm
- 2 x plywood - 450 x 85 x 10 mm
- 2 x plywood - 450 x 85 x 10 mm

### Bolting

- 8 x Mini V Wheel
- 4 x Aluminium Spacer - ID : 5mm - Height : 6mm
- 4 x Eccentric Spacer - M5
- 4 x Hex. Locking Nut - M5
- 4 x Thin Hex. Nut - M5
- 8 x Mini Precision Shim - OD : 8 mm - ID : 5 mm - Thickness : 1 mm
- 26 x T-Nuts - M5
- 14 x Hex. Socket Button Head Cap Screw - M5 x 8 mm
- 12 x Hex. Socket Button Head Cap Screw - M5 x 12 mm
- 2 x Hex. Socket Button Head Cap Screw - M5 x 35 mm
- 2 x Hex. Socket Button Head Cap Screw - M5 x 30 mm
- 2 x Hex. Socket Button Head Cap Screw - M5 x 25 mm
- 8 x Hex. Socket Button Head Cap Screw - M5 x 15 mm
- 4 x Slotted Head Screw - M2 x 15 mm
- 4 x Nut - M2
- 8 x Hex. Socket Head Cap Screw - M3 x 10 mm
- 1 x Hex. Socket Head Cap Screw - M4 x 15 mm
- 4 x Slotted Countersunk Head Screw - M5 x 20 mm
- 4 x Nut - M5

## PCB routing and screen printing

## Used libraries
