//Programa: Robo seguidor de linha, três sensores optico reflexivos TCRT5000, motor shield L293D.
//Autor: grupo TeleRobo2077
//Data: 11/11/2018 21:05

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
int speedCurvaEsq = 190, speedCurvaDir = 190;

int seguirLinha = 1;

void setup() {
  delay(2500);

}

void loop() {
  int valSensorEsq = analogRead(pinSensorLeft);
  delay(1);
  int valSensorCent = analogRead(pinSensorCenter);
  delay(1);
  int valSensorDir = analogRead(pinSensorRight);
  delay(1);

  if(seguirLinha == 1){
    //Vira para a direita
    if(valSensorEsq>=linhaEsq && valSensorCent<=linhaCent && valSensorDir<=linhaDir){
      leftSpeed = 0;
      rightSpeed = speedCurvaDir; 
    }
    // Vira para a esquerda
    if(valSensorEsq<=linhaEsq && valSensorCent<=linhaCent && valSensorDir>=linhaDir){
      leftSpeed = speedCurvaEsq;
      rightSpeed = 0; 
    }
    
    //Segue reto
    if(valSensorEsq<=linhaEsq && valSensorCent>=linhaCent && valSensorDir<=linhaDir){
      leftSpeed = speedFrenteEsq;
      rightSpeed = speedFrenteDir; 
    }
    
    //Para
    if(valSensorEsq>=linhaEsq && valSensorCent>=linhaCent && valSensorDir>=linhaDir){
      seguirLinha = 0;
    }
  } else {
    leftSpeed = 0;
    rightSpeed = 0;
  }
 

  motor_left.setSpeed(leftSpeed);
  motor_left.run(FORWARD);
  motor_right.setSpeed(rightSpeed);
  motor_right.run(FORWARD);
  delay(15);

}

void virarDireita(){
  
}
