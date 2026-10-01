/*
 ██████╗ ██████╗ ██╗   ██╗██████╗  ██████╗      ██████╗ ███████╗    ██████╗ ██╗ ██████╗ ██╗██╗  ██╗
██╔════╝ ██╔══██╗██║   ██║██╔══██╗██╔═══██╗    ██╔═████╗╚════██║    ██╔══██╗██║██╔═══██╗██║╚██╗██╔╝
██║  ███╗██████╔╝██║   ██║██████╔╝██║   ██║    ██║██╔██║    ██╔╝    ██████╔╝██║██║   ██║██║ ╚███╔╝ 
██║   ██║██╔══██╗██║   ██║██╔═══╝ ██║   ██║    ████╔╝██║   ██╔╝     ██╔═══╝ ██║██║   ██║██║ ██╔██╗ 
╚██████╔╝██║  ██║╚██████╔╝██║     ╚██████╔╝    ╚██████╔╝   ██║      ██║     ██║╚██████╔╝██║██╔╝ ██╗
 ╚═════╝ ╚═╝  ╚═╝ ╚═════╝ ╚═╝      ╚═════╝      ╚═════╝    ╚═╝      ╚═╝     ╚═╝ ╚═════╝ ╚═╝╚═╝  ╚═╝                                                    
                                                                 Codigo Pantalla V1.1 Para A.UNO*/
//===============================
//Este es el Codigo final, uniendo los otros dos anteriores
//porfa, no falles
//===============================

// chiquilines usen VS Arduino, C/C++, C dev kit como tengo yo
// instalen AVR boards para que aparezca el arduino 
// para compilar este codigo, y no se olviden de poner la placa Arduino Nano
// para librerias de arduino usen Ultrasonic de Erick Simões, Adafruit GFX Library,
// LCDtouch, Adafruit ILI9341, servo de michael margolis y MCUFRIEND_kbv.

//Librerias
#include <Arduino.h>
#include <Ultrasonic.h>
#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>
#include <TouchScreen.h>

//Declaraciones UwU
Ultrasonic gustavo(9, 10);

//=======================================
//  Variables de vida y recursos
//=======================================
int cantidadDeLanas = 3;
int vidaDelMalditoYHorribleWarden = 200;
int Sucri = 20; //es la vida por si revisan este codigo, gord@s
//=======================================
//  I/O Con pantalla y botones
//=======================================
bool Jamon = true;
// pepe a muerto, ahora la hotbar esta acargo CasillaSeleccionada

//=======================================
//  Bools para el io
//=======================================
bool juegoIncia;
bool QuickEventJuanitoTech() {
  delay(1000);
  unsigned long ttts = millis();
  // Gran Chisitos es un numerorandom, que representa el tiempo en milisegundos que tiene el jugador para presionar el boton
  float granChisitos = random(150, 250);
  int jaimito = -1;
  MandarBonoEnString(ChisitosIn, granChisitos);
  while (jaimito == -1){
    // te ODIO, copilot
    // hola chicos, manuelito2 es el tiempo en milisegundos que ha pasado desde que empezo el evento
  unsigned long manuelito2 = millis() - ttts;
  manuelito2 = map(manuelito2, 0, 1000, 0, 480) / 4;
  //Serial.println(String(manuelito2) + "<->" + String(granChisitos)); esto es el pasado
  if (BtnACT())
  {
    if (manuelito2 > granChisitos - 25 && manuelito2 < granChisitos + 25)
    {
      jaimito = 1; 
    }else{
      jaimito = 0;
    }
    //Cereal = "";
  }
  if (manuelito2 > 312)
  {
    jaimito = 0;
  }
  delay(20);
  }
  return jaimito == 1? true : false;
}