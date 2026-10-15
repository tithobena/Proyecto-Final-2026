#ifndef JUEGO_H
#define JUEGO_H

#include <Arduino.h>

extern int cantidadDeLanas;
extern int vidaDelMalditoYHorribleWarden;
extern int Sucri;
extern int casila;
extern int accionesDisp;
extern byte BTN1;
extern bool Btnpress;
extern bool UD;
extern bool empiezalobueno;
extern int casillaActual;


int cantidadDeLanas = 3;
int vidaDelMalditoYHorribleWarden = 200;
int Sucri = 20; //es la vida por si revisan este codigo, ###### (insulto obviado) 
int accionesDisp = 1; //Cantidad de acciones disponibles (o turnos) por ronda

bool QuickEvent();
bool BtnACT();
void juegito();

#endif