/*
 ██████╗ ██████╗ ██╗   ██╗██████╗  ██████╗      ██████╗ ███████╗    ██████╗ ██╗ ██████╗ ██╗██╗  ██╗
██╔════╝ ██╔══██╗██║   ██║██╔══██╗██╔═══██╗    ██╔═████╗╚════██║    ██╔══██╗██║██╔═══██╗██║╚██╗██╔╝
██║  ███╗██████╔╝██║   ██║██████╔╝██║   ██║    ██║██╔██║    ██╔╝    ██████╔╝██║██║   ██║██║ ╚███╔╝ 
██║   ██║██╔══██╗██║   ██║██╔═══╝ ██║   ██║    ████╔╝██║   ██╔╝     ██╔═══╝ ██║██║   ██║██║ ██╔██╗ 
╚██████╔╝██║  ██║╚██████╔╝██║     ╚██████╔╝    ╚██████╔╝   ██║      ██║     ██║╚██████╔╝██║██╔╝ ██╗
 ╚═════╝ ╚═╝  ╚═╝ ╚═════╝ ╚═╝      ╚═════╝      ╚═════╝    ╚═╝      ╚═╝     ╚═╝ ╚═════╝ ╚═╝╚═╝  ╚═╝                                                    
                                                                 Codigo Pantalla V1.5 Para A.MEGA
===============================
Este es el Codigo final, PERO MEJOR
porfa, no falles
===============================

chiquilines usen VS Arduino, C/C++, C dev kit como tengo yo
instalen AVR boards para que aparezca el arduino 
para compilar este codigo, y no se olviden de poner la placa Arduino Nano
para librerias de arduino usen Ultrasonic de Erick Simões, Adafruit GFX Library,
LCDtouch, Adafruit ILI9341, servo de michael margolis y MCUFRIEND_kbv.
*/

//Librerias
#include <Arduino.h>
#include <Ultrasonic.h>
#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>
#include <TouchScreen.h>

//Modulos
#include "pantalla.h"
#include "juego.h"

//Pines Sensor ultrasonido
const byte PIN_TRIGGER = 22;
const byte PIN_ECHO    = 23;

//Pines botones
const byte BTN1        = 24;

//Pines LEDs

//=======================================
//  Variables de vida y recursos
//=======================================
int cantidadDeLanas = 3;
int vidaDelMalditoYHorribleWarden = 200;
int Sucri = 20; //es la vida por si revisan este codigo, ###### (insulto obviado) 
bool Btnpress = true;
int casillaActual = 0; 
int casila = -1;
bool UD = false;
int accionesDisp = 1; //Cantidad de acciones disponibles (o turnos) por ronda
bool empiezalobueno = true;
//Declaraciones UwU
Ultrasonic gustavo(PIN_TRIGGER, PIN_ECHO);
MCUFRIEND_kbv pantalla;
TouchScreen tactil(9, A2, A3, 8, 300); // XP, YP, XM, YM, resistencia


//==Juani QUE ES ESTO
bool ULTRASonicJbCOMPANY() {
  if (gustavo.read() < 5  && !UD)  {
    UD = true;
    Serial.println("LOG:A");
    return true;
  } else if(UD)  {
    //Serial.println("LOG:B"); //delay(1000);
    return true;
   
  } else  {
     
    Serial.println("LOG:C");
    return false;
  }
}


void setup() {
  Serial.begin(9600); 
  //Configuramos y encendemos la pantalla
  uint16_t ID = pantalla.readID();
  if (ID == 0xD3D3) ID = 0x9486; 
  pantalla.begin(ID);
  pantalla.setRotation(1); //ponemos la pantalla en horizontal (como debe ir en la caja)
  pantalla.fillScreen(COLOR_FONDO); //pintamos todo el fondo (de la pantalla)
  //Dibujamos 9 casillas cuando arranca el Arduino (que fiaca 9 veces el mismo comando)
  for (int i = 0; i < Cntcudritos; i++) {
    bool estaSeleccionada = (i == casillaActual);
    //dibujarCasilla(i, estaSeleccionada);
  }
}

void loop() {
  leerToque();
  //==
  if (ULTRASonicJbCOMPANY() == true) {
    if (accionesDisp != 0) {  //si es 0 termina tu turno
      if (Sucri <= 0) { //si te moris
        Serial.println("V0");
        UD = false;
        }
      else {
        if (vidaDelMalditoYHorribleWarden > 0) {
          juegito();
        }
        else {
          Serial.println("ganastebro");
          UD = false;
        }
      }
    } else {
      if (empiezalobueno)  {
        empiezalobueno = false;
        Sucri -= QuickEvent()? 0 : 6; //re tryhard xddddd
        Serial.println(String("V") + Sucri);
        accionesDisp = 1;
        empiezalobueno = true;
      }
    }
  }
}

