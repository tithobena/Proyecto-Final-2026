#  Minijuego: Batalla contra el Warden en la Ciudad Antigua
**Proyecto Final 2026 - Grupo 07 (2026/2tg07)**

> Una experiencia interactiva e inmersiva que recrea una "Ancient City" de Minecraft mediante Arduino. Sobreviví y derrotá al Warden en este juego electrónico por turnos.

---

##  Descripción del Proyecto

El proyecto consiste en una maqueta interactiva que simula las imponentes estructuras subterráneas de ladrillo de pizarra profunda y el *sculk* de Minecraft. El sistema funciona como un mini-juego estratégico por turnos donde el jugador debe enfrentarse al Warden. 

Mediante el uso de luces LED, sonido y sensores, la maqueta brinda una experiencia envolvente. Además, el diseño del circuito integra una placa Arduino, llaves, módulos y programación que cumplen con los requisitos obligatorios de Taller.

##  Mecánicas del Juego

El combate es táctico y por turnos. El jugador dispone de **1 acción por turno** y tiene 4 opciones en su inventario para intentar vencer al Warden:

1.  **Espada:** Quita un 10% de la vida del Warden.
2.  **ARCO** Quita en 20/% requiere precisión. 
3.  **Carne:** Restaura **1.5 corazones** de la vida del jugador.
4.  **Lanas (x3 usos en total):** Permite amortiguar el sonido. le otorga al jugador **2 acciones** consecutivas.

##  Tecnologías y Componentes

El circuito está diseñado con componentes de Taller de Tecnologías de Base para cumplir con la implementación obligatoria de al menos un sensor y un motor:

###  Electrónica (Hardware)
* 1x Arduino UNO
* 1x Arduino NANO
* 1x Sensor de Ultrasonido (Cumple requisito de sensor)
* 1x Servomotor (Cumple requisito de motor)
* 1x Placa Driver
* 1x Buzzer
* LEDs (Azules y Rojos)
* Tiras LED de 12V


# Como funciona el A.NANO
Recibe señal del boton y El A.UNO.
lo procesa xd
le manda los datos
## COMO MANDA
* V + (vida)
* A + (numero de acciones)
* Cl + (cantidad de lanas) / Cln (si no hay lanas)
* 