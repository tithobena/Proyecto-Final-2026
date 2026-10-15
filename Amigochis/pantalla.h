#ifndef PANTALLA_H
#define PANTALLA_H

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>
#include <TouchScreen.h>

//Hotbar
const byte Cntcudritos = 5;//cuantos cuadraditos pongo
const uint16_t tamanoCasilla = 80;
const uint16_t Anchbarra = Cntcudritos * tamanoCasilla; 
const uint16_t Pxi = (480 - Anchbarra) / 2; //Posicion x inicial (poreso P.X I.)
const uint16_t Pyi = 320 - tamanoCasilla - 20; //Aca lo hacemos separado por 20 de abajo
//colores en formato hexadecimal (RGB565)
const uint16_t COLOR_FONDO     = 0x6595;
const uint16_t COLOR_CASILLA   = 0x4208;
const uint16_t COLOR_BORDE     = 0xAD75;
const uint16_t COLOR_SOMBRA    = 0x2104;
const uint16_t COLOR_SELECCION = 0xFFFF;
const uint16_t NEGRO_GRIS      = 0x31A6;
const uint16_t LIMA_LIMOSO     = 0x07E0;
const uint16_t VERDE_VERDOSO   = 0x0400;

//Vars. externas (andan fuera)

extern MCUFRIEND_kbv pantalla;
extern TouchScreen tactil;
extern int casillaActual;
extern int casila;

void leerToque();
void dibujarCasilla(int numeroDeCasilla, bool estaSeleccionada);
void graficarQuickEvent(unsigned long Ttranscurrido, int ExpClkTm, int altura);
#endif