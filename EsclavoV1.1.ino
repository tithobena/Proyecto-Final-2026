#include <Arduino.h>
#include <Ultrasonic.h>
Ultrasonic gustavo(9, 10);

/*
 ██████╗ ██████╗ ██╗   ██╗██████╗  ██████╗      ██████╗ ███████╗    ██████╗ ██╗ ██████╗ ██╗██╗  ██╗
██╔════╝ ██╔══██╗██║   ██║██╔══██╗██╔═══██╗    ██╔═████╗╚════██║    ██╔══██╗██║██╔═══██╗██║╚██╗██╔╝
██║  ███╗██████╔╝██║   ██║██████╔╝██║   ██║    ██║██╔██║    ██╔╝    ██████╔╝██║██║   ██║██║ ╚███╔╝ 
██║   ██║██╔══██╗██║   ██║██╔═══╝ ██║   ██║    ████╔╝██║   ██╔╝     ██╔═══╝ ██║██║   ██║██║ ██╔██╗ 
╚██████╔╝██║  ██║╚██████╔╝██║     ╚██████╔╝    ╚██████╔╝   ██║      ██║     ██║╚██████╔╝██║██╔╝ ██╗
 ╚═════╝ ╚═╝  ╚═╝ ╚═════╝ ╚═╝      ╚═════╝      ╚═════╝    ╚═╝      ╚═╝     ╚═╝ ╚═════╝ ╚═╝╚═╝  ╚═╝                                                    
                                                                 Codigo Esclavo V1.1 Para A.NANO*/

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
int pepe = -1; //numero de la hotbar

//=======================================
//  Bools para el io
//=======================================
bool juegoIncia;
bool QuickEventJuanitoTech()
{
  delay(1000);
  unsigned long ttts = millis();
  // Gran Chisitos es un numerorandom, que representa el tiempo en milisegundos que tiene el jugador para presionar el boton
  float granChisitos = random(150, 250);
  int jaimito = -1;
  //ereal = "";
  while (jaimito == -1){
    // te ODIO, copilot
    // hola chicos, manuelito2 es el tiempo en milisegundos que ha pasado desde que empezo el evento
  unsigned long manuelito2 = millis() - ttts;
  manuelito2 = map(manuelito2, 0, 1000, 0, 400) / 4;
  Serial.println(String(manuelito2) + "<->" + String(granChisitos));
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
  }
  return jaimito == 1? true : false;
}
bool ULTRASonicJbCOMPANY()
{
  float chomber = gustavo.read();
  if (chomber > 7)
    return true;
  if (juegoIncia)
    return true;
  return false;
}
bool BtnACT() //Valor booleano que indica si el boton esta presionado o no
{
  if (digitalRead(12) == HIGH){ //si me tocan xdd
  if (Jamon)    {
      Jamon = false;
      return true;
    }
      return false;
  }
  Jamon = true;
  return false;
}
//=======================================
//  Variables de juego
//=======================================
int accionesDisp = 1; //Cantidad de acciones disponibles (o turnos) por ronda
bool empiezalobueno = true; //
void juegito() {
  //Espada
    if (DiplaSelct(1) && BtnACT())    {
      vidaDelMalditoYHorribleWarden -= 25;
      accionesDisp--;
      
      Serial.println(String("W") + vidaDelMalditoYHorribleWarden);
    }

    //Arco
    if (DiplaSelct(2) && BtnACT())    {
      vidaDelMalditoYHorribleWarden -= QuickEventJuanitoTech()? 50 : 0;
      accionesDisp--;
      Serial.println(String("W") + vidaDelMalditoYHorribleWarden);
      //use la misma mrd xd
    }

    //Bife
    if (DiplaSelct(3) && BtnACT())    {
      Sucri += 3;
      accionesDisp--;
      Serial.println(String("V") + Sucri);
    }

    //Lana
    if (DiplaSelct(4) && BtnACT())    {
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

bool DiplaSelct(int e) {//<-- vro es sans ahora
  return pepe == e + 1;
}
void setup() {
  Serial.begin(9600);
  pinMode(12, INPUT);
}

void loop() {
  juegoIncia = ULTRASonicJbCOMPANY();
  while(juegoIncia || ){
  //se fija si hay serial (cereal cremoso con yougr la serenisima)
  if (Serial.available() > 0)  {
    pepe = Serial.read();
    Serial.println(String("IUNO:") + pepe);
  }
  //modo rico (empeza el juego)
  if (accionesDisp != 0) {  //si es 0 termina tu turno
    
    if (Sucri <= 0) { //si te moris
      //temoristexddxd
      Serial.println("V0");
      juegoIncia = false;
      }
    else {
      //no te moris xdxdxxd
      if (vidaDelMalditoYHorribleWarden > 0) {
        juegito();
      }
      else {
        Serial.println("ganastebro");
        juegoIncia = false;
      }
    }
}else {
    if (empiezalobueno)
    {
    empiezalobueno = false;
    Sucri -= QuickEventJuanitoTech()? 0 : 6; //re tryhard xddddd
    Serial.println(String("V") + Sucri);
    accionesDisp = 1;
    empiezalobueno = true;
    }
  }
  }
}

