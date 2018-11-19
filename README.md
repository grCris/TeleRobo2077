# TeleRobo2077
Projeto em grupo de um AGV(Automated Guided Vehicle) seguidor de linha.

## Sobre
### O projeto ainda está em desenvolvimento, mas a proposta de funcionamento final é a seguinte:  

O AGV seguidor de linha sairá de um ponto A e irá até um ponto B. Durante o percurso, nosso robô encontrará uma faixa perpendicular na qual ele reconhece e para. É colocado um objeto nele, aciona-se uma entrada onde a carga é detectada, o AGV aguarda um determinado tempo e segue o percurso. Ele irá encontrar uma outra faixa, onde o robô para novamente e assim é removido o objeto que foi posto. O AGV detecta que a carga foi retirada e volta a condição inicial do projeto, podendo assim iniciar o processo novamente.

### Detalhes do estado atual do projeto:
  - O controlador é um BlackBoard Uno R3;
  - O driver dos motores DC, é um shield Motor L293D (baseado no AdaFruit Motor Shield V1.2);
  - O circuito é construído em uma base branca com fita isolante preta sendo o circuito;
  - Para a detecção da linha, são utilizados 5 sensores óptico reflexivo TCRT500;
  - No modo atual o AGV está percorrendo o circuito de forma satisfatória;
  - Ele detecta a linha perpendicular a do circuito e para.
  
### Implementações futuras:
  - Parte do código para detectar a carga;
  - Sequência de funcionamento como é descrito na proposta final.
  
