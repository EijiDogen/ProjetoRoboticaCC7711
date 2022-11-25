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
3. Se há um obstáculo na frente pelos sensores frontais, o robô gira para esquerda até não haver um obstáculo em frente
4. Verifica se o robô está em caminho para colidir com uma parede pelo sensor diagonal, se sim, anda curvado para esquerda.
5. Se há uma parede à direita, e o caminho em frente está livre, o robô segue em frente
6. Se o robô não detecta uma parede à direita, ou ele está se afastando da parede, ou a parede/obstáculo acabou, ele anda curvando para direita. Também há um contador que verifica quantas vezes seguidas esse comando foi realizado. Caso ultrapasse 100 vezes seguidas, entende-se que está andando em círculos, e volta para o estado inicial onde ele procura parede andando reto.
