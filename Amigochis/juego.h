#ifndef JUEGO_H
#define JUEGO_H

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>
#include <Servo.h>
#include <TouchScreen.h>

//=======================================
//  Estados del juego
//=======================================
enum EstadoJuego { MENU_INICIO, JUGANDO, VICTORIA, DERROTA };
extern EstadoJuego estado;

//=======================================
//  Variables compartidas
//=======================================
extern int cantidadDeLanas;
extern int vidaDelMalditoYHorribleWarden;
extern int Sucri;
extern int casila;
extern int casillaActual;
extern int accionesDisp;
extern bool Btnpress;
extern bool UD;
extern bool LanaUsable;
extern bool empiezalobueno;
extern bool tuTurno;

//=======================================
//  Hardware (definido en Amigochis.ino)
//=======================================
extern const byte BTN1;
extern const TSPoint TiraLed;
extern TouchScreen tactil;

//=======================================
//  Funciones
//=======================================
void turnoMan(bool tuTurno);
bool QuickEvent();
bool BtnACT();
void juegito();
void reiniciarJuego();
extern bool pantallaTocada();

#endif
