
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
#include <Arduino.h>       //Librerias
#include <Ultrasonic.h>    //Librerias
#include <Adafruit_GFX.h>  //Librerias
#include <MCUFRIEND_kbv.h> //Librerias
#include <TouchScreen.h>   //Librerias
#include <Servo.h>
#include <math.h>
#include "pantalla.h"      //Modulos
#include "juego.h"         //Modulos

const byte YP = A2;  const byte XM = A3;  //Pines del tactil
const byte YM = 8;   const byte XP = 9;   //Pines del tactil
const byte PIN_TRIGGER = 22;    //Pines Sensor ultrasonido
const byte PIN_ECHO    = 23;    //Pines Sensor ultrasonido
const byte BTN1        = 24;    //Pines Boton
const byte Ssignal     = 44;    //BerlinSans
const TSPoint TiraLed  = TSPoint(40, 41, 43); //athos es una cordenada

//=======================================
//  Variables de vida y recursos
//=======================================
bool Btnpress = false;
int casillaActual = 0; 
int casila = 0;
bool UD = false;
bool empiezalobueno = true;
EstadoJuego estado = MENU_INICIO;
bool Remember24 = false; // Referenia a End Of Beggining - Djo

//Declaraciones UwU
Ultrasonic gustavo(PIN_TRIGGER, PIN_ECHO);
MCUFRIEND_kbv pantalla;
TouchScreen tactil(XP, YP, XM, YM, 300); // XP, YP, XM, YM, resistencia
Servo BerlinSans;

bool ULTRASonicJbCOMPANY() {
  if (gustavo.read() < 5  && !UD)  {
    UD = true;
    Serial.println("LOG:A");
    BerlinSans.write(90);
    return true;
  } else if(UD)  {
    //Serial.println("LOG:B"); //delay(1000);
    return true;
  } else  {
    BerlinSans.write(0);
    Serial.println("LOG:C");
    return false;
  }
}

void setup() {
  Serial.begin(9600); 
  BerlinSans.attach(Ssignal);

  pinMode(TiraLed.x, OUTPUT);  
  pinMode(TiraLed.y, OUTPUT);
  pinMode(TiraLed.z, OUTPUT);

  //Configuramos y encendemos la pantalla
  uint16_t ID = pantalla.readID();
  if (ID == 0xD3D3) ID = 0x9486; 
  pantalla.begin(ID);
  pantalla.setRotation(1); //ponemos la pantalla en horizontal (como debe ir en la caja)
  pantalla.fillScreen(NEGRO_GRIS); //pintamos todo el fondo (de la pantalla)
  dibujarMenuInicio();
}

void loop() {
  
  switch (estado) {
    case MENU_INICIO:
      if (pantallaTocada()) {
        reiniciarJuego();
        estado = JUGANDO;
        dibujarJuego();   // dibuja fondo + iconos en el mismo toque
        delay(300);
      }
      break;
    case JUGANDO:
      jugar();
      break;
    case VICTORIA:
    case DERROTA:
      if (pantallaTocada()) {
        estado = MENU_INICIO;
        dibujarMenuInicio();
        delay(300);
      }
      break;
  }
}
void jugar() {
  graficarVida(vidaDelMalditoYHorribleWarden, 250, 40, COLOR_SELECCION);
  leerToque();
  int totalBarras = (Sucri + 19) / 20; // Redondeo hacia arriba para incluir el residuo
  for (int C = 0; C < totalBarras; C++) {
      int vidaEnBarra = Sucri - (C * 20);
      if (vidaEnBarra > 20) {
          vidaEnBarra = 20;
      }
      int yPos = 180 - (C * 20);
      graficarVida(vidaEnBarra, 20, yPos, 0xF800);
  }
  if (Sucri <= 0) {
    Serial.println("V0");
    estado = DERROTA;
    dibujarDerrota();
    delay(300);
    return;
  }
  if (vidaDelMalditoYHorribleWarden <= 0) {
    Serial.println("ganastebro");
    estado = VICTORIA;
    dibujarVictoria();
    delay(300);
    return;
  }

  if (ULTRASonicJbCOMPANY() == true) {
    if (accionesDisp != 0) {
      juegito();
    } else if (empiezalobueno) {
      turnoMan(false);
      digitalWrite(TiraLed.y, 1);
      digitalWrite(TiraLed.z, 1);
      BerlinSans.write(95);
      empiezalobueno = false;
      Sucri -= QuickEvent() ? 0 : 8;
      Serial.println(String("V") + Sucri);
      accionesDisp = 1;
      empiezalobueno = true;
      digitalWrite(TiraLed.y, 0);
      digitalWrite(TiraLed.z, 0);
    }
  }
}

 // pantalla.fillScreen(COLOR_FONDO); //pintamos todo el fondo (de la pantalla)
  //Dibujamos 9 casillas cuando arranca el Arduino (que fiaca 9 veces el mismo comando)
  /*for (int i = 0; i < Cntcudritos; i++) {
    bool estaSeleccionada = (i == casillaActual);
    dibujarCasilla(i, estaSeleccionada);
  }
}

void loop() {
  graficarVida(Sucri, 20, 180, 0x8000);
  graficarVida(vidaDelMalditoYHorribleWarden, 250, 40, COLOR_SELECCION);
  leerToque();
  if (Sucri > 20){
    vidaDelMalditoYHorribleWarden -= Sucri - 20;
    Sucri = 20;
  }
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
}*/

