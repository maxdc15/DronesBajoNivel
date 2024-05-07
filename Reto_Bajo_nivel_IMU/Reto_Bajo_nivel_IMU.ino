/*Programa para leer los datos de un IMU (MPU6050) con interfaz I2C y enviar la información en un string mediante comunicación UART

  Ecudería de Robótica del CEM - Equipo de Drones

  Autores: Bruno Sánchez García        - A01378960 - MN-A
           Maximiliano De La Cruz Lima - A01798048 - IRS
           Ricardo Medina Nolasco      - A01745656 - IRS
  Versión 1.0 - 29/04/2024
*/

#include <I2Cdev.h>
#include <MPU6050.h>
#include <Wire.h>

MPU6050 sensor;

int ax, ay, az;
int gx, gy, gz;

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);    // Cambiado para coincidir con la velocidad del receptor
  Wire.begin();          
  sensor.initialize();

  if (sensor.testConnection()) Serial.println("Sensor iniciado correctamente");
  else Serial.println("Error al iniciar el sensor");
}

void loop() {
   sensor.getAcceleration(&ax, &ay, &az);
  sensor.getRotation(&gx, &gy, &gz);
  float ax_m_s2 = ax * (9.81/16384.0);
  float ay_m_s2 = ay * (9.81/16384.0);
  float az_m_s2 = az * (9.81/16384.0);
  float gx_deg_s = gx * (250.0/32768.0);
  float gy_deg_s = gy * (250.0/32768.0);
  float gz_deg_s = gz * (250.0/32768.0);

  // Formatear los datos como una cadena delimitada por dos puntos
  String dataString = String(ax_m_s2, 2) + ":" + String(ay_m_s2, 2) + ":" + String(az_m_s2, 2) + ":" +
                      String(gx_deg_s, 2) + ":" + String(gy_deg_s, 2) + ":" + String(gz_deg_s, 2);

  Serial.println(dataString);
  Serial1.println(dataString);  // Enviar la cadena formateada al otro Arduino

  delay(2000); // Ajustar según sea necesario para la velocidad de transmisión deseada
}

