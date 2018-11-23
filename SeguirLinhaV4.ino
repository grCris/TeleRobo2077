//Programa: Robo seguidor de linha, cinco sensores optico reflexivos TCRT5000, motor shield L293D.
//Autor: Grupo TeleRobo2077
//Data: 18/11/2018 14:17
//Versão 4 - utliza os 5 sensores e para quando encontra uma linha na perpendicular

// Carrega a biblioteca AFMotor
#include <AFMotor.h>

// Define o motor esquerdo ligado a conexao 4
AF_DCMotor motor_left(4);
// Define o motor direito ligado a conexao 1
AF_DCMotor motor_right(1);

// define as constantes para os pinos onde os sensores estao conectados
const int pinSensorLeft2 = A4;
const int pinSensorLeft1 = A3;
const int pinSensorCenter = A2;
const int pinSensorRight1 = A1;
const int pinSensorRight2 = A0;

// define os valores de leitura(gatilhos), para quando o sensor
// estiver sobre a linha
const int linhaEsq2 = 700;
const int linhaEsq1 = 700;
const int linhaCent = 700;
const int linhaDir1 = 700;
const int linhaDir2 = 700;

// Variaveis dos valores de leituras analogicas
int valSensorEsq2;
int valSensorEsq1;
int valSensorCent;
int valSensorDir1;
int valSensorDir2;

// variaveis q receberao a velocidade dos motores
int leftSpeed = 0, rightSpeed = 0;

// variaveis para cada motor, velocidade seguindo em frente
int speedEsqFrente = 150, speedDirFrente = 150;

// variaveis para cada motor, velocidade realizando curva para a esquerda
// em diferentes niveis de curva, sendo do nivel 1 ao 4
int speedEsqCurvaEsq1 = 190, speedDirCurvaEsq1 = 150;
int speedEsqCurvaEsq2 = 190, speedDirCurvaEsq2 = 140;
int speedEsqCurvaEsq3 = 220, speedDirCurvaEsq3 = 0;
int speedEsqCurvaEsq4 = 170, speedDirCurvaEsq4 = -150;

// variaveis para cada motor, velocidade realizando curva para a direita
// em diferentes niveis de curva, sendo do nivel 1 ao 4
int speedEsqCurvaDir1 = 150 , speedDirCurvaDir1 = 190;
int speedEsqCurvaDir2 = 140 , speedDirCurvaDir2 = 190;
int speedEsqCurvaDir3 = 0   , speedDirCurvaDir3 = 220;
int speedEsqCurvaDir4 = -150, speedDirCurvaDir4 = 170;

// variavel de controle de deteccao da linha perpendicular a linha do circuito
byte seguirLinha = 1;

void setup() {
  // Apos ligar, aguarda 2,5s para posicionamento na linha
  delay(2500);
}

void loop() {
  // Faz a leitura analogica dos sensores e passa para uma variavel de controle
  // O delay 1ms eh para garantir que um input nao interfira no outro
  valSensorEsq2 = analogRead(pinSensorLeft2);   // Faz a leitura do sensor a extrema esquerda
  delay(1);
  valSensorEsq1 = analogRead(pinSensorLeft1);   // Faz a leitura do sensor a esquerda
  delay(1);
  valSensorCent = analogRead(pinSensorCenter);  // Faz a leitura do sensor ao centro
  delay(1);
  valSensorDir1 = analogRead(pinSensorRight1);  // Faz a leitura do sensor a direita
  delay(1);
  valSensorDir2 = analogRead(pinSensorRight2);  // Faz a leitura do sensor a extrema direita
  delay(1);

  // Verifica se o robo deve seguir linha
  // se a variavel seguirLinha == 0, o robo permanece parado(velocidades = 0)
  if (seguirLinha == 0) {
    leftSpeed = 0;
    rightSpeed = 0;
  } else {// Caso não, realiza as verificacoes da linha
    verificarLinha();
  }

  //Verifica se o sentido de giro do motor esquerdo eh pra frente ou pra trás
  if (leftSpeed >= 0) {
    motor_left.setSpeed(leftSpeed); // define a vel do motor
    motor_left.run(FORWARD);        // define o sentido de giro para frente.
  } else {
    motor_left.setSpeed(-leftSpeed); // passa o valor leftSpeed pra positvo, e define a vel do motor
    motor_left.run(BACKWARD);        // define o sentido de giro para tras
  }

  //Verifica se o sentido de giro do motor direito eh pra frente ou pra tras
  if (rightSpeed >= 0) {
    motor_right.setSpeed(rightSpeed); // define a vel do motor
    motor_right.run(FORWARD);         // define o sentido de giro para frente.
  } else {
    motor_right.setSpeed(-rightSpeed); // passa o valor rightSpeed pra positvo, e define a vel do motor
    motor_right.run(BACKWARD);         // define o sentido de giro para tras
  }

  // Aguarda 15ms
  delay(15);
}

// Funcao que realiza as verifcacoes da posicao do AGV e define a vel determinada para cada motor
void verificarLinha() {
  // Segue reto (apenas o sensor do centro em cima da linha)
  if (valSensorEsq2 <= linhaEsq2 && valSensorEsq1 <= linhaEsq1 && valSensorCent >= linhaCent && valSensorDir1 <= linhaDir1 && valSensorDir2 <= linhaDir2) {
    leftSpeed = speedEsqFrente;
    rightSpeed = speedDirFrente;
  }

  // Vira para esquerda, nivel 1 (apenas o sensor do centro sobre da linha o da direita)
  else if (valSensorEsq2 <= linhaEsq2 && valSensorEsq1 <= linhaEsq1 && valSensorCent >= linhaCent && valSensorDir1 >= linhaDir1 && valSensorDir2 <= linhaDir2) {
    leftSpeed = speedEsqCurvaEsq1;
    rightSpeed = speedDirCurvaEsq1;
  }
  // vira para esquerda, nivel 2 (apenas o sensor da direita sobre a linha)
  else if (valSensorEsq2 <= linhaEsq2 && valSensorEsq1 <= linhaEsq1 && valSensorCent <= linhaCent && valSensorDir1 >= linhaDir1 && valSensorDir2 <= linhaDir2) {
    leftSpeed = speedEsqCurvaEsq2;
    rightSpeed = speedDirCurvaEsq2;
  }
  // vira para esquerda, nivel 3 (apenas o sensor da direita sobre a linha e o da extrema direita)
  else if (valSensorEsq2 <= linhaEsq2 && valSensorEsq1 <= linhaEsq1 && valSensorCent <= linhaCent && valSensorDir1 >= linhaDir1 && valSensorDir2 >= linhaDir2) {
    leftSpeed = speedEsqCurvaEsq3;
    rightSpeed = speedDirCurvaEsq3;
  }
  // vira para esquerda, nivel 4 (apenas o sensor da extrema direita sobre a linha)
  else if (valSensorEsq2 <= linhaEsq2 && valSensorEsq1 <= linhaEsq1 && valSensorCent <= linhaCent && valSensorDir1 <= linhaDir1 && valSensorDir2 >= linhaDir2) {
    leftSpeed = speedEsqCurvaEsq4;
    rightSpeed = speedDirCurvaEsq4;
  }


  // Vira para direita, nivel 1 (apenas o sensor da esquerda e do centro sobre a linha)
  else if (valSensorEsq2 <= linhaEsq2 && valSensorEsq1 >= linhaEsq1 && valSensorCent >= linhaCent && valSensorDir1 <= linhaDir1 && valSensorDir2 <= linhaDir2) {
    leftSpeed = speedEsqCurvaDir1;
    rightSpeed = speedDirCurvaDir1;
  }
  // vira para direita, nivel 2 (apenas o sensor da esquerda sobre a linha)
  else if (valSensorEsq2 <= linhaEsq2 && valSensorEsq1 >= linhaEsq1 && valSensorCent <= linhaCent && valSensorDir1 <= linhaDir1 && valSensorDir2 <= linhaDir2) {
    leftSpeed = speedEsqCurvaDir2;
    rightSpeed = speedDirCurvaDir2;
  }
  // vira para direita, nivel 3 (apenas o sensor da extrema esquerda e da esquerda sobre a linha)
  else if (valSensorEsq2 >= linhaEsq2 && valSensorEsq1 >= linhaEsq1 && valSensorCent <= linhaCent && valSensorDir1 <= linhaDir1 && valSensorDir2 <= linhaDir2) {
    leftSpeed = speedEsqCurvaDir3;
    rightSpeed = speedDirCurvaDir3;
  }
  // vira para direita, nivel 4 (apenas o sensor da extrema esquerda sobre a linha)
  else if (valSensorEsq2 >= linhaEsq2 && valSensorEsq1 <= linhaEsq1 && valSensorCent <= linhaCent && valSensorDir1 <= linhaDir1 && valSensorDir2 <= linhaDir2) {
    leftSpeed = speedEsqCurvaDir4;
    rightSpeed = speedDirCurvaDir4;
  }

  //Verifica se esta em cima da linha perpendicular (Os cinco em cima da linha )
  // se estiver em cima da linha perpendicular, define 0 para a variavel seguirLinha
  // assim o AGV permanecera parado ate que ocorra um reset
  else if (valSensorEsq2 >= linhaEsq2 && valSensorEsq1 >= linhaEsq1 && valSensorCent >= linhaCent && valSensorDir1 >= linhaDir1 && valSensorDir2 >= linhaDir2){
    seguirLinha = 0;
  }

}
