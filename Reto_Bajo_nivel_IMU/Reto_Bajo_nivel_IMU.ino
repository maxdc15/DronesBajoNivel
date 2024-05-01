/*Programa para leer los datos de un IMU (MPU6050) con interfaz I2C y enviar la información en un string mediante comunicación UART

  Ecudería de Robótica del CEM - Equipo de Drones

  Autores: Bruno Sánchez García        - A01378960 - MN-A
           Maximiliano De La Cruz Lima - A01798048 - IRS
           Ricardo Medina Nolasco      - A01745656 - IRS
  Versión 1.0 - 29/04/2024
*/

//Inclusión de librerías 
#include <Wire.h>  

#include "MPU6050.h"
//Inicialización comunicación I2C para IMU
//MPU6050 name(dirección de dispsitivo)
MPU6050 accelgyro(0X68); //0x68 es la dirección estándar para este dispositivo

 //declare variables
 float ax, ay, az;
 float gx, gy, gz;
 float temp;
 float temp_MPU;

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
