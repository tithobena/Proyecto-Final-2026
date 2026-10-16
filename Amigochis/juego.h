#ifndef JUEGO_H
#define JUEGO_H

#include <Arduino.h>

extern int cantidadDeLanas;
extern int vidaDelMalditoYHorribleWarden;
extern int Sucri;
extern int casila;
extern int accionesDisp;
extern const byte BTN1;
extern bool Btnpress;
extern bool UD;
extern bool empiezalobueno;
extern int casillaActual;

bool QuickEvent();
bool BtnACT();
void juegito();

#endif