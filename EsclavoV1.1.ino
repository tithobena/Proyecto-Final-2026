/*
 ██████╗ ██████╗ ██╗   ██╗██████╗  ██████╗      ██████╗ ███████╗    ██████╗ ██╗ ██████╗ ██╗██╗  ██╗
██╔════╝ ██╔══██╗██║   ██║██╔══██╗██╔═══██╗    ██╔═████╗╚════██║    ██╔══██╗██║██╔═══██╗██║╚██╗██╔╝
██║  ███╗██████╔╝██║   ██║██████╔╝██║   ██║    ██║██╔██║    ██╔╝    ██████╔╝██║██║   ██║██║ ╚███╔╝ 
██║   ██║██╔══██╗██║   ██║██╔═══╝ ██║   ██║    ████╔╝██║   ██╔╝     ██╔═══╝ ██║██║   ██║██║ ██╔██╗ 
╚██████╔╝██║  ██║╚██████╔╝██║     ╚██████╔╝    ╚██████╔╝   ██║      ██║     ██║╚██████╔╝██║██╔╝ ██╗
 ╚═════╝ ╚═╝  ╚═╝ ╚═════╝ ╚═╝      ╚═════╝      ╚═════╝    ╚═╝      ╚═╝     ╚═╝ ╚═════╝ ╚═╝╚═╝  ╚═╝                                                    
                                                                 Codigo Esclavo V1.1 Para A.NANO*/


// chiquilines usen VS Arduino, C/C++, C dev kit como tengo yo
// instalen AVR boards para que aparezca el arduino 
// para compilar este codigo, y no se olviden de poner la placa Arduino Nano
// para librerias de arduino usen Ultrasonic de Erick Simões, Adafruit GFX Library,
// LCDtouch, Adafruit ILI9341, servo de michael margolis y MCUFRIEND_kbv.

#include <Arduino.h>
#include <Ultrasonic.h>
Ultrasonic gustavo(9, 10);

int BonosbrutalmenteDevorados[10] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};

void MandarBonoEnString(int bono, int valor = 0) 
{                                                                   
  byte paquete[3];
  paquete[0] = (byte)bono;
  paquete[1] = highByte(valor);
  paquete[2] = lowByte(valor);
  Serial.write(paquete, 3);
}
int BonoRecibido(int bonoesperado)
{
  if (BonosbrutalmenteDevorados[bonoesperado] != -1) {
    int valorGuardado = BonosbrutalmenteDevorados[bonoesperado];
    BonosbrutalmenteDevorados[bonoesperado] = -1;
    return valorGuardado;
  }

  while (Serial.available() >= 3) {
    byte bonoLeido = Serial.read();
    byte alto = Serial.read();
    byte bajo = Serial.read();
    int valorLeido = word(alto, bajo);

    if (bonoLeido == bonoesperado) {
      return valorLeido;
    } else if (bonoLeido >= 1 && bonoLeido <= 9) {
      BonosbrutalmenteDevorados[bonoLeido] = valorLeido; 
    }
  }
  
  return -1;
}

//=======================================
//              Bonos
//=======================================
int Warden = 1;
int Vida = 2;
int ChisitosIn = 3; 
int Manuelito = 5;          // los bonos son como ID para los mensajes
int ADisp = 6;                //tienen un limite del 1 al 9, ya se que es ultramega crocante 
int LanaDisp = 7;
int Hotbar = 8;             //el nombre es porque antes iban a llamarse acciones y un cuasinonimo de eso es bonos :V
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
bool empiezalobueno = true; //println
void juegito() {
  //Espada
    if (DiplaSelct(1) && BtnACT())    {
      vidaDelMalditoYHorribleWarden -= 25;
      accionesDisp--;
      
      MandarBonoEnString(Warden, vidaDelMalditoYHorribleWarden);
    }

    //Arco
    if (DiplaSelct(2) && BtnACT())    {
      vidaDelMalditoYHorribleWarden -= QuickEventJuanitoTech()? 50 : 0;
      accionesDisp--;
      MandarBonoEnString(Warden, vidaDelMalditoYHorribleWarden);
      //use la misma mrd xd
    }

    //Bife
    if (DiplaSelct(3) && BtnACT())    {
      Sucri += 3;
      accionesDisp--;
      MandarBonoEnString(Vida, Sucri);
    }

    //Lana
    if (DiplaSelct(4) && BtnACT())    {
      if (cantidadDeLanas > 0) {
      accionesDisp = 2;
      cantidadDeLanas--;
      MandarBonoEnString(LanaDisp, cantidadDeLanas);
      MandarBonoEnString(ADisp, accionesDisp);
      }else {
        MandarBonoEnString(LanaDisp);
      }
    }
}

bool DiplaSelct(int e) {//<-- vro es sans ahora
  pepe += 1;
  bool resultadoJuanitoTech = pepe == e;
  pepe -= 1;
  return resultadoJuanitoTech;
}
void setup() {
  Serial.begin(9600);
  pinMode(12, INPUT);
  MandarBonoEnString(Vida, Sucri);
}

void loop() {
  juegoIncia = ULTRASonicJbCOMPANY();
  while(juegoIncia){
  //se fija si hay serial (cereal cremoso con yougr la serenisima)
  int debugpepe = BonoRecibido(Hotbar);
  
  // Cambia aca: Logica de asignacion simplificada (BonoRecibido ya revisa el array internamente)
  if (debugpepe != -1) {
    pepe = debugpepe;
  }
    
  //modo rico (empeza el juego)
  if (accionesDisp != 0) {  //si es 0 termina tu turno
    
    if (Sucri <= 0) { //si te moris
      //temoristexddxd
      MandarBonoEnString(Vida, Sucri);
      juegoIncia = false;
      }
    else {
      //no te moris xdxdxxd
      if (vidaDelMalditoYHorribleWarden > 0) {
        juegito();
      }
      else {
        // Serial.println("ganastebro"); // Cambia aca: Comentado para no corromper los paquetes Serial con texto
        juegoIncia = false;
      }
    }
}else {
    if (empiezalobueno)
    {
    empiezalobueno = false;
    Sucri -= QuickEventJuanitoTech()? 0 : 6; //re tryhard xddddd
    MandarBonoEnString(Vida, Sucri);
    MandarBonoEnString(ChisitosIn, 1);
    accionesDisp = 1;
    empiezalobueno = true;
    }
  }
  }
}
