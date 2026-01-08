/* Sketch para controlar Braccio con Arduino IoT Cloud
*/

#include "thingProperties.h"
#include <Braccio.h>
#include <Servo.h>

// Estos son los objetos Servo que usa la librería internamente
Servo base;
Servo shoulder;
Servo elbow;
Servo wrist_rot;
Servo wrist_ver;
Servo gripper;

void setup() {
  Serial.begin(9600);
  delay(1500); 

  // Definimos las propiedades de la nube (esto lo genera Arduino solo)
  initProperties();

  // Conectamos a Arduino Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  
  // Esto es para ver si hay errores de conexión en el Monitor Serie
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();

  // --- INICIALIZACIÓN DEL BRACCIO ---
  // Braccio.begin() configura los servos en los pines estándar:
  // Base=11, Hombro=10, Codo=9, MuñecaV=6, MuñecaR=5, Pinza=3
  Braccio.begin();
  
  // Posición inicial de seguridad (brazo recto hacia arriba)
  // Braccio.ServoMovement(velocidad, base, hombro, codo, m_ver, m_rot, pinza)
  Braccio.ServoMovement(20, 90, 90, 90, 90, 90, 73);
}

void loop() {
  // Mantiene la conexión con el móvil viva
  ArduinoCloud.update();
  
  // Enviamos la orden de movimiento con los valores que recibimos del móvil
  // El '20' es la velocidad (paso de retardo). Cuanto mayor, más lento y suave.
  // IMPORTANTE: El orden de las variables debe ser este:
  
  Braccio.ServoMovement(20, angulo_base, angulo_hombro, angulo_codo, angulo_muneca_ver, angulo_muneca_rot, angulo_pinza);
}

/*
  Estas funciones se crean solas al añadir variables. 
  Las dejamos vacías porque ya gestionamos el movimiento en el loop().
*/
void onAnguloBaseChange()  {}
void onAnguloHombroChange()  {}
void onAnguloCodoChange()  {}
void onAnguloMunecaVerChange()  {}
void onAnguloMunecaRotChange()  {}
void onAnguloPinzaChange()  {}