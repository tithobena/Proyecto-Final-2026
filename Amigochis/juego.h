#ifndef JUEGO_H
#define JUEGO_H

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>
#include <Servo.h>        
#include <TouchScreen.h>

enum EstadoJuego { MENU_INICIO, JUGANDO, VICTORIA, DERROTA };
extern EstadoJuego estado;
extern int cantidadDeLanas;
extern int vidaDelMalditoYHorribleWarden;
extern int Sucri;
extern int casila;
extern int accionesDisp;
extern const byte BTN1;
extern bool Btnpress;
extern bool UD;
extern bool LanaUsable;
extern bool empiezalobueno;
extern int casillaActual;
extern EstadoJuego estado;
extern const TSPoint TiraLed;
extern TouchScreen tactil;

bool QuickEvent();
bool BtnACT();
void juegito();
void reiniciarJuego();
extern bool pantallaTocada();




#endif