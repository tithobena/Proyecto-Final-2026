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
    Ttranscurrido = map(Ttranscurrido, 0, 1000, 0, 480) / 4;
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
          } else {
            vidaDelMalditoYHorribleWarden -= 40;
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
  int altoBarra = 80;
  int xBarra = (480 - anchoBarra) / 2;
  int yBarra = (320 - altoBarra) / 2 - 30;
  pantalla.fillRect(xBarra - 5, yBarra - 5, anchoBarra + 10, altoBarra + 10, COLOR_FONDO);
  return (Ganaste == 1);
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

  // Espada
  if (casila == 0 && BtnACT()) {
    BerlinSans.write(85);
    digitalWrite(TiraLed.x, HIGH);
    vidaDelMalditoYHorribleWarden -= 25;
    accionesDisp--;
    Serial.println(String("W") + vidaDelMalditoYHorribleWarden);
    delay(300);
    BerlinSans.write(90);
    digitalWrite(TiraLed.x, LOW);
  }

  // Arco
  if (casila == 1 && BtnACT()) {
    digitalWrite(TiraLed.z, HIGH);
    vidaDelMalditoYHorribleWarden -= QuickEvent() ? 49 : 0;
    accionesDisp--;
    Serial.println(String("W") + vidaDelMalditoYHorribleWarden);
    digitalWrite(TiraLed.z, LOW);
  }

  // Bife
  if (casila == 2 && BtnACT()) {
    digitalWrite(TiraLed.y, HIGH);
    if (Sucri + 3 > 20) {
      Sucri = int(((Sucri + 3) - 20) * 0.3);
    } else {
      Sucri += 3;
    }
    vidaDelMalditoYHorribleWarden -= 6;
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
  cantidadDeLanas = 5;
  vidaDelMalditoYHorribleWarden = 400;
  Sucri = 20;
  accionesDisp = 1;
  casillaActual = 0;
  casila = 0;
  UD = false;
  empiezalobueno = true;
  Btnpress = false;
  baiaba = objectos[casila];
}
