# TeleRobo2077
Projeto em grupo de um AGV(Automated Guided Vehicle) seguidor de linha.

## Sobre
### O projeto ainda está em desenvolvimento, mas a proposta de funcionamento final é a seguinte:  

O AGV seguidor de linha sairá de um ponto A e irá até um ponto B. Durante o percurso, nosso robô encontrará uma faixa perpendicular na qual ele reconhece e para. É colocado um objeto nele, aciona-se uma entrada onde a carga é detectada, o AGV aguarda um determinado tempo e segue o percurso. Ele irá encontrar uma outra faixa, onde o robô para novamente e assim é removido o objeto que foi posto. O AGV detecta que a carga foi retirada e volta a condição inicial do projeto, podendo assim iniciar o processo novamente.

### Detalhes do estado atual do projeto:
  - O controlador é um Uno BlackBoard R3(mas pode ser utilizado um arduino comum);
  - O driver dos motores DC, é um shield Motor L293D (baseado no AdaFruit Motor Shield V1.2);
  - O circuito é construido em uma base branca com fita isolante preta sendo o circuito;
  - Para a detecção da linha, são utilizados sensores 5 óptico reflexivo TCRT500;
  - No modo atual o AGV está percorrendo o circuito de forma satisfatoria;
  - Ele detecta a linha perpendicular para.
  
### Implementações futuras:
  - Parte do código para detectar a carga;
  - Seguencia de funcionamento como é descrito na proposta final.
  
