#include <Arduino.h>
/*
 ██████╗ ██████╗ ██╗   ██╗██████╗  ██████╗      ██████╗ ███████╗    ██████╗ ██╗ ██████╗ ██╗██╗  ██╗
██╔════╝ ██╔══██╗██║   ██║██╔══██╗██╔═══██╗    ██╔═████╗╚════██║    ██╔══██╗██║██╔═══██╗██║╚██╗██╔╝
██║  ███╗██████╔╝██║   ██║██████╔╝██║   ██║    ██║██╔██║    ██╔╝    ██████╔╝██║██║   ██║██║ ╚███╔╝ 
██║   ██║██╔══██╗██║   ██║██╔═══╝ ██║   ██║    ████╔╝██║   ██╔╝     ██╔═══╝ ██║██║   ██║██║ ██╔██╗ 
╚██████╔╝██║  ██║╚██████╔╝██║     ╚██████╔╝    ╚██████╔╝   ██║      ██║     ██║╚██████╔╝██║██╔╝ ██╗
 ╚═════╝ ╚═╝  ╚═╝ ╚═════╝ ╚═╝      ╚═════╝      ╚═════╝    ╚═╝      ╚═╝     ╚═╝ ╚═════╝ ╚═╝╚═╝  ╚═╝                                                    
                                                                 Codigo Esclavo V1.1 Para A.NANO*/
//=======================================
//  I/O Con pantalla y botones
//=======================================
bool BtnActpre; //Valor booleano que indica si el boton esta presionado o no
int pepe = -1; //numero de la hotbar
bool BtnACT = !BtnActpre; //la inversa usando !, esta mas rico que "jamon()"
//=======================================
//  Variables de juego
//=======================================
int accionesDisp = 1; //Cantidad de acciones disponibles (o turnos) por ronda
bool empiezalobueno = true; //
//=======================================
//  Variables de vida y recursos
//=======================================
int cantidadDeLanas = 3;
int vidaDelMalditoYHorribleWarden = 200;
int Sucri = 20; //es la vida por si revisan este codigo, gord@s

bool DiplaSelct(int e) {//<-- vro es sans ahora
  return ASSApepe == e + 1;
}



void setup() {
  Serial.begin(9600);
  pinMode(12, INPUT);
}

void loop() {
  BtnACT = digitalRead(12); 
  if (Serial.available() > 0)  {
    pepe = Serial.read();
    Serial.println(String("granpepe") + pepe);
  }
  if (accionesDisp != 0) {

    //Espada
    if (DiplaSelct(1) && BtnACT)    {
      vidaDelMalditoYHorribleWarden -= 25;
      accionesDisp--;
      
      Serial.println(String("W") + vidaDelMalditoYHorribleWarden);
    }

    //Arco
    if (DiplaSelct(2) && BtnACT)    {
      vidaDelMalditoYHorribleWarden -= QuickEventJuanitoTech()? 50 : 0;
      accionesDisp--;
      Serial.println("W" + vidaDelMalditoYHorribleWarden);
      //use la misma mrd xd
    }

    //Bife
    if (DiplaSelct(3) && BtnACT)    {
      Sucri += 3;
      accionesDisp--;
      Serial.println(String("Vida:") + Sucri);
    }

    //Lana
    if (DiplaSelct(4) && BtnACT)
    {
      if (cantidadDeLanas > 0) {
      accionesDisp = 2;
      cantidadDeLanas--;
      Serial.println("AC:" + String(accionesDisp));
      }else {
        Serial.println("nlana");
      }
    }
}else {
    if (empiezalobueno)
    {
    empiezalobueno = false;
    Sucri -= QuickEventJuanitoTech()? 0 : 6; //re tryhard xddddd
    Serial.println(String("Vida: ") + Sucri);
    accionesDisp = 1;
    empiezalobueno = true;
    }
  }

}

bool QuickEventJuanitoTech()
{
  delay(1000);
  unsigned long ttts = millis();
  float granChisitos = random(150, 250);
  int jaimito = -1;
  //ereal = "";
  while (jaimito == -1){
  unsigned long manuelito2 = millis() - ttts;
  manuelito2 = map(manuelito2, 0, 1000, 0, 400) / 4;
  Serial.println(String(manuelito2) + "<->" + String(granChisitos));
  if (BtnACT)
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
