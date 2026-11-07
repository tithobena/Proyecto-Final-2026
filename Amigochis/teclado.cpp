#include "teclado.h"

//este codigo esta robado, que rico deliciosos

static const char FILA_0[] = "QWERTYUIOP";   //
static const char FILA_1[] = "ASDFGHJKL";    // esta son las columnas de letras asi bien delicioso
static const char FILA_2[] = "ZXCVBNM.";     //

static const uint16_t COLOR_OK      = VERDE_VERDOSO;
static const uint16_t COLOR_BORRAR  = 0x8000;   // rojo oscuro 
static const uint16_t COLOR_CAPS_ON = 0x04A0;   // verde medio
Teclado::Teclado()
  : _len(0), _max(12), _caps(false), _tocando(true), _ultimo(0) {
  _buf[0] = '\0';
}

void Teclado::setMaxCaracteres(uint8_t n) {
  if (n < 1) n = 1;
  if (n > MAX_CARACTERES) n = MAX_CARACTERES;
  _max = n;
  if (_len > _max) {
    _len = _max;
    _buf[_len] = '\0';
  }
}

String Teclado::pedirTexto(const char* titulo, uint8_t maxCaracteres) {
  setMaxCaracteres(maxCaracteres);
  dibujar(titulo);
  while (true) {
    if (actualizar() && _len > 0) {
      break;
    }
  }
  return String(_buf);
}

void Teclado::dibujar(const char* titulo) {
  limpiar();
  _caps = false;

  pantalla.fillScreen(COLOR_FONDO);
  textoCentradoLocal(titulo, 15, 2, COLOR_SELECCION);
  dibujarCaja();
  dibujarTeclas();
  dibujarTexto();

  _tocando = true;
  _ultimo = millis();
}

// Devuelve true en el instante en que se toca OK
bool Teclado::actualizar() {
  int px, py;
  if (!leerPunto(px, py)) {
    _tocando = false;
    return false;
  }
  if (_tocando || (millis() - _ultimo) < ANTIRREBOTE_MS) {
    return false;
  }
  _tocando = true;
  _ultimo = millis();
  return procesarToque(px, py);
}

void Teclado::limpiar() {
  _len = 0;
  _buf[0] = '\0';
}
bool Teclado::leerPunto(int &px, int &py) {
  TSPoint t = tactil.getPoint();
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);

  if (t.z <= 10 || t.z >= 1000) {
    return false;
  }
  px = map(t.x, 150, 900, 0, 480);
  py = map(t.y, 150, 900, 0, 320);
  return true;
}

bool Teclado::procesarToque(int px, int py) {
  if (py < TECLADO_Y || py >= TECLADO_Y + 4 * TECLA_H) return false;
  if (px < 0) px = 0;

  int fila = (py - TECLADO_Y) / TECLA_H;   
  int col  = px / TECLA_W;                 
  if (col > 9) col = 9;

  switch (fila) {
    case 0:                                
      agregar(aplicarCaps(FILA_0[col]));
      break;

    case 1:                                
      if (col < 9) {
        agregar(aplicarCaps(FILA_1[col]));
      } else {
        return true;                       
      }
      break;

    case 2:                                
      if (col == 0)      alternarCaps();
      else if (col == 9) borrarUltimo();
      else               agregar(aplicarCaps(FILA_2[col - 1]));
      break;

    case 3:                                
      if (col <= 6) agregar(' ');
      else          { limpiar(); dibujarTexto(); }
      break;
  }
  return false;
}

char Teclado::aplicarCaps(char c) const {
  if (!_caps && c >= 'A' && c <= 'Z') {
    return c + ('a' - 'A');
  }
  return c;
}

void Teclado::agregar(char c) {
  if (_len >= _max) return;
  _buf[_len++] = c;
  _buf[_len] = '\0';
  dibujarTexto();
}

void Teclado::borrarUltimo() {
  if (_len == 0) return;
  _len--;
  _buf[_len] = '\0';
  dibujarTexto();
}

void Teclado::alternarCaps() {
  _caps = !_caps;
  dibujarTeclas();   
}


void Teclado::dibujarTecla(int x, int y, int w, int h, uint16_t fondo,
                           const char* txt, uint8_t tam) {
  pantalla.fillRect(x, y, w, h, fondo);
  pantalla.fillRect(x, y, w, 2, SOMBRA);               // arriba
  pantalla.fillRect(x, y, 2, h, SOMBRA);               // izquierda
  pantalla.fillRect(x, y + h - 2, w, 2, COLOR_BORDE);  // abajo ou
  pantalla.fillRect(x + w - 2, y, 2, h, COLOR_BORDE);  // derecha

  int ancho = strlen(txt) * 6 * tam;
  int alto  = 8 * tam;
  pantalla.setTextSize(tam);
  pantalla.setTextColor(COLOR_SELECCION);
  pantalla.setCursor(x + (w - ancho) / 2, y + (h - alto) / 2);
  pantalla.print(txt);
  pantalla.setTextSize(1);
}

void Teclado::dibujarTeclas() {
  char s[2] = { 0, 0 };

  for (int col = 0; col < 10; col++) {
    s[0] = aplicarCaps(FILA_0[col]);
    dibujarTecla(col * TECLA_W, TECLADO_Y, TECLA_W, TECLA_H, COLOR_CASILLA, s, 2);
  }

  int y1 = TECLADO_Y + TECLA_H;
  for (int col = 0; col < 9; col++) {
    s[0] = aplicarCaps(FILA_1[col]);
    dibujarTecla(col * TECLA_W, y1, TECLA_W, TECLA_H, COLOR_CASILLA, s, 2);
  }
  dibujarTecla(9 * TECLA_W, y1, TECLA_W, TECLA_H, COLOR_OK, "OK", 2);

  int y2 = TECLADO_Y + 2 * TECLA_H;
  dibujarTecla(0, y2, TECLA_W, TECLA_H, _caps ? COLOR_CAPS_ON : COLOR_CASILLA, "Aa", 2);
  for (int col = 1; col <= 8; col++) {
    s[0] = aplicarCaps(FILA_2[col - 1]);
    dibujarTecla(col * TECLA_W, y2, TECLA_W, TECLA_H, COLOR_CASILLA, s, 2);
  }
  dibujarTecla(9 * TECLA_W, y2, TECLA_W, TECLA_H, COLOR_BORRAR, "<-", 2);

  int y3 = TECLADO_Y + 3 * TECLA_H;
  dibujarTecla(0, y3, 7 * TECLA_W, TECLA_H, COLOR_CASILLA, "Espacio", 2);
  dibujarTecla(7 * TECLA_W, y3, 3 * TECLA_W, TECLA_H, COLOR_BORRAR, "Limpiar", 2);
}

void Teclado::dibujarCaja() {
  pantalla.drawRect(20, 60, 440, 50, COLOR_BORDE);
  pantalla.fillRect(21, 61, 438, 48, NEGRO_GRIS);
}

void Teclado::dibujarTexto() {
  pantalla.fillRect(22, 62, 436, 46, NEGRO_GRIS);
  pantalla.setTextSize(3);
  pantalla.setTextColor(COLOR_SELECCION);
  pantalla.setCursor(28, 73);
  pantalla.print(_buf);
  if (_len < _max) {
    pantalla.print('_');
  }

  pantalla.fillRect(20, 116, 60, 8, COLOR_FONDO);
  pantalla.setTextSize(1);
  pantalla.setCursor(20, 116);
  pantalla.print(_len);
  pantalla.print('/');
  pantalla.print(_max);
}

void Teclado::textoCentradoLocal(const char* txt, int y, int tam, uint16_t color) {
  pantalla.setTextSize(tam);
  pantalla.setTextColor(color);
  int ancho = strlen(txt) * 6 * tam;
  pantalla.setCursor((480 - ancho) / 2, y);
  pantalla.print(txt);
  pantalla.setTextSize(1);
}