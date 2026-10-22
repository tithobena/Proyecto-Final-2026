#include "juego.h"
#include "pantalla.h" // Se agrega para poder invocar graficarQuickEvent

int cantidadDeLanas = 5;
int vidaDelMalditoYHorribleWarden = 250;
int Sucri = 20;
int accionesDisp = 1;
bool LanaUsable = true;

// Resto de tu código en juego.cpp...
//=======================================
//  Funciones
//=======================================
//==QUICKEVENT
bool QuickEvent() { //minijuego de reacción/precisión con tiempo límite
  float ExpClkTm = random(150, 250); 
  dibujarFondoQuickEvent(ExpClkTm, 30);
  actualizarCursorQuickEvent(0, 0, ExpClkTm, 30); // Posición inicial en 0
  delay(1000);
  unsigned long ttts = millis();
  int Ganaste = -1;
  unsigned long ultimoTtranscurrido = 0;
  while (Ganaste == -1){
    unsigned long Ttranscurrido = millis() - ttts;
    Ttranscurrido = map(Ttranscurrido, 0, 1000, 0, 480) / 4;
    if (Ttranscurrido != ultimoTtranscurrido) {
      actualizarCursorQuickEvent(ultimoTtranscurrido, Ttranscurrido, ExpClkTm, 30);
      ultimoTtranscurrido = Ttranscurrido;
    }
    Serial.println(String(Ttranscurrido) + "/" + ExpClkTm + "/ 312");
    if (BtnACT() or pantallaTocada())  { 
      if (Ttranscurrido > ExpClkTm - 15 && Ttranscurrido < ExpClkTm + 15)    {
        if (Ttranscurrido > ExpClkTm - 4 && Ttranscurrido < ExpClkTm + 4)  {
          if (Ttranscurrido == ExpClkTm)  {
            if (casila != 2){
              vidaDelMalditoYHorribleWarden -= 120;
            } else {
              vidaDelMalditoYHorribleWarden -= 40;
            }
          }
          else  {
            if (casila != 2){
              vidaDelMalditoYHorribleWarden -= 35;
            } else {
              vidaDelMalditoYHorribleWarden -= 4;
            }
          }
        }
        Ganaste = 1; 
      } else {
        Ganaste = 0;
      }
    }
    if (Ttranscurrido > 312)  {
      Ganaste = 0;
    }
    delay(8);
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
  BerlinSans.write(90);
  if (accionesDisp != 0) {
    turnoMan(true);
  }
  if (casila == 0 && BtnACT())    {
      BerlinSans.write(85);
      digitalWrite(TiraLed.x, HIGH);
      vidaDelMalditoYHorribleWarden -= 25;
      accionesDisp--;
      Serial.println(String("W") + vidaDelMalditoYHorribleWarden);
      delay(300);
      BerlinSans.write(90);
      digitalWrite(TiraLed.x, LOW);
    }

    //Arco
    if (casila == 1 && BtnACT())    {
      digitalWrite(TiraLed.z, HIGH);
      vidaDelMalditoYHorribleWarden -= QuickEvent()? 50 : 0;
      accionesDisp--;
      Serial.println(String("W") + vidaDelMalditoYHorribleWarden);
      //use la misma mrd xd
      digitalWrite(TiraLed.z, LOW);
    }
    //Bife
    if (casila == 2 && BtnACT())    {
      digitalWrite(TiraLed.y, HIGH);
      Sucri += 3;
      vidaDelMalditoYHorribleWarden -= 8;
      accionesDisp--;
      Serial.println(String("V") + Sucri);
      Serial.println(String("W") + vidaDelMalditoYHorribleWarden);
      delay(300);
      digitalWrite(TiraLed.y, LOW);
    }
    //Lana
    if (casila == 3 && BtnACT())    {
      digitalWrite(TiraLed.x, HIGH);
      digitalWrite(TiraLed.y, HIGH);
      digitalWrite(TiraLed.z, HIGH);
      if (cantidadDeLanas > 0 && LanaUsable) {
      accionesDisp = 2;
      LanaUsable = false;
      cantidadDeLanas--;
      Serial.println("Cl" + String(cantidadDeLanas));
      Serial.println("A" + String(accionesDisp));
      
      }else {
        Serial.println("Cln");
        digitalWrite(TiraLed.x, HIGH);
       delay(300);
      }
      digitalWrite(TiraLed.x, LOW);
      digitalWrite(TiraLed.y, LOW);
      digitalWrite(TiraLed.z, LOW);
    }
}
void reiniciarJuego() {
  cantidadDeLanas = 5;
  vidaDelMalditoYHorribleWarden = 250;
  Sucri = 20;
  accionesDisp = 1;
  casillaActual = 0;
  casila = 0;
  UD = false;
  empiezalobueno = true;
  Btnpress = false;
  baiaba = objectos[casila];
}