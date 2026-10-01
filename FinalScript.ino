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
MCUFRIEND_kbv pantalla; 
#define YP A2  
#define XM A3  
#define YM 8   
#define XP 9   
TouchScreen tactil = TouchScreen(XP, YP, XM, YM, 300);

//configs obvios talvez
//Variables para organizar las casillas (la barra de abajo)
const int Cntcudritos = 9;     //cuantos cuadraditos pongo
const int tamanoCasilla = 50;
const int Anchbarra = Cntcudritos * tamanoCasilla; 
//Centro como dije antes
const int Pxi = (480 - Anchbarra) / 2; //Posicion x inicial (poreso P.X I.)
//Aca lo hacemos separado por 20 de abajo
const int Pyi = 320 - tamanoCasilla - 20; 

//colores en formato hexadecimal (RGB565)
#define COLOR_FONDO       0x6595 
#define COLOR_CASILLA     0x4208 
#define COLOR_BORDE       0xAD75 
#define COLOR_SOMBRA      0x2104 
#define COLOR_SELECCION   0xFFFF 

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
int casillaActual = 0; 
//=======================================
//  Bools para el io
//=======================================
bool juegoIncia;
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
  if (BtnACT())  { //BTNACT ES OBSOLETO
    if (Ttranscurrido > ExpClkTm - 25 && Ttranscurrido < ExpClkTm + 25)    {
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
  return Ganaste == 1? true : false;
}


void setup() {
  //Iniciamos la comunicacion con el otro Arduino a 9600 de velocidad
  Serial.begin(9600); 
  
  //Configuramos y encendemos la pantalla
  uint16_t ID = pantalla.readID();
  if (ID == 0xD3D3) ID = 0x9486; 
  
  pantalla.begin(ID);
  pantalla.setRotation(1); //ponemos la pantalla en horizontal (como debe ir en la caja)
  pantalla.fillScreen(COLOR_FONDO); //pintamos todo el fondo (de la pantalla)
  
  //Dibujamos 9 casillas cuando arranca el Arduino (que fiaca 9 veces el mismo comando)
  for (int i = 0; i < Cntcudritos; i++) {
    bool estaSeleccionada = (i == casillaActual);
    dibujarCasilla(i, estaSeleccionada);
  }
  
}




//=======================================
//  VOIDS O.O
//=======================================

//===============================
//  TOUCHSCREEN
//===============================
void leerToque() {
  //se fija si me tocan
  TSPoint toque = tactil.getPoint();
  //Es obligatorio restaurar estos pines después de leer el táctil
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  //di la presión esta fuerte entonces SI ME TOCARON
  if(toque.z > 10 && toque.z < 1000) {
    //Convertimos las coordenadas del sensor a píxeles reales de la pantalla
    int pixelX = map(toque.x, 150, 900, 0, 480); 
    int pixelY = map(toque.y, 150, 900, 0, 320); 
    //comprobamos si toco algun boton
    if (pixelY > Pyi && pixelY < Pyi + tamanoCasilla) { //SI ESTA DENTRO DEL EJE Y ENTONCES
      if (pixelX > Pxi && pixelX < Pxi + Anchbarra) {//ME FIJO SI ESTA DENTRO DE LA BARRA
        int casillaTocada = (pixelX - Pxi) / tamanoCasilla;//ME FIJO CUAL ITEM TOCO (DIVIDO LA BARRA)
        if (casillaTocada >= 0 && casillaTocada < 9) {//SI TIENE SENTIDO EL NUMERO QUE DA
          if (casillaTocada != casillaActual) {
            //Guardamos la casilla vieja para borrarle el marco blanco
            int casillaAnterior = casillaActual;
            casillaActual = casillaTocada; //Actualizamos a la nueva casilla
            //Redibujamos las dos casillas que cambiaron
            dibujarCasilla(casillaAnterior, false); //Apaga el marco de la vieja
            dibujarCasilla(casillaActual, true);    //Prende el marco de la nueva
            //le mando un whatsapp al otro arduino con la casilla actual
            Serial.write(casillaActual); 
            delay(150); //Pausa para que no lea dos toques muy rápidos por error
          }
          else {
            Serial.write(casillaActual); 
            delay(150);
          }}}}}}
//================================
// GRAFICOS DE PANTALLA
//================================
void dibujarCasilla(int numeroDeCasilla, bool estaSeleccionada) {
  //Calculamos en qué posición X va esta casilla en particular
  int x = Pxi + (numeroDeCasilla * tamanoCasilla);
  int y = Pyi;
  int grosorDelMarco = 4; 
  // Dibujamos el cuadrado base y los bordes para que tenga efecto 3D
  pantalla.fillRect(x, y, tamanoCasilla, tamanoCasilla, COLOR_CASILLA);
  pantalla.fillRect(x, y, tamanoCasilla, grosorDelMarco, COLOR_SOMBRA);       
  pantalla.fillRect(x, y, grosorDelMarco, tamanoCasilla, COLOR_SOMBRA);  //:3     
  pantalla.fillRect(x, y + tamanoCasilla - grosorDelMarco, tamanoCasilla, grosorDelMarco, COLOR_BORDE); 
  pantalla.fillRect(x + tamanoCasilla - grosorDelMarco, y, grosorDelMarco, tamanoCasilla, COLOR_BORDE); 
  //Si esta casilla está seleccionada, le dibujamos un marco extra de color blanco brillante
  if (estaSeleccionada) {
    for (int grosor = 0; grosor < (grosorDelMarco + 1); grosor++) { 
      pantalla.drawRect(x + grosor, y + grosor, tamanoCasilla - (grosor*2), tamanoCasilla - (grosor*2), COLOR_SELECCION);
    }}}