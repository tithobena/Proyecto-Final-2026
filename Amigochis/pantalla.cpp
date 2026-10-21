#include "pantalla.h"
const String objectos[4] = {"espada", "arco", "bife", "lana"};
String baiaba = objectos[0];
//================================
// MENUS
//================================
// Centra un texto en la pantalla (la fuente base mide 6 px de ancho por tamaño)
void textoCentrado(const char* texto, int y, int tam, uint16_t color) {
  pantalla.setTextSize(tam);
  pantalla.setTextColor(color);
  int ancho = strlen(texto) * 6 * tam;
  pantalla.setCursor((480 - ancho) / 2, y);
  pantalla.print(texto);
  pantalla.setTextSize(1); // volvemos al tamaño normal para las casillas
  pantalla.setTextColor(COLOR_SELECCION);
}

bool pantallaTocada() {
  TSPoint t = tactil.getPoint();
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  if (t.z != 0) {return (true);}
  else{return (false);}
  
}

void dibujarJuego() {
  pantalla.fillScreen(COLOR_FONDO);
  for (int i = 0; i < Cntcudritos; i++) {
    dibujarCasilla(i, i == casillaActual, 5);
  }
}

void dibujarMenuInicio() {
  pantalla.fillScreen(COLOR_FONDO);
  textoCentrado("Warden", 90, 4, COLOR_SELECCION);
  textoCentrado("El mejor juego bro", 200, 2, LIMA_LIMOSO);
  BerlinSans.write(90);
}

void dibujarVictoria() {
  pantalla.fillScreen(VERDE_VERDOSO);
  textoCentrado("GANASTE! OSHI OSHI", 100, 4, COLOR_SELECCION);
  textoCentrado("Toca para volver al menu", 210, 2, COLOR_SELECCION);
  BerlinSans.write(0);
}

void dibujarDerrota() {
  pantalla.fillScreen(0x8000);
  textoCentrado("PERDISTE... (insulto obviado)", 100, 4, COLOR_SELECCION);
  textoCentrado("Toca para volver al menu", 210, 2, COLOR_SELECCION);
}
//===============================
//  TOUCHSCREEN
//===============================
//serial ver.
/*void leerToque() {
  if (Serial.available() > 0) {
    char entrada = Serial.read();
    
    // Si se ingresa un número del '1' al '5'
    if (entrada >= '1' && entrada <= '5') {
      int nuevaCasilla = entrada - '1'; // Convierte char '1'..'5' a índice 0..4
      
      casillaActual = nuevaCasilla;
      casila = casillaActual + 1; // Ajusta el índice para que coincida con juegito()
      
      Serial.print("Casilla seleccionada: ");
      Serial.println(casila);
    }}}*/
//pantalla ver.
void leerToque(int cantidadDeLanas) {
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
    if (pixelY > Pyi && pixelY < Pyi + tamanoCasilla && pixelX > Pxi && pixelX < Pxi + Anchbarra) { //SI ESTA DENTRO DEL EJE X e Y ENTONCES
        int casillaTocada = (pixelX - Pxi) / tamanoCasilla;//ME FIJO CUAL ITEM TOCO (DIVIDO LA BARRA)
        if (casillaTocada >= 0 && casillaTocada < 9) {//SI TIENE SENTIDO EL NUMERO QUE DA
          if (casillaTocada != casillaActual) {
            int casillaAnterior = casillaActual;//Guardamos la casilla vieja para borrarle el marco blanco
            casillaActual = casillaTocada; //Actualizamos a la nueva casilla
            //Redibujamos las dos casillas que cambiaron
            dibujarCasilla(casillaAnterior, false, cantidadDeLanas); //Apaga el marco de la vieja
            dibujarCasilla(casillaActual, true, cantidadDeLanas);    //Prende el marco de la nueva
            //le mando un whatsapp al otro arduino con la casilla actual
            Serial.println(casillaActual); 
            casila = casillaActual;
            baiaba = objectos[casila];
            delay(150); //Pausa para que no lea dos toques muy rápidos por error
          }
          else {
            Serial.println(casillaActual); 
            delay(150);
          }}}}}



//================================
// GRAFICOS DE PANTALLA
//================================
void dibujarCasilla(int numeroDeCasilla, bool estaSeleccionada, int cantidadDeLanas) {
  //Calculamos en qué posición X va esta casilla en particular
  int x = Pxi + (numeroDeCasilla * tamanoCasilla);
  int y = Pyi;
  int grosorDelMarco = 4; 
  // Dibujamos el cuadrado base y los bordes para que tenga efecto 3D
  pantalla.fillRect(x, y, tamanoCasilla, tamanoCasilla, COLOR_CASILLA);
  pantalla.fillRect(x, y, tamanoCasilla, grosorDelMarco, COLOR_SOMBRA);       
  pantalla.fillRect(x, y, grosorDelMarco, tamanoCasilla, COLOR_SOMBRA);  //:3  athos no eres agus como para poner el ":3"   
  pantalla.fillRect(x, y + tamanoCasilla - grosorDelMarco, tamanoCasilla, grosorDelMarco, COLOR_BORDE); 
  pantalla.fillRect(x + tamanoCasilla - grosorDelMarco, y, grosorDelMarco, tamanoCasilla, COLOR_BORDE); 
 String texto = objectos[numeroDeCasilla]; 
  int anchoTexto = texto.length() * 6; // 6 píxeles por carácter en tamaño 1
  int altoTexto = 8;                  // 8 píxeles de alto en tamaño 1
  int cursorX = x + (tamanoCasilla - anchoTexto) / 2;
  int cursorY = y + (tamanoCasilla - altoTexto) / 2;

  pantalla.setTextSize(1);
  pantalla.setTextColor(COLOR_SELECCION);
  pantalla.setCursor(cursorX, cursorY);
  pantalla.print(texto);

  if (numeroDeCasilla == 2)
  {
    int ancho = strlen(cantidadDeLanas) * 6 * 1.1;
    pantalla.setTextSize(1.1);
    pantalla.setCursor(x + tamanoCasilla - ancho - 5, y + tamanoCasilla - 15);
    pantalla.print(cantidadDeLanas);
    pantalla.setTextSize(1.0);
    if (cantidadDeLanas == 0)
    {
      pantalla.fillRect(x + 3, y + (tamanoCasilla / 2) - 5, tamanoCasilla - 3, 10, 0x8000);
    }
      
  }
  //Si esta casilla está seleccionada, le dibujamos un marco extra de color blanco brillante
  if (estaSeleccionada) {
    for (int grosor = 0; grosor < (grosorDelMarco + 1); grosor++) { 
      pantalla.drawRect(x + grosor, y + grosor, tamanoCasilla - (grosor*2), tamanoCasilla - (grosor*2), COLOR_SELECCION);
    }}}
void graficarQuickEvent(unsigned long Ttranscurrido, int ExpClkTm, int altura) {
  const int anchoBarra = 312;
  const int altoBarra = 80;
  int xBarra = (480 - anchoBarra) / 2; // xBarra = 84
  int yBarra = (320 - altoBarra) / 2 - altura;
  pantalla.fillRect(xBarra, yBarra, anchoBarra, altoBarra, NEGRO_GRIS);
  int xProgreso = xBarra + Ttranscurrido;
  if (xProgreso > xBarra && xProgreso < (xBarra + anchoBarra)) {
    pantalla.fillRect(xProgreso - 2, yBarra, 4, altoBarra, COLOR_SELECCION);
  }
  int anchoZonaObjetivo = 30; 
  int xZonaObjetivo = xBarra + (ExpClkTm - anchoZonaObjetivo / 2);
  pantalla.fillRect(xZonaObjetivo, yBarra, anchoZonaObjetivo, altoBarra, LIMA_LIMOSO);
  pantalla.fillRect(xZonaObjetivo + 11, yBarra, 8, altoBarra, VERDE_VERDOSO); // Centro ideal
  pantalla.fillRect(ExpClkTm - 2, yBarra- 3, 2, altoBarra + 2, 0xFDE0);
}
void dibujarFondoQuickEvent(int ExpClkTm, int altura) {
  const int anchoBarra = 312;
  const int altoBarra = 80;
  int xBarra = (480 - anchoBarra) / 2; 
  int yBarra = (320 - altoBarra) / 2 - altura;
  
  pantalla.fillRect(xBarra, yBarra, anchoBarra, altoBarra, NEGRO_GRIS);
  
  int anchoZonaObjetivo = 30; 
  int xZonaObjetivo = xBarra + (ExpClkTm - anchoZonaObjetivo / 2);
  pantalla.fillRect(xZonaObjetivo, yBarra, anchoZonaObjetivo, altoBarra, LIMA_LIMOSO);
  pantalla.fillRect(xZonaObjetivo + 11, yBarra, 8, altoBarra, VERDE_VERDOSO); 
  pantalla.fillRect(xBarra + ExpClkTm - 2, yBarra - 3, 2, altoBarra + 2, 0xFDE0);
}
void actualizarCursorQuickEvent(unsigned long tAnt, unsigned long tNuevo, int ExpClkTm, int altura) {
  const int anchoBarra = 312;
  const int altoBarra = 80;
  int xBarra = (480 - anchoBarra) / 2;
  int yBarra = (320 - altoBarra) / 2 - altura;
  
  int anchoZonaObjetivo = 30; 
  int xZonaObjetivo = xBarra + (ExpClkTm - anchoZonaObjetivo / 2);

  //Limpiar la pos anterior del cursor restaurando su fondo correspondiente
  if (tAnt > 0 && tAnt <= anchoBarra) {
    int xAnt = xBarra + tAnt;
    if (xAnt >= xBarra && xAnt < xBarra + anchoBarra) {
      if (xAnt >= xZonaObjetivo && xAnt < xZonaObjetivo + anchoZonaObjetivo) {
        if (xAnt >= xZonaObjetivo + 11 && xAnt < xZonaObjetivo + 11 + 8) {
          pantalla.fillRect(xAnt - 2, yBarra, 4, altoBarra, VERDE_VERDOSO);
        } else {
          pantalla.fillRect(xAnt - 2, yBarra, 4, altoBarra, LIMA_LIMOSO);
        }
      } else {
        pantalla.fillRect(xAnt - 2, yBarra, 4, altoBarra, NEGRO_GRIS);
      }
    }
  }

  //Dibujar el nuevo cursor con el color dinamico según la zona
  if (tNuevo > 0 && tNuevo <= anchoBarra) {
    int xNuevo = xBarra + tNuevo;
    if (xNuevo >= xBarra && xNuevo < xBarra + anchoBarra) {
      uint16_t colorCursor = COLOR_SELECCION;
      
      if (xNuevo >= xZonaObjetivo && xNuevo < xZonaObjetivo + anchoZonaObjetivo) {
        if (xNuevo >= xZonaObjetivo + 11 && xNuevo < xZonaObjetivo + 11 + 8) {
          colorCursor = VERDE_VERDOSO; 
        } else {
          colorCursor = LIMA_LIMOSO;   
        }
      }
      
      pantalla.fillRect(xNuevo - 2, yBarra, 4, altoBarra, colorCursor);
    }
  }
}

void graficarVida(int vidaActual, int vidaMaxima, int yPos, uint16_t colorBarra) {
  const int x = (480 - 200) / 2;
  const int anchoInterior = 198;
  int ancho = map(constrain(vidaActual, 0, vidaMaxima), 0, vidaMaxima, 0, anchoInterior);

  pantalla.drawRect(x, yPos, 200, 15, COLOR_BORDE);
  // parte llena (vida)
  if (ancho > 0) {
    pantalla.fillRect(x + 1, yPos + 1, ancho, 13, colorBarra);
  }
  // parte vacía (lo que falta)
  if (ancho < anchoInterior) {
    pantalla.fillRect(x + 1 + ancho, yPos + 1, anchoInterior - ancho, 13, COLOR_SOMBRA);
  }
}
void turnoMan(bool tuTurno)
{
  pantalla.fillRect(0, 0, 480, 40, COLOR_FONDO);
  pantalla.setCursor(0, 0);
  pantalla.setTextSize(2.3);
  if (tuTurno)
  {
  pantalla.print("Tu turno");
  }else
  {
    pantalla.print("Turno del warden");
  }
    pantalla.setTextSize(1);
}