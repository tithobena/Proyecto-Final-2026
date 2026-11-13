#include "WString.h"
#include "Arduino.h"
#include "juego.h"
#include "pantalla.h" // Para poder invocar graficarQuickEvent y demas funciones de pantalla

//=======================================
//  Variables globales del juego
//=======================================
int cantidadDeLanas = 5;
int vidaDelMalditoYHorribleWarden = 400;
int Sucri = 20;
int accionesDisp = 1;
bool LanaUsable = true;

//=======================================
//  QUICKEVENT
//=======================================
// Minijuego de reaccion/precision con tiempo limite
bool QuickEvent() {
  float ExpClkTm = random(125, 275);
  dibujarFondoQuickEvent(ExpClkTm, 30);
  actualizarCursorQuickEvent(0, 0, ExpClkTm, 30); // Posicion inicial en 0
  delay(1000);

  unsigned long ttts = millis();
  int Ganaste = -1;
  unsigned long ultimoTtranscurrido = 0;

  while (Ganaste == -1) {
    unsigned long Ttranscurrido = millis() - ttts;
    Ttranscurrido = map(Ttranscurrido, 0, 1000, 0, 480) / 2;
    if (Ttranscurrido != ultimoTtranscurrido) {
      actualizarCursorQuickEvent(ultimoTtranscurrido, Ttranscurrido, ExpClkTm, 30);
      ultimoTtranscurrido = Ttranscurrido;
    }
    Serial.println(String(Ttranscurrido) + "/" + ExpClkTm + "/ 312");

    if (BtnACT() || pantallaTocada()) {
      if (Ttranscurrido > ExpClkTm - 10 && Ttranscurrido < ExpClkTm + 10) {
        if (Ttranscurrido == ExpClkTm) {
          if (casila != 2) {
            vidaDelMalditoYHorribleWarden -= 120;
            dibujarDan(false, 120, false);
          } else {
            vidaDelMalditoYHorribleWarden -= 40;
            dibujarDan(false, 40, false);
          }
        }
        Ganaste = 1;
      } else {
        Ganaste = 0;
      }
    }
    if (Ttranscurrido > 312) {
      Ganaste = 0;
    }
  }
  
  // Borra la barra del minijuego
  int anchoBarra = 312;
  int altoBarra = 88;
  int xBarra = (480 - anchoBarra) / 2;
  int yBarra = (320 - altoBarra) / 2 - 30;
  pantalla.fillRect(xBarra - 5, yBarra - 5, anchoBarra + 10, altoBarra + 10, COLOR_FONDO);
  return (Ganaste == 1);
}
bool InQuickEvent()
{
  long Ttranscurrido;
  long tutus = millis();
  int banana = 0;
  
  const int anchoBarra = 312;
  const int altoBarra = 80;
  int xBarra = (480 - anchoBarra) / 2;
  int yBarra = (320 - altoBarra) / 2;
  
  long Poso = 0;
  long ultimoPoso = 0;
  float Velocity = 0; //acaxo esto es un nuevx verity
  float Experofafoiso = random(50, anchoBarra - 50);
  
  actualizarCursorQuickEvent(0, 0, Experofafoiso, 30);
  dibujarFondoQuickEvent(Experofafoiso, 30, anchoBarra, altoBarra);
  pantalla.setCursor((anchoBarra / 2) - 30, altoBarra - 10);
  pantalla.setTextColor(COLOR_BORDE);
  pantalla.setTextSize(2);
  pantalla.print("Estas Atragantao");
  while(banana != 3)
  {
    Ttranscurrido = millis() - tutus;
    
    if(Poso > 0)
    {
      if(Velocity < 4)
        Velocity += 0.1;
      Poso -= (long)Velocity;
    }
    else
    {
      Velocity = 0;
    }
    
    if (BtnACT())
    {
      Velocity = 0;
      Poso += 30;
      if (Poso > anchoBarra)
      {
        Poso = anchoBarra;
      }
      if (Poso > Experofafoiso - 10 && Poso < Experofafoiso + 10)
      {
        banana++;
        Experofafoiso = random(50, anchoBarra - 50);
        dibujarFondoQuickEvent(Experofafoiso, 30, anchoBarra, altoBarra);
      }
      delay(30);
    }
    
    if (Poso < 0)
    {
      Poso = 0;
    }
    else if (Poso > anchoBarra) 
    {
      Poso = anchoBarra;
    }
    
    if (Poso != ultimoPoso) {
      actualizarCursorQuickEvent(ultimoPoso, Poso, Experofafoiso, 30);
      ultimoPoso = Poso;
    }
    
    pantalla.setCursor(xBarra, yBarra - 20);
    pantalla.setTextSize(2.5);
    pantalla.setTextColor(COLOR_SELECCION);
    pantalla.print(String("T:") + (15 - (Ttranscurrido / 1000)));
    pantalla.setCursor(xBarra, yBarra - 20);
    pantalla.setTextSize(2.5);
    pantalla.setTextColor(NEGRO_GRIS);
    pantalla.print(String("T:") + (15 - (Ttranscurrido / 1000)));
    if (Ttranscurrido > 15000) 
    {
      pantalla.fillRect(xBarra - 5, yBarra - 50, anchoBarra + 10, altoBarra + 50, COLOR_FONDO);
      return false;
    }
  }
  pantalla.fillRect(xBarra - 5, yBarra - 50, anchoBarra + 10, altoBarra + 50, COLOR_FONDO);
  return true;
}
bool EXPOQuick()
{
  long Ttranscurrido;
  float Experofafoiso = random(280, 310); //es Como ExpClkTm
  long tutus;
  long ultimoTtranscurrido = 0;
  actualizarCursorQuickEvent(0, 0, Experofafoiso, 30);
  dibujarFondoQuickEvent(Experofafoiso, 30);
  delay(300);
  while(digitalRead(BTN1) == LOW)
  {
    //espera los churros de churreria juanitoPancherias.Co
    Serial.println("crayola");
    tutus = millis();
    delay(10);
  }
  while (digitalRead(BTN1) == HIGH) {
  Serial.println("esto es temporal viejo");
  }
  while(digitalRead(BTN1) == LOW)
  {
    Serial.println("amaM no me dijiste que nos ibamos a lo de los abuelos");
    Ttranscurrido = millis() - tutus;
    Ttranscurrido = map(Ttranscurrido, 0, 1000, 0, 480) / 10; 
    Ttranscurrido = (Ttranscurrido * Ttranscurrido) / 10;
    Serial.println(String("Hola:") + Ttranscurrido + ":" + Experofafoiso);
    if (Ttranscurrido != ultimoTtranscurrido) 
    {
      actualizarCursorQuickEvent(ultimoTtranscurrido, Ttranscurrido, Experofafoiso, 30);
      ultimoTtranscurrido = Ttranscurrido;
    }
    if (Ttranscurrido > 312)
    {
      int anchoBarra = 312;
      int altoBarra = 80;
      int xBarra = (480 - anchoBarra) / 2;
      int yBarra = (320 - altoBarra) / 2;
      pantalla.fillRect(xBarra - 5, yBarra - 5, anchoBarra + 10, altoBarra + 10, COLOR_FONDO);
      return false;
    }
  }
  if (Ttranscurrido < Experofafoiso + 10 && Ttranscurrido > Experofafoiso - 10)
  {
    if (Ttranscurrido == Experofafoiso)
    {
      vidaDelMalditoYHorribleWarden -= 40;
    }
    int anchoBarra = 312;
    int altoBarra = 80;
    int xBarra = (480 - anchoBarra) / 2;
    int yBarra = (320 - altoBarra) / 2;
    pantalla.fillRect(xBarra - 5, yBarra - 5, anchoBarra + 10, altoBarra + 10, COLOR_FONDO);
    return true;
  }
  return false;
}
//=======================================
//  BTNACT
//=======================================
// Indica si el boton fue presionado (flanco: una sola vez por pulsacion)
bool BtnACT() {
  if (digitalRead(BTN1) == HIGH) {
    if (Btnpress) {
      Btnpress = false;
      dibujarCasilla(3, casila == 3, cantidadDeLanas);
      Serial.println("butotucado");
      return true;
    }
    return false;
  }
  Btnpress = true;
  return false;
}

//=======================================
//  JUEGITO (turno del jugador)
//=======================================
void juegito() {
  BerlinSans.write(90);
  if (accionesDisp != 0) {
    turnoMan(true);
  }
  pantalla.setCursor(460, 20);
  pantalla.print(String("Ac:" + accionesDisp));
  pantalla.setCursor(460, 20);
  pantalla.setTextColor(COLOR_FONDO);
  pantalla.print(String("Ac:" + accionesDisp));
  // Espada
  if (casila == 0 && BtnACT()) {
    BerlinSans.write(85);
    digitalWrite(TiraLed.x, HIGH);
    vidaDelMalditoYHorribleWarden -= 25;
    dibujarDan(false, 25, false);
    accionesDisp--;
    Serial.println(String("W") + vidaDelMalditoYHorribleWarden);
    delay(300);
    BerlinSans.write(90);
    digitalWrite(TiraLed.x, LOW);
  }

  // Arco
  if (casila == 1 && BtnACT()) {
    digitalWrite(TiraLed.z, HIGH);
    bool javito = QuickEvent();
    vidaDelMalditoYHorribleWarden -= javito ? 49 : 0;
    dibujarDan(false, javito * 50, false);
    accionesDisp--;
    Serial.println(String("W") + vidaDelMalditoYHorribleWarden);
    digitalWrite(TiraLed.z, LOW);
  }

  // Bife
  if (casila == 2 && BtnACT()) {
    digitalWrite(TiraLed.y, HIGH);
    if ((Sucri + 3) > 20) {
      Sucri = ceil(((Sucri + 3)-20) *0.3) + 20;
      dibujarDan(true, 2, true);
    } else {
      Sucri += 4;
      dibujarDan(true, 4, true);
    }
    int papa = random(0, 15);
    if (papa == 7)
    {
      bool das;
      das = InQuickEvent();
      Sucri -= das ? 0 : 5;
      dibujarDan(true, !(das) * 5, false);
    }
    vidaDelMalditoYHorribleWarden -= 12;
    accionesDisp--;
    Serial.println(String("V") + Sucri);
    Serial.println(String("W") + vidaDelMalditoYHorribleWarden);
    delay(300);
    digitalWrite(TiraLed.y, LOW);
  }

  // Lana
  if (casila == 3 && BtnACT()) {
    digitalWrite(TiraLed.x, HIGH);
    digitalWrite(TiraLed.y, HIGH);
    digitalWrite(TiraLed.z, HIGH);
    if (cantidadDeLanas > 0 && LanaUsable) {
      accionesDisp = 2;
      LanaUsable = false;
      cantidadDeLanas--;
      Serial.println("Cl" + String(cantidadDeLanas));
      Serial.println("A" + String(accionesDisp));
    } else {
      Serial.println("Cln");
      digitalWrite(TiraLed.x, HIGH);
      delay(300);
    }
    digitalWrite(TiraLed.x, LOW);
    digitalWrite(TiraLed.y, LOW);
    digitalWrite(TiraLed.z, LOW);
  }
}

//=======================================
//  REINICIAR JUEGO
//=======================================
void reiniciarJuego() {
  Serial.println("reinic");
  cantidadDeLanas = 5;
  vidaDelMalditoYHorribleWarden = 400;
  Sucri = 20;
  accionesDisp = 1;
  casillaActual = 0;
  casila = 0;
  empiezalobueno = true;
  Btnpress = false;
  baiaba = objectos[casila];
}
