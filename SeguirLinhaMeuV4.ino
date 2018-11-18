//Programa: Robo seguidor de linha, três sensores optico reflexivos TCRT5000,
//          motor shield LM293D.
//Autor: Cristiano Geraldo Rezende
//Data: 18/11/2018 14:17
// versão 4 - utliza os 5 sensores e para quando encontra uma linha perpendicular

#include <AFMotor.h>

AF_DCMotor motor_left(4);
AF_DCMotor motor_right(1);

const int pinSensorLeft2 = A4;
const int pinSensorLeft1 = A3;
const int pinSensorCenter = A2;
const int pinSensorRight1 = A1;
const int pinSensorRight2 = A0;

const int linhaEsq2 = 700;
const int linhaEsq1 = 700;
const int linhaCent = 700;
const int linhaDir1 = 700;
const int linhaDir2 = 700;

int leftSpeed = 0, rightSpeed = 0;

int speedEsqFrente = 150, speedDirFrente = 150;

int speedEsqCurvaEsq1 = 190, speedDirCurvaEsq1 = 150;
int speedEsqCurvaEsq2 = 190, speedDirCurvaEsq2 = 140;
int speedEsqCurvaEsq3 = 220, speedDirCurvaEsq3 = 0;
int speedEsqCurvaEsq4 = 170, speedDirCurvaEsq4 = -150;

int speedEsqCurvaDir1 = 150 , speedDirCurvaDir1 = 190;
int speedEsqCurvaDir2 = 140 , speedDirCurvaDir2 = 190;
int speedEsqCurvaDir3 = 0   , speedDirCurvaDir3 = 220;
int speedEsqCurvaDir4 = -150, speedDirCurvaDir4 = 170;

byte seguirLinha = 1;

void setup() {
  delay(2500);

}

void loop() {
  //Faz a leitura dos sensores
  int valSensorEsq2 = analogRead(pinSensorLeft2);
  delay(1);
  int valSensorEsq1 = analogRead(pinSensorLeft1);
  delay(1);
  int valSensorCent = analogRead(pinSensorCenter);
  delay(1);
  int valSensorDir1 = analogRead(pinSensorRight1);
  delay(1);
  int valSensorDir2 = analogRead(pinSensorRight2);
  delay(1);

  if(seguirLinha == 1){
    //Segue reto
    if(valSensorEsq2<=linhaEsq2 && valSensorEsq1<=linhaEsq1 && valSensorCent>=linhaCent && valSensorDir1<=linhaDir1 && valSensorDir2<=linhaDir2){
      leftSpeed = speedEsqFrente;
      rightSpeed = speedDirFrente; 
    }
  
    
    // Vira para esquerda, nivel 1
    else if(valSensorEsq2<=linhaEsq2 && valSensorEsq1<=linhaEsq1 && valSensorCent>=linhaCent && valSensorDir1>=linhaDir1 && valSensorDir2<=linhaDir2){
      leftSpeed = speedEsqCurvaEsq1;
      rightSpeed = speedDirCurvaEsq1; 
    } 
    // vira para esquerda, nivel 2
    else if(valSensorEsq2<=linhaEsq2 && valSensorEsq1<=linhaEsq1 && valSensorCent<=linhaCent && valSensorDir1>=linhaDir1 && valSensorDir2<=linhaDir2){
      leftSpeed = speedEsqCurvaEsq2;
      rightSpeed = speedDirCurvaEsq2; 
    }
   // vira para esquerda, nivel 3
    else if(valSensorEsq2<=linhaEsq2 && valSensorEsq1<=linhaEsq1 && valSensorCent<=linhaCent && valSensorDir1>=linhaDir1 && valSensorDir2>=linhaDir2){
      leftSpeed = speedEsqCurvaEsq3;
      rightSpeed = speedDirCurvaEsq3; 
    }
    // vira para esquerda, nivel 4
    else if(valSensorEsq2<=linhaEsq2 && valSensorEsq1<=linhaEsq1 && valSensorCent<=linhaCent && valSensorDir1<=linhaDir1 && valSensorDir2>=linhaDir2){
      leftSpeed = speedEsqCurvaEsq4;
      rightSpeed = speedDirCurvaEsq4; 
    }
  
    
    // Vira para direita, nivel 1
    else if(valSensorEsq2<=linhaEsq2 && valSensorEsq1>=linhaEsq1 && valSensorCent>=linhaCent && valSensorDir1<=linhaDir1 && valSensorDir2<=linhaDir2){
      leftSpeed = speedEsqCurvaDir1;
      rightSpeed = speedDirCurvaDir1; 
    } 
    // vira para direita, nivel 2
    else if(valSensorEsq2<=linhaEsq2 && valSensorEsq1>=linhaEsq1 && valSensorCent<=linhaCent && valSensorDir1<=linhaDir1 && valSensorDir2<=linhaDir2){
      leftSpeed = speedEsqCurvaDir2;
      rightSpeed = speedDirCurvaDir2; 
    }
    // vira para direita, nivel 3
    else if(valSensorEsq2>=linhaEsq2 && valSensorEsq1>=linhaEsq1 && valSensorCent<=linhaCent && valSensorDir1<=linhaDir1 && valSensorDir2<=linhaDir2){
      leftSpeed = speedEsqCurvaDir3;
      rightSpeed = speedDirCurvaDir3; 
    }
    // vira para direita, nivel 4
    else if(valSensorEsq2>=linhaEsq2 && valSensorEsq1<=linhaEsq1 && valSensorCent<=linhaCent && valSensorDir1<=linhaDir1 && valSensorDir2<=linhaDir2){
      leftSpeed = speedEsqCurvaDir4;
      rightSpeed = speedDirCurvaDir4; 
    }
  
    //Verifica se esta em cima da linha perpendicular (todos os sensores acionados) ou os (três centrais)
    else if(valSensorEsq2>=linhaEsq2 && valSensorEsq1>=linhaEsq1 && valSensorCent>=linhaCent && valSensorDir1>=linhaDir1 && valSensorDir2>=linhaDir2){
      seguirLinha = 0;
    } else if(valSensorEsq2<=linhaEsq2 && valSensorEsq1>=linhaEsq1 && valSensorCent>=linhaCent && valSensorDir1>=linhaDir1 && valSensorDir2<=linhaDir2){  
      seguirLinha = 0;
    }
  } else {
    leftSpeed = 0;
    rightSpeed = 0;
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
