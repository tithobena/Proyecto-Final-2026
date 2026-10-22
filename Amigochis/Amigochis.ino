/*
 ██████╗ ██████╗ ██╗   ██╗██████╗  ██████╗      ██████╗ ███████╗    ██████╗ ██╗ ██████╗ ██╗██╗  ██╗
██╔════╝ ██╔══██╗██║   ██║██╔══██╗██╔═══██╗    ██╔═████╗╚════██║    ██╔══██╗██║██╔═══██╗██║╚██╗██╔╝
██║  ███╗██████╔╝██║   ██║██████╔╝██║   ██║    ██║██╔██║    ██╔╝    ██████╔╝██║██║   ██║██║ ╚███╔╝ 
██║   ██║██╔══██╗██║   ██║██╔═══╝ ██║   ██║    ████╔╝██║   ██╔╝     ██╔═══╝ ██║██║   ██║██║ ██╔██╗ 
╚██████╔╝██║  ██║╚██████╔╝██║     ╚██████╔╝    ╚██████╔╝   ██║      ██║     ██║╚██████╔╝██║██╔╝ ██╗
 ╚═════╝ ╚═╝  ╚═╝ ╚═════╝ ╚═╝      ╚═════╝      ╚═════╝    ╚═╝      ╚═╝     ╚═╝ ╚═════╝ ╚═╝╚═╝  ╚═╝                                                    
                                                                 Codigo Pantalla V1.5 Para A.MEGA
Este es el Codigo final, PERO MEJOR    para librerias de arduino usen Ultrasonic de Erick Simões, Adafruit GFX Library,
porfa, no falles                       LCDtouch, Adafruit ILI9341, servo de michael margolis y MCUFRIEND_kbv.
=====================================================================================================================*/
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
bool Btnpress = true;
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
  uint16_t ID = pantalla.readID();
  if (ID == 0xD3D3) ID = 0x9486; 
  pantalla.begin(ID);
  pantalla.setRotation(1); //ponemos la pantalla en horizontal (como debe ir en la caja)
  pantalla.fillScreen(NEGRO_GRIS); //pintamos todo el fondo (de la pantalla)
  dibujarMenuInicio();
  accionesDisp == 1;
}

void loop() {
  
  switch (estado) {
    case MENU_INICIO:
      if (pantallaTocada()) {
        reiniciarJuego();
        estado = JUGANDO;
        dibujarJuego();   
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
  graficarBarraBossWarden(vidaDelMalditoYHorribleWarden, 250);
  leerToque(cantidadDeLanas);
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
    } else if (empiezalobueno) { //turno del warden
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
      LanaUsable = true;
    }
  }
}


