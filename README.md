# ProjetoRoboticaCC7711

Integrantes:<br>
Augusto Farina RA: 22.219.020-9<br>
Eiji Dogen RA: 22.219.027-4

Link para vídeo de demonstração:
https://youtu.be/WRSzoT3GLi8 


Considerações:<br>
Foi utilizado o mundo: CC7711_testes_II.wbt<br>
A rotação inicial do robô foi alterada para ele olhar uma parede válida.

Funcionamento do robô:
1. Robô inicia em estado inicial de “Procura de parede”. Ele anda para frente até um dos sensores detectar algo.
2. Quando um dos sensores detectar algo, o robô tenta acompanhar a parede pela direita.
3. Se há um obstáculo na frente, o robô gira para esquerda até não haver um obstáculo em frente
4. Se há uma parede à direita, e o caminho em frente está livre, o robô segue em frente
5. Se o robô não detecta uma parede à direita, ou ele está se afastando da parede, ou a parede/obstáculo acabou e ele precisa curvar para direita.
6. Caso o robô continue andando curvando para direita sem encontrar um outro obstáculo, ele andará em círculos. Em casos assim, um contador identifica que o robô está em loop e o coloca no estado inicial, forçando ele a andar em frente.
