/*=====================================================================
  pantalla.cpp - Dibujo en pantalla, tactil y HUD de Amigochis
=======================================================================
  INDICE
    [1] DATOS GLOBALES
          objectos, baiaba
    [2] UTILIDADES DE DIBUJO
          textoCentrado, truquilloSonic, pantallaScanlines
    [3] TACTIL
          pantallaTocada, leerToque (+ version por serie desactivada)
    [4] HOTBAR / CASILLAS
          dibujarCasilla
    [5] HUD
          turnoMan, graficarVida, graficarBarraBossWarden
    [6] QUICKEVENT (minijuego de reaccion)
          graficarQuickEvent, dibujarFondoQuickEvent,
          actualizarCursorQuickEvent
    [7] PANTALLAS COMPLETAS
          dibujarMenuInicio, dibujarJuego, dibujarVictoria, dibujarDerrota

  Nota: textoCentrado y pantallaScanlines no estan declaradas en
  pantalla.h, por eso se definen en [2], antes de usarse.
=====================================================================*/
/*=====================================================================
  pantalla.cpp - Dibujo en pantalla, tactil y HUD de Amigochis
=======================================================================
  INDICE
    [1] DATOS GLOBALES
          objectos, baiaba
    [2] UTILIDADES DE DIBUJO
          textoCentrado, truquilloSonic, pantallaScanlines
    [3] TACTIL
          pantallaTocada, leerToque (+ version por serie desactivada)
    [4] HOTBAR / CASILLAS
          dibujarCasilla
    [5] HUD
          turnoMan, graficarVida, graficarBarraBossWarden
    [6] QUICKEVENT (minijuego de reaccion)
          graficarQuickEvent, dibujarFondoQuickEvent,
          actualizarCursorQuickEvent
    [7] PANTALLAS COMPLETAS
          dibujarMenuInicio, dibujarJuego, dibujarVictoria, dibujarDerrota

  Nota: textoCentrado y pantallaScanlines no estan declaradas en
  pantalla.h, por eso se definen en [2], antes de usarse.
=====================================================================*/
#include "pantalla.h"

//=====================================================================
// [1] DATOS GLOBALES
//=====================================================================
//=====================================================================
// [1] DATOS GLOBALES
//=====================================================================
const String objectos[4] = {"espada", "arco", "bife", "lana"};
String baiaba = objectos[0];

//=====================================================================
// [2] UTILIDADES DE DIBUJO
//=====================================================================

// Centra un texto en la pantalla (la fuente base mide 6 px de ancho por tamano)

//=====================================================================
// [2] UTILIDADES DE DIBUJO
//=====================================================================

// Centra un texto en la pantalla (la fuente base mide 6 px de ancho por tamano)
void textoCentrado(const char* texto, int y, int tam, uint16_t color) {
  pantalla.setTextSize(tam);
  pantalla.setTextColor(color);
  int ancho = strlen(texto) * 6 * tam;
  pantalla.setCursor((480 - ancho) / 2, y);
  pantalla.print(texto);
  pantalla.setTextSize(1); // Volvemos al tamano normal para las casillas
  pantalla.setTextSize(1); // Volvemos al tamano normal para las casillas
  pantalla.setTextColor(COLOR_SELECCION);
}

// Cuadrado "semitransparente" (dibuja un pixel si y otro no, en damero)

// Cuadrado "semitransparente" (dibuja un pixel si y otro no, en damero)
void truquilloSonic(int x, int y, int w, int h, uint16_t color) {
  for (int i = 0; i < w; i++) {
    for (int j = 0; j < h; j++) {
      if ((i + j) % 2 == 0) {
        pantalla.drawPixel(x + i, y + j, color);
      }
    }
  }
}

// Lineas horizontales en las filas pares de toda la pantalla
void pantallaScanlines(uint16_t color) {
  for (int y = 0; y < 320; y += 2) {
    pantalla.drawFastHLine(0, y, 480, color);
  }
}

//=====================================================================
// [3] TACTIL
//=====================================================================

// Devuelve true si hay algun toque en la pantalla

// Lineas horizontales en las filas pares de toda la pantalla
void pantallaScanlines(uint16_t color) {
  for (int y = 0; y < 320; y += 2) {
    pantalla.drawFastHLine(0, y, 480, color);
  }
}

//=====================================================================
// [3] TACTIL
//=====================================================================

// Devuelve true si hay algun toque en la pantalla
bool pantallaTocada() {
  TSPoint t = tactil.getPoint();
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  if (t.z != 0) {
    return true;
  } else {
    return false;
  }
}

// --- Version por serie (DESACTIVADA) ---------------------------------
  if (t.z != 0) {
    return true;
  } else {
    return false;
  }
}

// --- Version por serie (DESACTIVADA) ---------------------------------
/*void leerToque() {
  if (Serial.available() > 0) {
    char entrada = Serial.read();

    // Si se ingresa un numero del '1' al '5'

    // Si se ingresa un numero del '1' al '5'
    if (entrada >= '1' && entrada <= '5') {
      int nuevaCasilla = entrada - '1'; // Convierte char '1'..'5' a indice 0..4

      int nuevaCasilla = entrada - '1'; // Convierte char '1'..'5' a indice 0..4

      casillaActual = nuevaCasilla;
      casila = casillaActual + 1; // Ajusta el indice para que coincida con juegito()

      casila = casillaActual + 1; // Ajusta el indice para que coincida con juegito()

      Serial.print("Casilla seleccionada: ");
      Serial.println(casila);
    }}}*/

// --- Version por pantalla (ACTIVA) -----------------------------------

// --- Version por pantalla (ACTIVA) -----------------------------------
void leerToque(int cantidadDeLanas) {
  // Se fija si me tocan
  // Se fija si me tocan
  TSPoint toque = tactil.getPoint();
  // Es obligatorio restaurar estos pines despues de leer el tactil
  // Es obligatorio restaurar estos pines despues de leer el tactil
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);

  // Si la presion es fuerte entonces SI ME TOCARON
  if (toque.z > 10 && toque.z < 1000) {
    // Convertimos las coordenadas del sensor a pixeles reales de la pantalla
    int pixelX = map(toque.x, 150, 900, 0, 480);
    int pixelY = map(toque.y, 150, 900, 0, 320);

    // Comprobamos si toco algun boton (dentro del eje X e Y de la barra)
    if (pixelY > Pyi && pixelY < Pyi + tamanoCasilla && pixelX > Pxi && pixelX < Pxi + Anchbarra) {
      // Me fijo cual item toco (divido la barra)
      int casillaTocada = (pixelX - Pxi) / tamanoCasilla;
      // Si tiene sentido el numero que da
      if (casillaTocada >= 0 && casillaTocada < 9) {
        if (casillaTocada != casillaActual) {
          // Guardamos la casilla vieja para borrarle el marco blanco
          int casillaAnterior = casillaActual;
          casillaActual = casillaTocada; // Actualizamos a la nueva casilla
          // Redibujamos las dos casillas que cambiaron
          dibujarCasilla(casillaAnterior, false, cantidadDeLanas); // Apaga el marco de la vieja
          dibujarCasilla(casillaActual, true, cantidadDeLanas);    // Prende el marco de la nueva
          // Le mando un whatsapp al otro arduino con la casilla actual
          Serial.println(casillaActual);
          casila = casillaActual;
          baiaba = objectos[casila];
          delay(150); // Pausa para que no lea dos toques muy rapidos por error
        } else {
          Serial.println(casillaActual);
          delay(150);
        }
      }
    }
  }
}

  // Si la presion es fuerte entonces SI ME TOCARON
  if (toque.z > 10 && toque.z < 1000) {
    // Convertimos las coordenadas del sensor a pixeles reales de la pantalla
    int pixelX = map(toque.x, 150, 900, 0, 480);
    int pixelY = map(toque.y, 150, 900, 0, 320);

    // Comprobamos si toco algun boton (dentro del eje X e Y de la barra)
    if (pixelY > Pyi && pixelY < Pyi + tamanoCasilla && pixelX > Pxi && pixelX < Pxi + Anchbarra) {
      // Me fijo cual item toco (divido la barra)
      int casillaTocada = (pixelX - Pxi) / tamanoCasilla;
      // Si tiene sentido el numero que da
      if (casillaTocada >= 0 && casillaTocada < 9) {
        if (casillaTocada != casillaActual) {
          // Guardamos la casilla vieja para borrarle el marco blanco
          int casillaAnterior = casillaActual;
          casillaActual = casillaTocada; // Actualizamos a la nueva casilla
          // Redibujamos las dos casillas que cambiaron
          dibujarCasilla(casillaAnterior, false, cantidadDeLanas); // Apaga el marco de la vieja
          dibujarCasilla(casillaActual, true, cantidadDeLanas);    // Prende el marco de la nueva
          // Le mando un whatsapp al otro arduino con la casilla actual
          Serial.println(casillaActual);
          casila = casillaActual;
          baiaba = objectos[casila];
          delay(150); // Pausa para que no lea dos toques muy rapidos por error
        } else {
          Serial.println(casillaActual);
          delay(150);
        }
      }
    }
  }
}

//=====================================================================
// [4] HOTBAR / CASILLAS
//=====================================================================
//=====================================================================
// [4] HOTBAR / CASILLAS
//=====================================================================
void dibujarCasilla(int numeroDeCasilla, bool estaSeleccionada, int cantidadDeLanas) {
  // Calculamos en que posicion X va esta casilla en particular
  // Calculamos en que posicion X va esta casilla en particular
  int x = Pxi + (numeroDeCasilla * tamanoCasilla);
  int y = Pyi;
  int grosorDelMarco = 4;

  int grosorDelMarco = 4;

  // Dibujamos el cuadrado base y los bordes para que tenga efecto 3D
  pantalla.fillRect(x, y, tamanoCasilla, tamanoCasilla, COLOR_CASILLA);
  pantalla.fillRect(x, y, tamanoCasilla, grosorDelMarco, SOMBRA);
  pantalla.fillRect(x, y, grosorDelMarco, tamanoCasilla, SOMBRA);  //:3  athos no eres agus como para poner el ":3"
  pantalla.fillRect(x, y + tamanoCasilla - grosorDelMarco, tamanoCasilla, grosorDelMarco, COLOR_BORDE);
  pantalla.fillRect(x + tamanoCasilla - grosorDelMarco, y, grosorDelMarco, tamanoCasilla, COLOR_BORDE);

  String texto = objectos[numeroDeCasilla];
  int anchoTexto = texto.length() * 6; // 6 pixeles por caracter en tamano 1
  int altoTexto = 8;                   // 8 pixeles de alto en tamano 1
  pantalla.fillRect(x, y, tamanoCasilla, grosorDelMarco, SOMBRA);
  pantalla.fillRect(x, y, grosorDelMarco, tamanoCasilla, SOMBRA);  //:3  athos no eres agus como para poner el ":3"
  pantalla.fillRect(x, y + tamanoCasilla - grosorDelMarco, tamanoCasilla, grosorDelMarco, COLOR_BORDE);
  pantalla.fillRect(x + tamanoCasilla - grosorDelMarco, y, grosorDelMarco, tamanoCasilla, COLOR_BORDE);

  String texto = objectos[numeroDeCasilla];
  int anchoTexto = texto.length() * 6; // 6 pixeles por caracter en tamano 1
  int altoTexto = 8;                   // 8 pixeles de alto en tamano 1
  int cursorX = x + (tamanoCasilla - anchoTexto) / 2;
  int cursorY = y + (tamanoCasilla - altoTexto) / 2;

  // Imagen del item
  // Imagen del item
  const uint16_t* imagenActual = nullptr;
  switch (numeroDeCasilla) {
    case 0: imagenActual = image_minecraft_diamond_sword_16x16_pixels; break;
    case 1: imagenActual = image_minecraft_bow_16x16_pixels; break;
    case 2: imagenActual = image_minecraft_cooked_beef_16x16_pixels; break;
    case 3: imagenActual = image_minecraft_white_wool_16x16_pixels; break;
    default: break;
  }

  // Si hay una imagen valida, la escalamos y dibujamos pixel por pixel
  // Si hay una imagen valida, la escalamos y dibujamos pixel por pixel
  if (imagenActual != nullptr) {
    int escala = 5; // 80 / 16 = 5
    // Margen interno opcional para que no pegue contra el borde del marco (ej: 4 pixeles de margen)
    int margen = 0;

    // Margen interno opcional para que no pegue contra el borde del marco (ej: 4 pixeles de margen)
    int margen = 0;

    for (int py = 0; py < 16; py++) {
      for (int px = 0; px < 16; px++) {
        // Leemos el color desde la memoria PROGMEM del Arduino Mega
        uint16_t colorPixel = pgm_read_word(&imagenActual[py * 16 + px]);


        // Si el color NO es negro (0x0000), lo dibujamos como un bloque de escala x escala
        if (colorPixel != 0x0000) {
          pantalla.fillRect(
            x + grosorDelMarco + (px * escala),
            y + grosorDelMarco + (py * escala),
            escala,
            escala,
            x + grosorDelMarco + (px * escala),
            y + grosorDelMarco + (py * escala),
            escala,
            escala,
            colorPixel
          );
        }
      }
    }
  }

  pantalla.setTextSize(1);
  pantalla.setTextColor(COLOR_SELECCION);
  pantalla.setCursor(cursorX, cursorY);
  pantalla.print(texto);

  // Contador de lanas (solo en la casilla 3)
  if (numeroDeCasilla == 3) {
  // Contador de lanas (solo en la casilla 3)
  if (numeroDeCasilla == 3) {
    int ancho = strlen(cantidadDeLanas) * 6 * 1.1;
    pantalla.setTextSize(1.1);
    pantalla.setCursor(x + tamanoCasilla - ancho - 5, y + tamanoCasilla - 15);
    pantalla.print(cantidadDeLanas);
    pantalla.setTextSize(1.0);
    if (cantidadDeLanas == 0) {
    if (cantidadDeLanas == 0) {
      pantalla.fillRect(x + 3, y + (tamanoCasilla / 2) - 5, tamanoCasilla - 3, 10, 0x8000);
    }
  }

  // Si esta casilla esta seleccionada, le dibujamos un marco extra de color blanco brillante

  // Si esta casilla esta seleccionada, le dibujamos un marco extra de color blanco brillante
  if (estaSeleccionada) {
    for (int grosor = 0; grosor < (grosorDelMarco + 1); grosor++) {
      pantalla.drawRect(x + grosor, y + grosor, tamanoCasilla - (grosor * 2), tamanoCasilla - (grosor * 2), COLOR_SELECCION);
    }
  }
}

//=====================================================================
// [5] HUD
//=====================================================================

// Cartel "Tu turno" / "Turno del warden" (solo redibuja si cambia el turno)
void turnoMan(bool tuTurno) {
  static int estadoAnteriorTurno = -1;
  int turnoActualInt = tuTurno ? 1 : 0;
  if (turnoActualInt != estadoAnteriorTurno) {
    estadoAnteriorTurno = turnoActualInt;
    pantalla.fillRect(20, 35, 440, 45, COLOR_FONDO);
    pantalla.setCursor(20, 35);
    pantalla.setTextSize(2);
    pantalla.setTextColor(COLOR_SELECCION);
    if (tuTurno) {
      pantalla.print("Tu turno");
    } else {
      pantalla.print("Turno del warden");
    }
    pantalla.setTextSize(1);
  }
}

// Vida del jugador: 10 corazones estilo Minecraft
void graficarVida(int vidaActual, int vidaMaxima, int yPos, uint16_t colorBarra) {
  const int totalCorazones = 10; // 10 corazones estilo Minecraft clasico
  int escala = 2;                // Escala de tamano (9x9 * 2 = 18x18 pixeles por corazon)
  int anchoCorazon = 9 * escala;
  int espacioEntreCorazones = 3;

  int anchoTotalBarra = (totalCorazones * anchoCorazon) + ((totalCorazones - 1) * espacioEntreCorazones);
  int xInicio = (480 - anchoTotalBarra) / 2;

  float vidaPorCorazon = (float)vidaMaxima / totalCorazones;

  for (int i = 0; i < totalCorazones; i++) {
    int xCorazon = xInicio + (i * (anchoCorazon + espacioEntreCorazones));

    float umbralCompleto = (i + 1) * vidaPorCorazon;
    float umbralMitad = umbralCompleto - (vidaPorCorazon / 2.0);

    const uint16_t* imgAUsar = nullptr;

    if (vidaActual >= umbralCompleto) {
      imgAUsar = image_full_pixels;      // Corazon lleno
    } else if (vidaActual >= umbralMitad) {
      imgAUsar = image_half_pixels;      // Corazon a la mitad
    } else {
      imgAUsar = image_empty_pixels;     // Corazon vacio (nuevo)
    }

    // Dibujo ultrarrapido usando la funcion nativa con escalado por software directo
    // Esto evita el bucle pesado de fillRect individual y elimina el "lag" en pantalla.
    for (int py = 0; py < 9; py++) {
      for (int px = 0; px < 9; px++) {
        uint16_t colorPixel = pgm_read_word(&imgAUsar[py * 9 + px]);

        // Si el color no es negro absoluto, lo pintamos (manejando transparencia simulada)
        if (colorPixel != 0x0000) {
          pantalla.fillRect(xCorazon + (px * escala), yPos + (py * escala), escala, escala, colorPixel);
        } else {
          // Rellenamos el fondo del espacio vacio con el color de fondo para evitar rastros
          pantalla.fillRect(xCorazon + (px * escala), yPos + (py * escala), escala, escala, COLOR_FONDO);
        }
      }
    }
  }
}

// Barra de vida del Warden (arriba de la pantalla)
void graficarBarraBossWarden(int vidaActual, int vidaMaxima) {
  // Variable estatica para recordar la ultima vida dibujada y evitar redibujos innecesarios
  static int vidaAnterior = -1;

  // (bro no es el turno, no es gracioso que parpadees)
  if (vidaActual == vidaAnterior) {
    return;
  }
  vidaAnterior = vidaActual; // Actualizamos registro

  const int anchoBarra = 360;
  const int altoBarra = 16;
  const int xBarra = (480 - anchoBarra) / 2;
  const int yBarra = 12;
  const uint16_t COLOR_BORDE_BOSS  = 0x4810;
  const uint16_t COLOR_FONDO_BOSS  = 0x1883;
  const uint16_t COLOR_VIDA_WARDEN = 0x881F;

  pantalla.drawRect(xBarra - 2, yBarra - 2, anchoBarra + 4, altoBarra + 4, COLOR_BORDE_BOSS);
  pantalla.drawRect(xBarra - 1, yBarra - 1, anchoBarra + 2, altoBarra + 2, COLOR_BORDE_BOSS);
  pantalla.fillRect(xBarra, yBarra, anchoBarra, altoBarra, COLOR_FONDO_BOSS);

  int vidaClampeada = constrain(vidaActual, 0, vidaMaxima);
  int anchoActual = map(vidaClampeada, 0, vidaMaxima, 0, anchoBarra);
  if (anchoActual > 0) {
    pantalla.fillRect(xBarra, yBarra, anchoActual, altoBarra, COLOR_VIDA_WARDEN);
  }
  if (anchoActual < anchoBarra) {
    pantalla.fillRect(xBarra + anchoActual, yBarra, anchoBarra - anchoActual, altoBarra, COLOR_FONDO_BOSS);
  }

  pantalla.setTextSize(1);
  pantalla.setTextColor(COLOR_SELECCION);
  int anchoTexto = 6 * 6;
  pantalla.setCursor((480 - anchoTexto) / 2, yBarra - 10);
  pantalla.print("Warden");
}

//=====================================================================
// [6] QUICKEVENT (minijuego de reaccion)
//=====================================================================

// Version completa: barra + zona objetivo + cursor (hoy no se usa, la logica
// actual usa dibujarFondoQuickEvent + actualizarCursorQuickEvent)
    for (int grosor = 0; grosor < (grosorDelMarco + 1); grosor++) {
      pantalla.drawRect(x + grosor, y + grosor, tamanoCasilla - (grosor * 2), tamanoCasilla - (grosor * 2), COLOR_SELECCION);
    }
  }
}

//=====================================================================
// [5] HUD
//=====================================================================

// Cartel "Tu turno" / "Turno del warden" (solo redibuja si cambia el turno)
void turnoMan(bool tuTurno) {
  static int estadoAnteriorTurno = -1;
  int turnoActualInt = tuTurno ? 1 : 0;
  if (turnoActualInt != estadoAnteriorTurno) {
    estadoAnteriorTurno = turnoActualInt;
    pantalla.fillRect(20, 35, 440, 45, COLOR_FONDO);
    pantalla.setCursor(20, 35);
    pantalla.setTextSize(2);
    pantalla.setTextColor(COLOR_SELECCION);
    if (tuTurno) {
      pantalla.print("Tu turno");
    } else {
      pantalla.print("Turno del warden");
    }
    pantalla.setTextSize(1);
  }
}

// Vida del jugador: 10 corazones estilo Minecraft
void graficarVida(int vidaActual, int vidaMaxima, int yPos, uint16_t colorBarra) {
  const int totalCorazones = 10; // 10 corazones estilo Minecraft clasico
  int escala = 2;                // Escala de tamano (9x9 * 2 = 18x18 pixeles por corazon)
  int anchoCorazon = 9 * escala;
  int espacioEntreCorazones = 3;

  int anchoTotalBarra = (totalCorazones * anchoCorazon) + ((totalCorazones - 1) * espacioEntreCorazones);
  int xInicio = (480 - anchoTotalBarra) / 2;

  float vidaPorCorazon = (float)vidaMaxima / totalCorazones;

  for (int i = 0; i < totalCorazones; i++) {
    int xCorazon = xInicio + (i * (anchoCorazon + espacioEntreCorazones));

    float umbralCompleto = (i + 1) * vidaPorCorazon;
    float umbralMitad = umbralCompleto - (vidaPorCorazon / 2.0);

    const uint16_t* imgAUsar = nullptr;

    if (vidaActual >= umbralCompleto) {
      imgAUsar = image_full_pixels;      // Corazon lleno
    } else if (vidaActual >= umbralMitad) {
      imgAUsar = image_half_pixels;      // Corazon a la mitad
    } else {
      imgAUsar = image_empty_pixels;     // Corazon vacio (nuevo)
    }

    // Dibujo ultrarrapido usando la funcion nativa con escalado por software directo
    // Esto evita el bucle pesado de fillRect individual y elimina el "lag" en pantalla.
    for (int py = 0; py < 9; py++) {
      for (int px = 0; px < 9; px++) {
        uint16_t colorPixel = pgm_read_word(&imgAUsar[py * 9 + px]);

        // Si el color no es negro absoluto, lo pintamos (manejando transparencia simulada)
        if (colorPixel != 0x0000) {
          pantalla.fillRect(xCorazon + (px * escala), yPos + (py * escala), escala, escala, colorPixel);
        } else {
          // Rellenamos el fondo del espacio vacio con el color de fondo para evitar rastros
          pantalla.fillRect(xCorazon + (px * escala), yPos + (py * escala), escala, escala, COLOR_FONDO);
        }
      }
    }
  }
}

// Barra de vida del Warden (arriba de la pantalla)
void graficarBarraBossWarden(int vidaActual, int vidaMaxima) {
  // Variable estatica para recordar la ultima vida dibujada y evitar redibujos innecesarios
  static int vidaAnterior = -1;

  // (bro no es el turno, no es gracioso que parpadees)
  if (vidaActual == vidaAnterior) {
    return;
  }
  vidaAnterior = vidaActual; // Actualizamos registro

  const int anchoBarra = 360;
  const int altoBarra = 16;
  const int xBarra = (480 - anchoBarra) / 2;
  const int yBarra = 12;
  const uint16_t COLOR_BORDE_BOSS  = 0x4810;
  const uint16_t COLOR_FONDO_BOSS  = 0x1883;
  const uint16_t COLOR_VIDA_WARDEN = 0x881F;

  pantalla.drawRect(xBarra - 2, yBarra - 2, anchoBarra + 4, altoBarra + 4, COLOR_BORDE_BOSS);
  pantalla.drawRect(xBarra - 1, yBarra - 1, anchoBarra + 2, altoBarra + 2, COLOR_BORDE_BOSS);
  pantalla.fillRect(xBarra, yBarra, anchoBarra, altoBarra, COLOR_FONDO_BOSS);

  int vidaClampeada = constrain(vidaActual, 0, vidaMaxima);
  int anchoActual = map(vidaClampeada, 0, vidaMaxima, 0, anchoBarra);
  if (anchoActual > 0) {
    pantalla.fillRect(xBarra, yBarra, anchoActual, altoBarra, COLOR_VIDA_WARDEN);
  }
  if (anchoActual < anchoBarra) {
    pantalla.fillRect(xBarra + anchoActual, yBarra, anchoBarra - anchoActual, altoBarra, COLOR_FONDO_BOSS);
  }

  pantalla.setTextSize(1);
  pantalla.setTextColor(COLOR_SELECCION);
  int anchoTexto = 6 * 6;
  pantalla.setCursor((480 - anchoTexto) / 2, yBarra - 10);
  pantalla.print("Warden");
}

//=====================================================================
// [6] QUICKEVENT (minijuego de reaccion)
//=====================================================================

// Version completa: barra + zona objetivo + cursor (hoy no se usa, la logica
// actual usa dibujarFondoQuickEvent + actualizarCursorQuickEvent)
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

  int anchoZonaObjetivo = 30;
  int xZonaObjetivo = xBarra + (ExpClkTm - anchoZonaObjetivo / 2);
  pantalla.fillRect(xZonaObjetivo, yBarra, anchoZonaObjetivo, altoBarra, LIMA_LIMOSO);
  pantalla.fillRect(xZonaObjetivo + 11, yBarra, 8, altoBarra, VERDE_VERDOSO); // Centro ideal
  pantalla.fillRect(ExpClkTm - 2, yBarra - 3, 2, altoBarra + 2, 0xFDE0);
  pantalla.fillRect(ExpClkTm - 2, yBarra - 3, 2, altoBarra + 2, 0xFDE0);
}

// Dibuja la barra y la zona objetivo (una sola vez al empezar)

// Dibuja la barra y la zona objetivo (una sola vez al empezar)
void dibujarFondoQuickEvent(int ExpClkTm, int altura) {
  const int anchoBarra = 312;
  const int altoBarra = 80;
  int xBarra = (480 - anchoBarra) / 2;
  int xBarra = (480 - anchoBarra) / 2;
  int yBarra = (320 - altoBarra) / 2 - altura;


  pantalla.fillRect(xBarra, yBarra, anchoBarra, altoBarra, NEGRO_GRIS);

  int anchoZonaObjetivo = 30;

  int anchoZonaObjetivo = 30;
  int xZonaObjetivo = xBarra + (ExpClkTm - anchoZonaObjetivo / 2);
  pantalla.fillRect(xZonaObjetivo, yBarra, anchoZonaObjetivo, altoBarra, LIMA_LIMOSO);
  pantalla.fillRect(xZonaObjetivo + 11, yBarra, 8, altoBarra, VERDE_VERDOSO);
  pantalla.fillRect(xZonaObjetivo + 11, yBarra, 8, altoBarra, VERDE_VERDOSO);
  pantalla.fillRect(xBarra + ExpClkTm - 2, yBarra - 3, 2, altoBarra + 2, 0xFDE0);
}

// Mueve el cursor: borra el anterior restaurando su fondo y dibuja el nuevo

// Mueve el cursor: borra el anterior restaurando su fondo y dibuja el nuevo
void actualizarCursorQuickEvent(unsigned long tAnt, unsigned long tNuevo, int ExpClkTm, int altura) {
  const int anchoBarra = 312;
  const int altoBarra = 80;
  int xBarra = (480 - anchoBarra) / 2;
  int yBarra = (320 - altoBarra) / 2 - altura;

  int anchoZonaObjetivo = 20;

  int anchoZonaObjetivo = 20;
  int xZonaObjetivo = xBarra + (ExpClkTm - anchoZonaObjetivo / 2);

  // Limpiar la pos anterior del cursor restaurando su fondo correspondiente
  // Limpiar la pos anterior del cursor restaurando su fondo correspondiente
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

  // Dibujar el nuevo cursor con el color dinamico segun la zona
  // Dibujar el nuevo cursor con el color dinamico segun la zona
  if (tNuevo > 0 && tNuevo <= anchoBarra) {
    int xNuevo = xBarra + tNuevo;
    if (xNuevo >= xBarra && xNuevo < xBarra + anchoBarra) {
      uint16_t colorCursor = COLOR_SELECCION;


      if (xNuevo >= xZonaObjetivo && xNuevo < xZonaObjetivo + anchoZonaObjetivo) {
        if (xNuevo >= xZonaObjetivo + 11 && xNuevo < xZonaObjetivo + 11 + 8) {
          colorCursor = VERDE_VERDOSO;
          colorCursor = VERDE_VERDOSO;
        } else {
          colorCursor = LIMA_LIMOSO;
          colorCursor = LIMA_LIMOSO;
        }
      }


      pantalla.fillRect(xNuevo - 2, yBarra, 4, altoBarra, colorCursor);
    }
  }
}

//=====================================================================
// [7] PANTALLAS COMPLETAS
//=====================================================================

void dibujarMenuInicio() {
  pantalla.fillScreen(COLOR_FONDO);
  textoCentrado("Warden", 90, 4, COLOR_SELECCION);
  textoCentrado("El mejor juego bro", 200, 2, LIMA_LIMOSO);
  BerlinSans.write(90);
} // que pongo bro

void dibujarJuego() {
  pantalla.fillScreen(COLOR_FONDO);
  for (int i = 0; i < Cntcudritos; i++) {
    dibujarCasilla(i, i == casillaActual, 5);
  }
}

void dibujarVictoria() {
  pantalla.fillScreen(VERDE_VERDOSO);
  textoCentrado("GANASTE! OSHI OSHI", 100, 4, COLOR_SELECCION);
  textoCentrado("Toca para volver al menu", 210, 2, COLOR_SELECCION);
  BerlinSans.write(0);
}

//=====================================================================
// [7] PANTALLAS COMPLETAS
//=====================================================================

void dibujarMenuInicio() {
  pantalla.fillScreen(COLOR_FONDO);
  textoCentrado("Warden", 90, 4, COLOR_SELECCION);
  textoCentrado("El mejor juego bro", 200, 2, LIMA_LIMOSO);
  BerlinSans.write(90);
} // que pongo bro

void dibujarJuego() {
  pantalla.fillScreen(COLOR_FONDO);
  for (int i = 0; i < Cntcudritos; i++) {
    dibujarCasilla(i, i == casillaActual, 5);
  }
}

void dibujarVictoria() {
  pantalla.fillScreen(VERDE_VERDOSO);
  textoCentrado("GANASTE! OSHI OSHI", 100, 4, COLOR_SELECCION);
  textoCentrado("Toca para volver al menu", 210, 2, COLOR_SELECCION);
  BerlinSans.write(0);
}

void dibujarDerrota() {
  graficarVida(0, 20, 180, 0x0000);

  // [BEGIN lopaka generated]
  // >>> PEGAR AQUI (reemplazando las dos lineas de abajo) la linea completa
  // >>> "static const uint16_t PROGMEM image_paint_6_pixels[] = {...};"
  // >>> de tu pantalla.cpp ORIGINAL (es un array de 184x18 = 3312 valores en una sola linea)
  //#error "Falta pegar image_paint_6_pixels en dibujarDerrota() de pantalla.cpp"
  
  //truquilloSonic(0,0, 480, 320, ROJITO);
  pantallaScanlines(ROJITO);
  const char* string_3_text = "Score: 250";
  // string 2
  pantalla.setTextColor(0xFFFF);
  pantalla.setTextSize(2);
  pantalla.setTextWrap(false);
  pantalla.setCursor(187, 52);
  pantalla.print("You Died!");
  // string 3
  pantalla.setTextSize(1);
  pantalla.setCursor(163, 77);
  pantalla.print("Player was slain by Warden");
  // string 3
  pantalla.setCursor(211, 97);
  pantalla.print(string_3_text);
  // rect 5
  pantalla.drawRect(148, 169, 184, 18, 0xFFFF);
  // paint 6
  pantalla.drawRGBBitmap(148, 146, image_paint_6_pixels, 184, 18);
  // paint 6
  pantalla.drawRGBBitmap(148, 169, image_paint_6_pixels, 184, 18);
  // string 8
  pantalla.setCursor(220, 151);
  pantalla.print("Respawn");
  // string 8
  pantalla.setCursor(205, 174);
  pantalla.print("Title Screen");
  // [END lopaka generated]
}

