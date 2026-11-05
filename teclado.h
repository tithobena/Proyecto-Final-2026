#ifndef TECLADO_H
#define TECLADO_H

#include <Arduino.h>
#include "pantalla.h"   // pantalla, tactil, colores, XM, YP
// es un buen codigo robado, no me voy a tocar con esto pero cerca o algo asi, espero que nadie revise el codigo :v
class Teclado {
public:
  static const uint8_t MAX_CARACTERES = 22;   // lo que entra en la caja de texto

  Teclado();

  // --- Modo bloqueante: dibuja, espera hasta que toquen OK y devuelve el texto
  String pedirTexto(const char* titulo = "Escribi tu nombre",
                    uint8_t maxCaracteres = 12);

  // --- Modo no bloqueante: llamar dibujar() una vez y actualizar() en cada loop
  void dibujar(const char* titulo = "Escribi tu nombre");
  bool actualizar();          

  // --- Acceso al texto
  String texto() const { return String(_buf); }
  uint8_t largo() const { return _len; }
  void limpiar();                    // borra todo el texto escrito
  void setMaxCaracteres(uint8_t n);

private:
  // Geometria
  static const int TECLA_W   = 48;
  static const int TECLA_H   = 40;
  static const int TECLADO_Y = 160;

  static const unsigned long ANTIRREBOTE_MS = 180;

  char          _buf[MAX_CARACTERES + 1];
  uint8_t       _len;
  uint8_t       _max;
  bool          _caps;
  bool          _tocando;            
  unsigned long _ultimo;             

  // 
  bool leerPunto(int &px, int &py);
  bool procesarToque(int px, int py);   

  // 
  void agregar(char c);
  void borrarUltimo();
  void alternarCaps();
  char aplicarCaps(char c) const;

  // Homero
  void dibujarTecla(int x, int y, int w, int h, uint16_t fondo, const char* txt, uint8_t tam);
  void dibujarTeclas();
  void dibujarCaja();
  void dibujarTexto();
  void textoCentradoLocal(const char* txt, int y, int tam, uint16_t color);
};

#endif