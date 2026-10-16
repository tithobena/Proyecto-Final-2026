#include "pantalla.h"
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
    if (pixelY > Pyi && pixelY < Pyi + tamanoCasilla && pixelX > Pxi && pixelX < Pxi + Anchbarra) { //SI ESTA DENTRO DEL EJE X e Y ENTONCES
        int casillaTocada = (pixelX - Pxi) / tamanoCasilla;//ME FIJO CUAL ITEM TOCO (DIVIDO LA BARRA)
        if (casillaTocada >= 0 && casillaTocada < 9) {//SI TIENE SENTIDO EL NUMERO QUE DA
          if (casillaTocada != casillaActual) {
            int casillaAnterior = casillaActual;//Guardamos la casilla vieja para borrarle el marco blanco
            casillaActual = casillaTocada; //Actualizamos a la nueva casilla
            //Redibujamos las dos casillas que cambiaron
            dibujarCasilla(casillaAnterior, false); //Apaga el marco de la vieja
            dibujarCasilla(casillaActual, true);    //Prende el marco de la nueva
            //le mando un whatsapp al otro arduino con la casilla actual
            Serial.println(casillaActual); 
            casila = casillaActual;
            delay(150); //Pausa para que no lea dos toques muy rápidos por error
          }
          else {
            Serial.println(casillaActual); 
            delay(150);
          }}}}}



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

  pantalla.setCursor(x + tamanoCasilla / 2, y + tamanoCasilla / 2);
  String nombre = objectos[numeroDeCasilla];
  pantalla.print(nombre);
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
    int xZonaObjetivo = xBarra + (ExpClkTm - 20);
  int anchoZonaObjetivo = 40; 
  pantalla.fillRect(xZonaObjetivo, yBarra, anchoZonaObjetivo, altoBarra, LIMA_LIMOSO);
  pantalla.fillRect(xZonaObjetivo + 10, yBarra, 20, altoBarra, VERDE_VERDOSO); // Centro ideal
}

void graficarVida(int vidaActual, int vidaMaxima, int yPos, uint16_t colorBarra) {
  pantalla.fillRect((480 - 200) / 2, yPos, 200, 15, COLOR_SOMBRA);
  pantalla.drawRect((480 - 200) / 2, yPos, 200, 15, COLOR_BORDE);
  if (vidaActual > 0) {
    pantalla.fillRect((480 - 200) / 2 + 2, yPos + 2, map(constrain(vidaActual, 0, vidaMaxima), 0, vidaMaxima, 0, 196), 11, colorBarra);
  }
}