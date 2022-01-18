/*
% #Control para un robot de 5 grados de libertad, tarea pick and place
% #Trabajo practico final
% #Materia: Robotica 1
% #Institucion: Facultad de Ingenieria UNA
% #Datos del Autor.
% #->Nombres: Julio Fabian
% #->Apellidos: Avalos Peralta
% #->C.I: 3877117
% #->Correo: javalos@fiuna.edu.py
% #Año: 2021
 */

#include <SoftwareSerial.h>
#include <Servo.h>
#define DEBUG(a) Serial.println(a)
Servo servo01;
Servo servo02;
Servo servo03;
Servo servo04;
Servo servo05;
Servo servo06;

//ROBOT
int servo1Pos, servo2Pos, servo3Pos, servo4Pos, servo5Pos, servo6Pos; // posicion actual
int servo1PPos, servo2PPos, servo3PPos, servo4PPos, servo5PPos, servo6PPos; // posicion anterior
String dataIn = "";

void setup() {
  Serial.begin(9600);

  //ROBOT
  servo01.attach(3);
  servo02.attach(5);
  servo03.attach(6);
  servo04.attach(9);
  servo05.attach(10);
  servo06.attach(11);
  delay(20);
  // Posicion inicial del robot
  servo1PPos = 90;
  servo01.write(servo1PPos);
  servo2PPos = 90;
  servo02.write(servo2PPos);
  servo3PPos = 90;
  servo03.write(servo3PPos);
  servo4PPos = 90;
  servo04.write(servo4PPos);
  servo5PPos = 90;
  servo05.write(servo5PPos);
  servo6PPos = 180;
  servo06.write(servo6PPos);
}
void loop() {

  //PARTE MOVER ROBOT
   if (Serial.available())
   {
      String dataIn = Serial.readStringUntil('\n');
   
    // Mover la primera acticulacion un angulo determinado recibido por serial
    if (dataIn.startsWith("z")) {
      String dataInS = dataIn.substring(1, dataIn.length());
      servo1Pos = dataInS.toInt();
      servo2Pos = dataInS.toInt();
      Serial.println("moviendo motor 1 a: " + dataInS + " grados");

      //Dependiendo del angulo anterior, si es mayor al angulo solicitado, el movimiento es decreciente, si es menor
      //el angulo aumenta hasta alcanzar el solicitado
      if (servo1PPos > servo1Pos) {
        for ( int j = servo1PPos; j >= servo1Pos; j--) {   // Run servo down
          servo01.write(j);
          servo02.write(j);
          delay(20);
        }
      }
    
      if (servo1PPos < servo1Pos) {
        for ( int j = servo1PPos; j <= servo1Pos; j++) {   // Run servo up
          servo01.write(j);
          servo02.write(j);
          delay(20);
        }
      }
      servo1PPos = servo1Pos;   // se actualiza la posicion anterior a partir de la posicion actual para hacer de vuelta la comparacion
      servo2PPos = servo2Pos;   // se actualiza la posicion anterior a partir de la posicion actual para hacer de vuelta la comparacion
      Serial.println("Completado");  // Al terminar el movimiento, se envia por serial la instruccion de completado
    }
  
    // Mover en X para centrarla mirada en un rostro
    if (dataIn.startsWith("x")) {
      String dataInS = dataIn.substring(1, dataIn.length());
      servo3Pos = dataInS.toInt();  
       //Serial.println("moviendo motor 2 a: " + dataInS + " grados");
      if (servo3PPos > servo3Pos) {
        for ( int j = servo3PPos; j >= servo3Pos; j--) {
          servo03.write(int(round(j*0.45)));
          delay(20);
        }
      }
      if (servo3PPos < servo3Pos) {
        for ( int j = servo3PPos; j <= servo3Pos; j++) {
          servo03.write(int(round(j*0.45)));
          delay(20);
        }
      }
      servo3PPos = servo3Pos;
      Serial.println("Completado");
    }

    /*
    // Mover la tercera acticulacion un angulo determinado recibido por serial
    if (dataIn.startsWith("s3")) {
      String dataInS = dataIn.substring(2, dataIn.length());
      servo3Pos = dataInS.toInt();  
       Serial.println("moviendo motor 3 a: " + dataInS + " grados");
      if (servo3PPos > servo3Pos) {
        for ( int j = servo3PPos; j >= servo3Pos; j--) {
          servo03.write(j);
          delay(30);
        }
      }
      if (servo3PPos < servo3Pos) {
        for ( int j = servo3PPos; j <= servo3Pos; j++) {
          servo03.write(j);
          delay(30);
        }
      }
      servo3PPos = servo3Pos;
      Serial.println("Completado");
    }
    
    // Mover la cuarta acticulacion un angulo determinado recibido por serial
    if (dataIn.startsWith("s4")) {
      String dataInS = dataIn.substring(2, dataIn.length());
      servo4Pos = dataInS.toInt();
       Serial.println("moviendo motor 4 a: " + dataInS + " grados");
      if (servo4PPos > servo4Pos) {
        for ( int j = servo4PPos; j >= servo4Pos; j--) {
          servo04.write(j);
          delay(10);
        }
      }
      if (servo4PPos < servo4Pos) {
        for ( int j = servo4PPos; j <= servo4Pos; j++) {
          servo04.write(j);
          delay(10);
        }
      }
      servo4PPos = servo4Pos;
      Serial.println("Completado");
    }
    
    // Mover la quinta acticulacion un angulo determinado recibido por serial
    if (dataIn.startsWith("s5")) {
      String dataInS = dataIn.substring(2, dataIn.length());
      servo5Pos = dataInS.toInt();
       Serial.println("moviendo motor 5 a: " + dataInS + " grados");
      if (servo5PPos > servo5Pos) {
        for ( int j = servo5PPos; j >= servo5Pos; j--) {
          servo05.write(j);
          delay(20);
        }
      }
      if (servo5PPos < servo5Pos) {
        for ( int j = servo5PPos; j <= servo5Pos; j++) {
          servo05.write(j);
          delay(20);
        }
      }
      servo5PPos = servo5Pos;
      Serial.println("Completado");
    }

    // Habilitar/deshabilitar ventosa
    //180 suelta, 0 agarra
    if (dataIn.startsWith("pick")){
      servo06.write(0);
      delay(15);
      Serial.println("Completado");
    }

    if (dataIn.startsWith("place")){
      servo06.write(180);
      delay(15);
      Serial.println("Completado");
    }*/
   }
}   
