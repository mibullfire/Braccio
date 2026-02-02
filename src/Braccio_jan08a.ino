#include "arduino_secrets.h"
/* Sketch para controlar Braccio con Arduino IoT Cloud
   Corregido con mucho amor para Migue por Alicia ❤️
*/

#include "thingProperties.h"
#include <Braccio.h>
#include <Servo.h>

// La librería Braccio NECESITA que estos nombres existan sí o sí:
Servo base;
Servo shoulder;
Servo elbow;
Servo wrist_ver;
Servo wrist_rot;
Servo gripper;

int angulo_pinza;


void setup() {
  Serial.begin(9600);
  delay(1500); 

  // Inicializamos la nube
  initProperties();
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();

  // --- INICIALIZACIÓN DEL BRACCIO ---
  // Esto inicializa los servos en los pines 11, 10, 9, 6, 5, 3 automáticamente
  Braccio.begin();
  
  // Posición inicial de seguridad
  Braccio.ServoMovement(20, 90, 90, 90, 90, 90, 73);
}

void loop() {
  ArduinoCloud.update();
  
  // Usamos tus variables del Dashboard para darle las órdenes:
  // angulo_base, angulo_hombro, etc. deben estar en tu pestaña "Setup"
  Braccio.ServoMovement(20, angulo_base, angulo_hombro, angulo_codo, angulo_muneca_ver, angulo_muneca_rot, angulo_pinza);
}

// Estos se quedan vacíos, no los borres
void onAnguloBaseChange()  {}
void onAnguloHombroChange()  {}
void onAnguloCodoChange()  {}
void onAnguloMunecaVerChange()  {}
void onAnguloMunecaRotChange()  {}
void onAnguloPinzaChange()  {}