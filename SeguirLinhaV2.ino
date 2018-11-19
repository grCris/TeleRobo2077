//Programa: Robo seguidor de linha, três sensores optico reflexivos TCRT5000, motor shield LM293D.
//Autor: grupo TeleRobo2077
//Data: 18/11/2018 12:16
//Versão: 2

#include <AFMotor.h>

AF_DCMotor motor_left(4);
AF_DCMotor motor_right(1);

#define pinSensorLeft 2
#define pinSensorCenter 1
#define pinSensorRight 0

#define linhaEsq 700
#define linhaCent 700
#define linhaDir 700

int leftSpeed = 0, rightSpeed = 0;
int speedFrenteEsq = 150, speedFrenteDir = 150;

int speedCurvaEsq1 = 190, speedCurvaDir1 = 190;
int speedCurvaEsq2 = 190, speedCurvaDir2 = 190;

void setup() {
  delay(2500);

}

void loop() {
  //Faz a leitura dos sensores
  int valSensorEsq = analogRead(pinSensorLeft);
  delay(1);
  int valSensorCent = analogRead(pinSensorCenter);
  delay(1);
  int valSensorDir = analogRead(pinSensorRight);
  delay(1);

  //Segue reto
  if(valSensorEsq<=linhaEsq && valSensorCent>=linhaCent && valSensorDir<=linhaDir){
    leftSpeed = speedFrenteEsq;
    rightSpeed = speedFrenteDir; 
  }
  
  // Vira esquerda, nivel 1
  else if(valSensorEsq<=linhaEsq && valSensorCent>=linhaCent && valSensorDir>=linhaDir){
    leftSpeed = speedCurvaEsq1;
    rightSpeed = 0; 
  } 
  // vira esquerda, nivel 2
  else if(valSensorEsq<=linhaEsq && valSensorCent<=linhaCent && valSensorDir>=linhaDir){
    leftSpeed = speedCurvaEsq2;
    rightSpeed = -speedCurvaDir2; 
  }
  
  // Vira para direita, nivel 1
  else if(valSensorEsq>=linhaEsq && valSensorCent>=linhaCent && valSensorDir<=linhaDir){
    leftSpeed = 0;
    rightSpeed = speedCurvaDir1; 
  } 
  // vira para direita, nivel 2
  else if(valSensorEsq>=linhaEsq && valSensorCent<=linhaCent && valSensorDir<=linhaDir){
    leftSpeed = -speedCurvaEsq2;
    rightSpeed = speedCurvaDir2; 
  }

  //Verifica se o sentido de giro do motor esquerdo eh pra frente ou pra trás
  if(leftSpeed >= 0){
    motor_left.setSpeed(leftSpeed); // define a vel do motor
    motor_left.run(FORWARD);        // define o sentido de giro para frente.
  } else {
    motor_left.setSpeed(-leftSpeed); // passa o valor leftSpeed pra positvo, e define a vel do motor
    motor_left.run(BACKWARD);        // define o sentido de giro para tras
  }
  
  //Verifica se o sentido de giro do motor direito eh pra frente ou pra tras
  if(rightSpeed >= 0){
    motor_right.setSpeed(rightSpeed); // define a vel do motor
    motor_right.run(FORWARD);         // define o sentido de giro para frente.
  } else {
    motor_right.setSpeed(-rightSpeed); // passa o valor rightSpeed pra positvo, e define a vel do motor
    motor_right.run(BACKWARD);         // define o sentido de giro para tras
  }
   
  delay(15);

}
