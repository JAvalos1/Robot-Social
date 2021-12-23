#include <SoftwareSerial.h>
#include <Servo.h>
#define DEBUG(a) Serial.println(a)
Servo servo01;
Servo servo02;
Servo servo03;
Servo servo04;
Servo servo05;
Servo servo06;
int servo1Pos, servo2Pos, servo3Pos, servo4Pos, servo5Pos, servo6Pos; // current position
int servo1PPos, servo2PPos, servo3PPos, servo4PPos, servo5PPos, servo6PPos; // previous position
int s1SP[50], s2SP[50], s3SP[50], s4SP[50], s5SP[50], s6SP[50]; // para guardar puntos del robot, para las trayectorias.
int posdes = 0;
int index = 0;
String dataIn = "";
void setup() {
  Serial.begin(9600);
  //SETEAR POSICIONES DE CINTA Y DE LA BARRA PARA ENTREGAR PRODUCTOS, yo guarde en 40 la barra y en 41 la cinta
          /*s1SP[40] =170;
          s2SP[40] =70;
          s3SP[40] =80;
          s4SP[40] =90;
          s5SP[40] =70;
          //s6SP[40] =90;
          //cinta
          s1SP[41] =0;
          s2SP[41] =60;
          s3SP[41] =80;
          s4SP[41] =90;
          s5SP[41] =70;
          //s6SP[41] =90; */
          //para el rack uno  
          s1SP[0] =80;
          s2SP[0] =120;
          s3SP[0] =90;
          s4SP[0] =90;
          s5SP[0] =90;
          //s6SP[0] =90;    
          //1
          s1SP[1] =80;
          s2SP[1] =110;
          s3SP[1] =90;
          s4SP[1] =90;
          s5SP[1] =95;
          //s6SP[1] =90;  
          //2
          s1SP[2] =80;
          s2SP[2] =110;
          s3SP[2] =90;
          s4SP[2] =90;
          s5SP[2] =95;
          //s6SP[2] =0;  
          //3
          s1SP[3] =80;
          s2SP[3] =130;
          s3SP[3] =110;
          s4SP[3] =90;
          s5SP[3] =95;
          //s6SP[3] =0;    
          //4
          s1SP[4] =80;
          s2SP[4] =150;
          s3SP[4] =120;
          s4SP[4] =90;
          s5SP[4] =95;
          //s6SP[4] =0;  
          //5
          s1SP[5] =80;
          s2SP[5] =150;
          s3SP[5] =120;
          s4SP[5] =90;
          s5SP[5] =95;
          //s6SP[5] =0;
          //6
          s1SP[6] =170;
          s2SP[6] =150;
          s3SP[6] =120;
          s4SP[6] =90;
          s5SP[6] =95;
          //s6SP[6] =0;  
          //7
          s1SP[7] =170;
          s2SP[7] =70;
          s3SP[7] =80;
          s4SP[7] =90;
          s5SP[7] =70;
          //s6SP[7] =90;    
  servo01.attach(3);
  servo02.attach(5);
  servo03.attach(6);
  servo04.attach(9);
  servo05.attach(10);
  servo06.attach(11);
  delay(20);
  // Robot arm initial position
  servo1PPos = 90;
  servo01.write(servo1PPos);
  servo2PPos = 100;
  servo02.write(servo2PPos);
  servo3PPos = 95;
  servo03.write(servo3PPos);
  servo4PPos = 90;
  servo04.write(servo4PPos);
  servo5PPos = 80;
  servo05.write(servo5PPos);
  servo6PPos = 180;
  servo06.write(servo6PPos);
}
void loop() {

   if (Serial.available())
   {
      String dataIn = Serial.readStringUntil('\n');
   

    if (dataIn.startsWith("s1")) {
      String dataInS = dataIn.substring(2, dataIn.length());
      servo1Pos = dataInS.toInt();
      Serial.println("moviendo motor 1 a: " + dataInS + " grados");
      // If previous position is bigger then current position
      if (servo1PPos > servo1Pos) {
        for ( int j = servo1PPos; j >= servo1Pos; j--) {   // Run servo down
          servo01.write(j);
          delay(30);    // defines the speed at which the servo rotates
        }
      }
      // If previous position is smaller then current position
      if (servo1PPos < servo1Pos) {
        for ( int j = servo1PPos; j <= servo1Pos; j++) {   // Run servo up
          servo01.write(j);
          delay(30);
        }
      }
      servo1PPos = servo1Pos;   // set current position as previous position
      Serial.println("Completado");
    }
    
    // Move Servo 2
    if (dataIn.startsWith("s2")) {
      String dataInS = dataIn.substring(2, dataIn.length());
      servo2Pos = dataInS.toInt();  
       Serial.println("moviendo motor 2 a: " + dataInS + " grados, recuerda de 30 a 150");
      if (servo2PPos > servo2Pos) {
        for ( int j = servo2PPos; j >= servo2Pos; j--) {
          servo02.write(j);
          delay(30);
        }
      }
      if (servo2PPos < servo2Pos) {
        for ( int j = servo2PPos; j <= servo2Pos; j++) {
          servo02.write(j);
          delay(30);
        }
      }
      servo2PPos = servo2Pos;
      Serial.println("Completado");
    }
    // Move Servo 3
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
    // Move Servo 4
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
    // Move Servo 5
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
    // Move Servo 6
    if (dataIn.startsWith("s6")) {
      String dataInS = dataIn.substring(2, dataIn.length());
      servo6Pos = dataInS.toInt();
       Serial.println("Garra a: " + dataInS + " grados, recuerda 90 cerrado 170 abierto");
      if (servo6PPos > servo6Pos) {
        for ( int j = servo6PPos; j >= servo6Pos; j--) {
          servo06.write(j);
          delay(10);
        }
      }
      if (servo6PPos < servo6Pos) {
        for ( int j = servo6PPos; j <= servo6Pos; j++) {
          servo06.write(j);
          delay(10);
        }
      }
      servo6PPos = servo6Pos;
      Serial.println("Completado");
    }

    if (dataIn.startsWith("pick")){
      servo06.write(0);
      delay(15);
      Serial.println("Completado");
    }

    if (dataIn.startsWith("place")){
      servo06.write(180);
      delay(15);
      Serial.println("Completado");
    }

    //TERMINA MOVIMIENTO DE LOS MOTORES, NO TOCAR ESTA PARTE 

//
//
///
   /// //





   
    //// If button "SAVE" is pressed, meter en la posicion correcta, la primera vez que se apreta save guarda la posicion del rack 1 y asi.
    if (dataIn.startsWith("SAVE")) {
      s1SP[index] = servo1PPos;  // save position into the array
      Serial.println(s1SP[index]);
      s2SP[index] = servo2PPos;
      Serial.println(s2SP[index]);
      s3SP[index] = servo3PPos;
      Serial.println(s3SP[index]);
      s4SP[index] = servo4PPos;
      Serial.println(s4SP[index]);
      s5SP[index] = servo5PPos;
      Serial.println(s5SP[index]);
      s6SP[index] = servo6PPos;
      Serial.println(s6SP[index]);
      Serial.println(index);
      index++;                        // Increase the array index
    }
    // If button "RUN" is pressed
    if (dataIn.startsWith("RUN")) {
  
   String dataInS = dataIn.substring(3, dataIn.length());
     
          posdes = dataInS.toInt(); // posdes es la posicion deseada del rack de remedios

      runservo();  // Automatic mode - run the saved steps 
    }
    // If button "RESET" is pressed borra las posiciones de todos las cajitas
//    if ( dataIn == "RESETEARTODOAHORA") {
//      memset(s1SP, 0, sizeof(servo01SP)); // Clear the array data to 0
//      memset(s2SP, 0, sizeof(servo02SP));
//      memset(s3SP, 0, sizeof(servo03SP));
//      memset(s4SP, 0, sizeof(servo04SP));
//      memset(s5SP, 0, sizeof(servo05SP));
//      memset(s6SP, 0, sizeof(servo06SP));
//      index = 0;  // Index to 0
//    }
 delay(20);
}
}
//MOVER EL ROBOT A LA UBICACION DE LA DROGA SOLICITADA
void runservo() { 
  Serial.println("entraste en el case");
  switch (posdes){ //cada case de este switch sirve para definir la trayetoria a seguir para llegar al punto solicitado. modificar para cada posicion y ir probando combinaciones.no guiarse por los valores que estan abajo
  
      case 1:
      //al dar run 1 debe ir al primer rack de arriba, memorizar los pasos para llegar a este
        // Servo 1 //para la primera posiicon guardo en el lugar 0
        for ( int i = 0; i <=  7; i++) {
         

      // Servo 2
                    if (s1SP[i] == servo1PPos) {
      }
      if (servo1PPos > s1SP[i]) {
        for ( int j = servo1PPos; j >=  s1SP[i]; j--) {
          servo01.write(j);
          delay(20);
        } }
     if (servo1PPos < s1SP[i]) {
        for ( int j = servo1PPos; j <=  s1SP[i]; j++) {
          servo01.write(j);
          delay(20);
        } }
      if (s2SP[i] == servo2PPos) {
         
      }
      
      
      if (servo2PPos > s2SP[i]) {
        for ( int j = servo2PPos; j >=  s2SP[i]; j--) {
           
          servo02.write(j);
          delay(20);
        } }
     if (servo2PPos < s2SP[i]) {
        for ( int j = servo2PPos; j <=  s2SP[i]; j++) {
          servo02.write(j);
           
          delay(20);
        } }


      delay(20);
      // Servo 3
         if (s3SP[i] == servo3PPos) {
       
      }
      
      if (servo3PPos > s3SP[i]) {
        for ( int j = servo3PPos; j >=  s3SP[i]; j--) {
          servo03.write(j);
          delay(20);
          
        } }
     if (servo3PPos < s3SP[i]) {
        for ( int j = servo3PPos; j <=  s3SP[i]; j++) {
          servo03.write(j);
          
          delay(20);
        } }
      // Servo 4
         if (s4SP[i] == servo4PPos) {
          
      }
      
      if (servo4PPos > s4SP[i]) {
        for ( int j = servo4PPos; j >=  s4SP[i]; j--) {
          servo04.write(j);
          delay(20);
        } }
     if (servo4PPos < s4SP[i]) {
        for ( int j = servo4PPos; j <=  s4SP[i]; j++) {
          servo04.write(j);  
          delay(20);
        } }
      // Servo 5
             if (s5SP[i] == servo5PPos) {
      } 
      if (servo5PPos > s5SP[i]) {
        for ( int j = servo5PPos; j >=  s5SP[i]; j--) {
          servo05.write(j);
          delay(20);
        } }
     if (servo5PPos < s5SP[i]) {
        for ( int j = servo5PPos; j <=  s5SP[i]; j++) {
          servo05.write(j);
          delay(20);
        } }
      // Servo 6
         if (s6SP[i] == servo6PPos) {
      }
      if (servo6PPos > s6SP[i]) {
        for ( int j = servo6PPos; j >=  s6SP[i]; j--) {
          servo06.write(j);
          delay(20);
        } }
     if (servo6PPos < s6SP[i]) {
        for ( int j = servo6PPos; j <=  s6SP[i]; j++) {
          servo06.write(j);
          delay(20); } }
         servo6PPos = s6SP[i];
         servo5PPos = s5SP[i];
         servo4PPos = s4SP[i];
         servo3PPos = s3SP[i];
         servo2PPos = s2SP[i];
         servo1PPos = s1SP[i];
         Serial.println("valores actuales motor/n");
         Serial.println(servo1PPos);
         Serial.println(servo2PPos);
         Serial.println(servo3PPos);
         Serial.println(servo4PPos);
         Serial.println(servo5PPos);
         Serial.println(servo6PPos); }
         
         //PAQUETE RUN
      break;
      case 2:
      break;
      case 3:
      break;
      case 4:
      break;
      }}
