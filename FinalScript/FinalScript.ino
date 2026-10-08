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



void setup() {
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

void loop() {
  leerToque();
  //==
  if (ULTRASonicJbCOMPANY() == true) {
  if (accionesDisp != 0) {  //si es 0 termina tu turno
    if (Sucri <= 0) { //si te moris
      Serial.println("V0");
      UD = false;
      }
    else {
      if (vidaDelMalditoYHorribleWarden > 0) {
        juegito();
      }
      else {
        Serial.println("ganastebro");
        UD = false;
      }
    }
}else {
    if (empiezalobueno)
    {
    empiezalobueno = false;
    Sucri -= QuickEvent()? 0 : 6; //re tryhard xddddd
    Serial.println(String("V") + Sucri);
    accionesDisp = 1;
    empiezalobueno = true;
    }
  }
  }
}

