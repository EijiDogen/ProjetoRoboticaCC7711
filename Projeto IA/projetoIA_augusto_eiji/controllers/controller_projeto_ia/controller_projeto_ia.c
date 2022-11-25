#include <stdio.h>
#include <webots/robot.h>
#include <webots/motor.h>
#include <webots/distance_sensor.h>
#include <webots/led.h>

#define TIME_STEP 128
#define QtddSensoresProx 8
#define QtddLeds 10
#define dist_normal 80
#define dist_prox 200

int main(int argc, char **argv) {
  int i=0;
  char texto[256];
  double Sensor[QtddSensoresProx];
  double AceleradorDireito=1.0, AceleradorEsquerdo=1.0;
  int estado=0, count = 0;
  bool front_wall, right_wall, right_close;

  for(i=0;i<256;i++) texto[i]='0';
  wb_robot_init();

  //configurei MOTORES
  WbDeviceTag MotorEsquerdo, MotorDireito;
  MotorEsquerdo = wb_robot_get_device("left wheel motor");
  MotorDireito = wb_robot_get_device("right wheel motor");
  wb_motor_set_position(MotorEsquerdo, INFINITY);
  wb_motor_set_position(MotorDireito, INFINITY);
  wb_motor_set_velocity(MotorEsquerdo,0);
  wb_motor_set_velocity(MotorDireito,0);

   //configurei Sensores de Proximidade
   WbDeviceTag SensorProx[QtddSensoresProx];

   SensorProx[0] = wb_robot_get_device("ps0");
   SensorProx[1] = wb_robot_get_device("ps1");
   SensorProx[2] = wb_robot_get_device("ps2");
   SensorProx[3] = wb_robot_get_device("ps3");
   SensorProx[4] = wb_robot_get_device("ps4");
   SensorProx[5] = wb_robot_get_device("ps5");
   SensorProx[6] = wb_robot_get_device("ps6");
   SensorProx[7] = wb_robot_get_device("ps7");

   wb_distance_sensor_enable(SensorProx[0],TIME_STEP);
   wb_distance_sensor_enable(SensorProx[1],TIME_STEP);
   wb_distance_sensor_enable(SensorProx[2],TIME_STEP);
   wb_distance_sensor_enable(SensorProx[3],TIME_STEP);
   wb_distance_sensor_enable(SensorProx[4],TIME_STEP);
   wb_distance_sensor_enable(SensorProx[5],TIME_STEP);
   wb_distance_sensor_enable(SensorProx[6],TIME_STEP);
   wb_distance_sensor_enable(SensorProx[7],TIME_STEP);

    //config leds
    WbDeviceTag Leds[QtddLeds];
    Leds[0] = wb_robot_get_device("led0");
    wb_led_set(Leds[0],-1);

  // Main loop
  while (wb_robot_step(TIME_STEP) != -1) {

    for(i=0;i<256;i++) texto[i]=0;

    // Processar dados dos sensores
    for(i=0;i<QtddSensoresProx;i++){
       Sensor[i]= wb_distance_sensor_get_value(SensorProx[i]);
       sprintf(texto,"%s|%d: %5.2f  ",texto,i,Sensor[i]);
    }
    
    right_wall = Sensor[2] > 100;
    right_close = Sensor[1] > 100;
    
    front_wall = Sensor[0] > 100 || Sensor[7] > 100;

    printf("%s\n",texto);
    wb_led_set(Leds[0], wb_led_get(Leds[0])*-1);

     // Logica
     
     // Estado inicial (Andar para frente ate encontrar parede)
     if (estado == 0){
       AceleradorEsquerdo = 1.0;
       AceleradorDireito = 1.0;
       if (front_wall || right_wall || right_close){
         estado = 1;
       }
     }
     
     if (estado == 1){  // Caso tenha encontrado uma parede
       if(front_wall){
         count = 0;
         AceleradorEsquerdo = -0.3;
         AceleradorDireito = 0.3;
     
       }else{
       
         if (right_wall){
           count = 0;
           AceleradorEsquerdo = 1.0;
           AceleradorDireito = 1.0;
 
         }else{
           AceleradorEsquerdo = 1.0;
           AceleradorDireito = 0.15;
           count += 1;
         }
         
         if (right_close){
           count = 0;
           AceleradorEsquerdo = 0.15;
           AceleradorDireito = 1.0;
         }
       }
       
       // Caso o robo esteja andando em circulos por muito tempo, ele
       // comeca a andar so para frente ate encontrar uma parede
       if (count > 100){
         count = 0;
         estado = 0;
       }
     }
     
    wb_motor_set_velocity(MotorEsquerdo,(6.28*AceleradorEsquerdo));
    wb_motor_set_velocity(MotorDireito, (6.28*AceleradorDireito));
    
  };

  wb_robot_cleanup();

  return 0;
}