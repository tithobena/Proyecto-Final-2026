/*
 ██████╗ ██████╗ ██╗   ██╗██████╗  ██████╗      ██████╗ ███████╗    ██████╗ ██╗ ██████╗ ██╗██╗  ██╗
██╔════╝ ██╔══██╗██║   ██║██╔══██╗██╔═══██╗    ██╔═████╗╚════██║    ██╔══██╗██║██╔═══██╗██║╚██╗██╔╝
██║  ███╗██████╔╝██║   ██║██████╔╝██║   ██║    ██║██╔██║    ██╔╝    ██████╔╝██║██║   ██║██║ ╚███╔╝ 
██║   ██║██╔══██╗██║   ██║██╔═══╝ ██║   ██║    ████╔╝██║   ██╔╝     ██╔═══╝ ██║██║   ██║██║ ██╔██╗ 
╚██████╔╝██║  ██║╚██████╔╝██║     ╚██████╔╝    ╚██████╔╝   ██║      ██║     ██║╚██████╔╝██║██╔╝ ██╗
 ╚═════╝ ╚═╝  ╚═╝ ╚═════╝ ╚═╝      ╚═════╝      ╚═════╝    ╚═╝      ╚═╝     ╚═╝ ╚═════╝ ╚═╝╚═╝  ╚═╝                                                    
                                                                 Codigo Pantalla V1.1 Para A.UNO*/
                  
#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>
#include <TouchScreen.h>

//Pongo el nombre "pantalla" a la pantalla y "tactil" al sensor de toques
MCUFRIEND_kbv pantalla; 
#define YP A2  
#define XM A3  
#define YM 8   
#define XP 9   
TouchScreen tactil = TouchScreen(XP, YP, XM, YM, 300);

//colores en formato hexadecimal (RGB565)
#define COLOR_FONDO       0x6595 
#define COLOR_CASILLA     0x4208 
#define COLOR_BORDE       0xAD75 
#define COLOR_SOMBRA      0x2104 
#define COLOR_SELECCION   0xFFFF 



//Variables para organizar las casillas (la barra de abajo)
const int Cntcudritos = 9;     //cuantos cuadraditos pongo
const int tamanoCasilla = 50;
const int Anchbarra = Cntcudritos * tamanoCasilla; 

//Centrar la barra 

/*NOTA IMPORTANTE:
LA PANTALLA MUESTRA LO QUE LE PEDIS COMENZANDO DE LA ESQUINA SUPERIOR IZQUIERDA.
SI LE QUERES CENTRAR NO PONES SOLO LA CANTIDAD DE PIXELES / 2, TENES QUE RESTAR EL ANCHO/ALTO
*/

//Centro como dije antes
const int Pxi = (480 - Anchbarra) / 2; //Posicion x inicial (poreso P.X I.)
//Aca lo hacemos separado por 20 de abajo
const int Pyi = 320 - tamanoCasilla - 20; //lo mismo xd

//Esta variable guarda que casilla esta seleccionada actualmente
int casillaActual = 0; 

void setup() {
  //Iniciamos la comunicacion con el otro Arduino a 9600 de velocidad (como si fuera a la pc, pero en cambio al otro arduino)
  Serial.begin(9600); 
  
  //Configuramos y encendemos la pantalla (primero se fija si es la pantalla correcta y despues arranca para que no )
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

void loop() {
  String info = String(Serial.read());
  if (info.length() > 0 && info[0] == 'W') {
    pantalla.setCursor(200, 50);
    info.remove(0, 1);
    pantalla.print(info);
  }
  if (info.length() > 0 && info[0] == 'V') {
    pantalla.setCursor(200, 50);
    info.remove(0, 1);
    pantalla.print(info);
  }

  /*codigo del boton*/

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
    
    //comprobamos si toco algun boton (esto seria "si donde toco esta dentro de el eje x de un bloque Y dentro del eje Y de un bloque entonces..")
    //porfa no se mueran con esto, no es TAN dificil, solo es largo
    //lo hago por pasitos chiquitos:

    //SI ESTA DENTRO DEL EJE Y ENTONCES
    if (pixelY > Pyi && pixelY < Pyi + tamanoCasilla) {
      
      //ME FIJO SI ESTA DENTRO DE LA BARRA
      if (pixelX > Pxi && pixelX < Pxi + Anchbarra) {
        
        //ME FIJO CUAL ITEM TOCO (DIVIDO LA BARRA)
        int casillaTocada = (pixelX - Pxi) / tamanoCasilla;
        
        //SI TIENE SENTIDO EL NUMERO QUE DA
        if (casillaTocada >= 0 && casillaTocada < 9) {
          //AL FINNN. NO ERA DIFICIL NO?
          //ahora hago esto para no hacer actualizar al pepe la pantalla
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
          }
        }
      }
    }
  }
}

//================================
// GRAFICOS
//================================
// Esta es una herramienta (funcion) que creamos para dibujar una sola casilla, es como un link que cada vez que lo llamas hace esto
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
    }
  }
}

