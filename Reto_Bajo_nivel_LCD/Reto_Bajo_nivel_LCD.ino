/*Programa para recibir un string mediante comunicación UART y mostrar su contenido en un display LCD 16x2 con interfaz I2C

  Ecudería de Robótica del CEM - Equipo de Drones

  Autores: Bruno Sánchez García - A01378960 - MN-A
  Versión 1.0 - 25/04/2024
*/

//Inclusión de librerías 
#include <Wire.h>                                        

#include <LiquidCrystal_I2C.h>   
//Inicialización comunicación I2C para LCD 
//LiquidCrystal_I2C name(dirección de dispositivo, numero de columnas, numero de filas)         
LiquidCrystal_I2C lcd(0x27, 16, 2);    //0x27 funciona para los modelos que tienen en el tec, si usan uno diferente, puede variar este, pero en los tutoriales especifican       

String text = "1.11:2.11:3.11:90:180:270"; //Es el mensaje que se recibe por uart desde el otro arduino, es un string que se indexa posteriormente
// El orden es el siguiente Acc_x:Acc_y:Acc_z:Gy_x:Gy_y:Gy_z  (las 3 aceleraciones y las 3 inclinaciones.
float Acx = 9.22;
float Acy = 9.22;
float Acz = 9.22;
int roll = 360;
int pitch = 360;
int yaw = 360;
int str_len = 0;                                          
                                                           //roll  pitch       
int p_pos = 18; //Posición del ":" que separa roll de pitch (90":"180) (Se suma +1 para el corte)
                                                          //pitch yaw
int y_pos = 21; //Posición del ":" que separa pitch de yaw (180":"270) (Se suma +1 para el corte)
// Las Aceleraciones siempre tienen la misma cantidad de caracteres, pero los giros no
//p_y_state alterna entre cuando se buscan los ":" que separan roll de pitch y de yaw, ya que su posición puede cambiar dependiente del valor 
//Ejemplo
// teniendo 1.11:2.11:3.11:90:180:270 los : de roll_pitch estan en la posición 17 y el de pitch_yaw en la posición 22.

//0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 20 21 22 23 24 25
//1 . 1 1 : 2 . 1 1 : 3  .   1  1  :  9  0  :  1  8  0  :  2  7  0 

//pero  teniendo 1.11:2.11:3.11:180:270:15 los espacios cambian a 18 y 23

//0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 20 21 22 23 
//1 . 1 1 : 2 . 1 1 : 3  .   1  1  :  1  8  0  :  2  7  0  :  1  5   

//Por eso es necesario que cada que se recibe el mensaje, se actualizen p_pos y y_pos


int p_y_state = 0; 

void setup()

{
  //Inicialización de la comunicación Serial
  Serial.begin(9600);
  Serial1.begin(9600);

  //Inicialización de la comunicación con el LCD
  lcd.init();                                                        

  Wire.begin();                                               

  //Se prende la luz de fondo del LCD
  lcd.backlight();                                              
}


void splitString(String s, char delimiter, float* values) {
    int i = 0;
    int pos = s.indexOf(delimiter);
    while (pos != -1) {
        values[i++] = s.substring(0, pos).toFloat();
        s = s.substring(pos + 1);
        pos = s.indexOf(delimiter);
    }
    values[i] = s.toFloat(); // Para el último elemento después del último delimitador
}

void loop() {
    if (Serial1.available()) {
        String dataString = Serial1.readStringUntil('\n');
        float values[6]; // ax, ay, az, gx, gy, gz
        splitString(dataString, ':', values);
        
        // Actualizar LCD con valores
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("AccX AccY AccZ");
        lcd.setCursor(0, 1);
        lcd.print(String(values[0], 2) + " " + String(values[1], 2) + " " + String(values[2], 2));
        delay(1500);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("GyrX GyrY GyrZ");
        lcd.setCursor(0, 1);
        lcd.print(String(values[3], 2) + " " + String(values[4], 2) + " " + String(values[5], 2));
        delay(1500);
    }
}
