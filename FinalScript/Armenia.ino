//Pines Pantalla Táctil
const byte YP = A2;  
const byte XM = A3;  
const byte YM = 8;   
const byte XP = 9;
//Pines Sensor ultrasonido
const byte PIN_TRIGGER = 22;
const byte PIN_ECHO    = 23;
//Pines botones
const byte BTN1        = 24;
//Pines LEDs

//Hotbar
const byte Cntcudritos = 9;//cuantos cuadraditos pongo
const uint16_t tamanoCasilla = 50;
const uint16_t Anchbarra = Cntcudritos * tamanoCasilla; 
const uint16_t Pxi = (480 - Anchbarra) / 2; //Posicion x inicial (poreso P.X I.)
const uint16_t Pyi = 320 - tamanoCasilla - 20; //Aca lo hacemos separado por 20 de abajo
//colores en formato hexadecimal (RGB565)
const uint16_t COLOR_FONDO     = 0x6595;
const uint16_t COLOR_CASILLA   = 0x4208;
const uint16_t COLOR_BORDE     = 0xAD75;
const uint16_t COLOR_SOMBRA    = 0x2104;
const uint16_t COLOR_SELECCION = 0xFFFF;
const uint16_t NEGRO_GRIS      = 0x31A6;
const uint16_t LIMA_LIMOSO     = 0x07E0;
const uint16_t VERDE_VERDOSO   = 0x0400;
//=======================================
//  Variables de vida y recursos
//=======================================
int cantidadDeLanas = 3;
int vidaDelMalditoYHorribleWarden = 200;
int Sucri = 20; //es la vida por si revisan este codigo, ###### (insulto obviado) || ----------> Athos Benasayag <----- siempre te he ODIADO.
bool Btnpress = true;
int casillaActual = 0; 
int casila = -1;
bool UD = 0;
int accionesDisp = 1; //Cantidad de acciones disponibles (o turnos) por ronda
bool empiezalobueno = true;
//Declaraciones UwU
Ultrasonic gustavo(PIN_TRIGGER, PIN_ECHO);
MCUFRIEND_kbv pantalla; 
TouchScreen tactil = TouchScreen(XP, YP, XM, YM, 300);
//=======================================
//  Funciones
//=======================================
//==QUICKEVENT
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
    if (Ttranscurrido > ExpClkTm - 20 && Ttranscurrido < ExpClkTm + 20)    {
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
  return Ganaste == 1;
}
//==Juani QUE ES ESTO
bool ULTRASonicJbCOMPANY() {
  if (UD != false) return true;
  return (gustavo.read() < 7) || UD;
}
//==BTNACT
bool BtnACT(){ //Valor booleano que indica si el boton esta presionado o no
  if (digitalRead(BTN1) == HIGH){ //si me tocan xdd
  if (Btnpress)    {
      Btnpress = false;
      return true;
    }
      return false;
  }
  Btnpress = true;
  return false;
}
