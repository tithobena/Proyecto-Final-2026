#include "juego.h"
//=======================================
//  Funciones
//=======================================
//==QUICKEVENT
bool QuickEvent() { //minijuego de reacción/precisión con tiempo límite
  delay(1000);
  unsigned long ttts = millis();
  float ExpClkTm = random(150, 250); //cambie la variable a ExpClkTm para que sea mas entendible, juani no me pegues
  int Ganaste = -1;
  //%%%%%%%%%%IMPORTANTE%%%%%%%%%%%Tarea
  //graficar la barra de 0 a 312, y que haya una linea (ExpClkTm)
  //%%%%%%%%%%IMPORTANTE%%%%%%%%%%%
  while (Ganaste == -1){
  unsigned long Ttranscurrido = millis() - ttts;//Ttranscurrido es el tiempo en milisegundos que ha pasado desde que empezo el evento
  Ttranscurrido = map(Ttranscurrido, 0, 1000, 0, 480) / 4;
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
  return Ganaste == 1;
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

  if (casila == 1 && BtnACT())    {
      vidaDelMalditoYHorribleWarden -= 25;
      accionesDisp--;
      Serial.println(String("W") + vidaDelMalditoYHorribleWarden);
    }

    //Arco
    if (casila == 2 && BtnACT())    {
      vidaDelMalditoYHorribleWarden -= QuickEvent()? 50 : 0;
      accionesDisp--;
      Serial.println(String("W") + vidaDelMalditoYHorribleWarden);
      //use la misma mrd xd
    }
    //Bife
    if (casila == 3 && BtnACT())    {
      Sucri += 4;
      vidaDelMalditoYHorribleWarden -= 10;
      accionesDisp--;
      Serial.println(String("V") + Sucri);
      Serial.println(String("W") + vidaDelMalditoYHorribleWarden);
    }
    //Lana
    if (casila == 4 && BtnACT())    {
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