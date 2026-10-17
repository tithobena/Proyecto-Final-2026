#include "juego.h"
#include "pantalla.h" // Se agrega para poder invocar graficarQuickEvent

int cantidadDeLanas = 3;
int vidaDelMalditoYHorribleWarden = 250;
int Sucri = 20;
int accionesDisp = 1;

// Resto de tu código en juego.cpp...
//=======================================
//  Funciones
//=======================================
//==QUICKEVENT
bool QuickEvent() { //minijuego de reacción/precisión con tiempo límite
  float ExpClkTm = random(150, 250); //cambie la variable a ExpClkTm para que sea mas entendible, juani no me pegues
  graficarQuickEvent(0, ExpClkTm, 30);
  delay(1000);
  unsigned long ttts = millis();
  int Ganaste = -1;
  //%%%%%%%%%%IMPORTANTE%%%%%%%%%%%Tarea
  //graficar la barra de 0 a 312, y que haya una linea (ExpClkTm)
  //%%%%%%%%%%IMPORTANTE%%%%%%%%%%%
  
  while (Ganaste == -1){
  unsigned long Ttranscurrido = millis() - ttts;//Ttranscurrido es el tiempo en milisegundos que ha pasado desde que empezo el evento
  Ttranscurrido = map(Ttranscurrido, 0, 1000, 0, 480) / 4;
  graficarQuickEvent(Ttranscurrido, ExpClkTm, 30);
  //%%%%%%%%%%IMPORTANTE%%%%%%%%%%%Tarea
  //Hacer que avanze la barra
  //%%%%%%%%%%IMPORTANTE%%%%%%%%%%%
  Serial.println(String(Ttranscurrido) + "/" + ExpClkTm + "/ 312");
  if (BtnACT())  { //BTNACT ES OBSOLETO
    if (Ttranscurrido > ExpClkTm - 20 && Ttranscurrido < ExpClkTm + 20)    {
      Ganaste = 1; 
    }else{
      Ganaste = 0;
    }
  }
  if (Ttranscurrido > 312)  {
    Ganaste = 0;
    }
  delay(20);
  }
    int anchoBarra = 312;
  int altoBarra = 80;
  int xBarra = (480 - anchoBarra) / 2;
  int yBarra = (320 - altoBarra) / 2 - 30;
  pantalla.fillRect(xBarra - 5, yBarra - 5, anchoBarra + 10, altoBarra + 10, COLOR_FONDO);
  return (Ganaste == 1);
}


//==BTNACT
bool BtnACT(){ //Valor booleano que indica si el boton esta presionado o no
  if (digitalRead(BTN1) == HIGH){ //si me tocan xdd
  if (Btnpress)    {
      Btnpress = false;
      return true;
    }
      return false;
  }
  Btnpress = true;
  return false;
}


//===============================
//  JUEGITO
//===============================
void juegito() {
  //Espada

  if (casila == 0 && BtnACT())    {
      vidaDelMalditoYHorribleWarden -= 25;
      accionesDisp--;
      Serial.println(String("W") + vidaDelMalditoYHorribleWarden);
    }

    //Arco
    if (casila == 1 && BtnACT())    {
      vidaDelMalditoYHorribleWarden -= QuickEvent()? 50 : 0;
      accionesDisp--;
      Serial.println(String("W") + vidaDelMalditoYHorribleWarden);
      //use la misma mrd xd
    }
    //Bife
    if (casila == 2 && BtnACT())    {
      Sucri += 4;
      vidaDelMalditoYHorribleWarden -= 10;
      accionesDisp--;
      Serial.println(String("V") + Sucri);
      Serial.println(String("W") + vidaDelMalditoYHorribleWarden);
    }
    //Lana
    if (casila == 3 && BtnACT())    {
      if (cantidadDeLanas > 0) {
      accionesDisp = 2;
      cantidadDeLanas--;
      Serial.println("Cl" + String(cantidadDeLanas));
      Serial.println("A" + String(accionesDisp));
      }else {
        Serial.println("Cln");
      }
    }
}
void reiniciarJuego() {
  cantidadDeLanas = 3;
  vidaDelMalditoYHorribleWarden = 250;
  Sucri = 20;
  accionesDisp = 1;
  casillaActual = 0;
  casila = -1;
  UD = false;
  empiezalobueno = true;
  Btnpress = true;
}