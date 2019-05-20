
// On choisit la pin sur laquelle
// le capteur est branché
#include <Wire.h>
#include "OF_capteur_couleur.h"

#define TCAADDR 0x70

void tcaselect(uint8_t i)
{
  if(i>7) return;
  Wire.beginTransmission(TCAADDR);
  Wire.write(1<<i);
  Wire.endTransmission();
}

Adafruit_TCS34725 color_sensor = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
//Adafruit_TCS34725 color_sensor_2 = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
byte gammatable[256];


void setup()
{
    Serial.begin(9600);
 
    tcaselect(2);
    if (color_sensor.begin()) {
    Serial.println("Found sensor");
    } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1); // halt!
    }
    tcaselect(7);
    if (color_sensor.begin()) {
    Serial.println("Found sensor");
    } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1); // halt!
    }

    for (int i=0; i<256; i++) 
    {
      float x = i;
      x /= 255;
      x = pow(x, 2.5);
      x *= 255; 
      gammatable[i] = x;
      //Serial.println(gammatable[i]);
    }
    delay(1000);
}
void loop()
{
  
    tcaselect(2);
    Serial.print("SENSOR 1 : ");Serial.print(color_sensor.RedValue(gammatable));Serial.print(" | GFUNC : "); Serial.print(color_sensor.GreenValue(gammatable));Serial.print(" | BFUNC : "); Serial.println(color_sensor.BlueValue(gammatable));

    tcaselect(7);
    Serial.print("SENSOR 2 : ");Serial.print(color_sensor.RedValue(gammatable));Serial.print(" | GFUNC : "); Serial.print(color_sensor.GreenValue(gammatable));Serial.print(" | BFUNC : "); Serial.println(color_sensor.BlueValue(gammatable));

    
    delay(100);
}
