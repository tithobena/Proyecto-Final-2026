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

//=======================================
//  Librerias
//=======================================
#include <Arduino.h>
#include <Ultrasonic.h>
#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>
#include <TouchScreen.h>
#include <Servo.h>
#include <math.h>
#include "teclado.h"
#include "ListLib.h"

Teclado SoyVictimaUnMoutruoMortal;

//=======================================
//  Modulos propios
//  (juego.h debe incluirse antes de las constantes de pines: declara BTN1 y
//  TiraLed como extern para que tengan enlace externo y las vea juego.cpp)
//=======================================
#include "pantalla.h"
#include "juego.h"

//=======================================
//  Pines
//=======================================
// Tactil
const byte YP = A2;
const byte XM = A3;
const byte YM = 8;
const byte XP = 9;

// Sensor ultrasonido
const byte PIN_TRIGGER = 22;
const byte PIN_ECHO    = 23;

// Boton y servo
const byte BTN1    = 24;
const byte Ssignal = 44; // Senal del servo (BerlinSans)

// Tira LED: x, y, z son los 3 pines de salida (no una coordenada real)
const TSPoint TiraLed = TSPoint(19, 20, 21);                                                    

//=======================================
//  Variables de estado del juego
//=======================================
EstadoJuego estado = MENU_INICIO;
bool Btnpress = true;
int casillaActual = 0;
int casila = 0;
bool UD = false;
bool empiezalobueno = true;
bool Remember24 = false; // Referencia a End Of Beginning - Djo
int turn0 = 0;
List<int> ListiPuntos;
List<String> ListiNombres;

//=======================================
//  Objetos de hardware
//=======================================
Ultrasonic gustavo(PIN_TRIGGER, PIN_ECHO);
MCUFRIEND_kbv pantalla;
TouchScreen tactil(XP, YP, XM, YM, 300); // XP, YP, XM, YM, resistencia
Servo BerlinSans;

//=======================================
//  Sensor ultrasonido + servo
//=======================================
bool ULTRASonicJbCOMPANY() {
  if (gustavo.read() < 5 && !UD) {
    UD = true;
    Serial.println("LOG:A");
    BerlinSans.write(90);
    return true;
  } else if (UD) {
    //Serial.println("LOG:B"); //delay(1000);
    return true;
  } else {
    BerlinSans.write(0);
    Serial.println("LOG:C");
    return false;
  }
}
//=======================================
//  Setup
//=======================================
void setup() {
  Serial.begin(9600);
  BerlinSans.attach(Ssignal);

  pinMode(TiraLed.x, OUTPUT);
  pinMode(TiraLed.y, OUTPUT);
  pinMode(TiraLed.z, OUTPUT);

  uint16_t ID = pantalla.readID();
  if (ID == 0xD3D3) ID = 0x9486;
  pantalla.begin(ID);
  pantalla.setRotation(1);          // Horizontal (como debe ir en la caja)
  pantalla.fillScreen(NEGRO_GRIS);  // Pinta todo el fondo

  dibujarMenuInicio();
  accionesDisp = 1;                 // Antes decia "== 1" (comparacion sin efecto)
}

//=======================================
//  Loop principal (maquina de estados)
//=======================================
void loop() {
  switch (estado) {
    case MENU_INICIO:
      if (pantallaTocada()) {
        reiniciarJuego();
        estado = JUGANDO;
        Serial.println("inciojuego");
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
        Serial.println("muenus Inico");
        delay(300);
      }
      break;
  }
}

//=======================================
//  Turno de juego
//=======================================
void jugar() {
  graficarBarraBossWarden(vidaDelMalditoYHorribleWarden, 400);
  leerToque(cantidadDeLanas);

  // Barras de vida del jugador (20 puntos por barra, redondeo hacia arriba)
  int totalBarras = (Sucri + 19) / 20;
  for (int C = 0; C < totalBarras; C++) {
    int vidaEnBarra = Sucri - (C * 20);
    if (vidaEnBarra > 20) {
      vidaEnBarra = 20;
    }
    int yPos = 180 - (C * 20);
    graficarVida(vidaEnBarra, 20, yPos, 0x000);
  }
  vidaDelMalditoYHorribleWarden = vidaDelMalditoYHorribleWarden < 0? 0 : vidaDelMalditoYHorribleWarden;
  int temipuntos = ((400 / vidaDelMalditoYHorribleWarden) -1) + 100;
  int puntos;
  if (temipuntos != puntos)
  {
    pantalla.setTextColor(0xBDF7);
    pantalla.setCursor(402, 61);
    pantalla.setTextColor(COLOR_FONDO);
    pantalla.setTextSize(3);
    pantalla.print(String("P:") + puntos);
  }
  puntos = temipuntos;
  pantalla.setTextColor(0xBDF7);
  pantalla.setCursor(402, 61);
  pantalla.setTextSize(2);
  pantalla.print(String("P:") + puntos);
  // Fin de partida
  if (Sucri <= 0) {
    Serial.println("V0");
    estado = DERROTA;
    dibujarDerrota();
    delay(2000);
    String nombresincocinar = SoyVictimaUnMoutruoMortal.pedirTexto("", 15);
    ListiNombres.Add(nombresincocinar);
    ListiPuntos.Add(puntos);
    delay(300);
    DibujarLilVro();
    return;
  }
  if (vidaDelMalditoYHorribleWarden <= 0) {
    Serial.println("ganastebro");
    estado = VICTORIA;
    dibujarVictoria();
    delay(2000);
    String nombresincocinar = SoyVictimaUnMoutruoMortal.pedirTexto("", 15);
    ListiNombres.Add(nombresincocinar);
    ListiPuntos.Add(puntos);
    delay(300);
    DibujarLilVro();
    return;
  }

  if (ULTRASonicJbCOMPANY() == true) {
    if (accionesDisp != 0) {
      juegito();
    } else if (empiezalobueno) { // Turno del Warden
      turn0++;
      turnoMan(false);
      digitalWrite(TiraLed.y, 1);
      digitalWrite(TiraLed.z, 1);
      BerlinSans.write(95);
      empiezalobueno = false;
      bool javio = QuickEvent();
      Sucri -= javio? 0 : 9;
      dibujarDan(true, !(javio) * 9, false);
      Serial.println(String("V") + Sucri);
      accionesDisp = 1;
      empiezalobueno = true;
      digitalWrite(TiraLed.y, 0);
      digitalWrite(TiraLed.z, 0);
      LanaUsable = true;
    }
  }
}
void DibujarLilVro()
{
  pantalla.fillScreen(COLOR_CASILLA);
  pantalla.fillRect(67, -13, 348, 373, 0x10C4);
  pantalla.fillRect(72, 20, 339, 32, 0x4208);
  pantalla.setTextColor(0xFFFF);
  pantalla.setTextSize(2);
  pantalla.setTextWrap(false);
  pantalla.setCursor(84, 31);
  pantalla.print("Nombres");
  pantalla.setTextSize(3);
  pantalla.setCursor(277, 25);
  pantalla.print("Puntos");
  int fifas = min((int)ListiNombres.Count(), (int)ListiPuntos.Count());
  if (fifas > 10) 
    fifas = 10;

  for (int i = 0; i < fifas; i++)
  {
    int y = 58 + i * 26;
    pantalla.fillRect(72, y, 339, 24, 0x4208);
    pantalla.setTextSize(2);
    pantalla.setCursor(84, y + 4);
    pantalla.print(ListiNombres[i]);
    pantalla.setCursor(277, y + 4);
    pantalla.print(ListiPuntos[i]);
  }
  pantalla.fillRect(238, -6, 5, 336, 0xBDF7); 
}
