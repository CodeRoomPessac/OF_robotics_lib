
// On choisit la pin sur laquelle
// le capteur est branché
#include <Wire.h>
#include "OF_capteur_couleur.h"
#include "OF_rgb_lcd.h"

Adafruit_TCS34725 color_sensor = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
byte gammatable[256];
rgb_lcd lcd;

void setup()
{
    Serial.begin(9600);
    lcd.begin(16, 2);
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
    lcd.print("Distance : 13cm");

    uint16_t clear, red, green, blue;
        
    //delay(60);  // takes 50ms to read 
    color_sensor.getRawData(&red, &green, &blue, &clear);
    //Serial.print("Clear : ");Serial.print(int(clear));Serial.print(" | R : ");Serial.print((int)red);Serial.print(" | G : "); Serial.print((int)green);Serial.print(" | B : "); Serial.println((int)blue);
    // Figure out some basic hex code for visualization
    uint32_t sum = clear;
    float r, g, b;
    r = red; r /= sum;
    g = green; g /= sum;
    b = blue; b /= sum;
    r *= 256; g *= 256; b *= 256;

    
    //Serial.print("R : ");Serial.print((int)r);Serial.print(" | G : "); Serial.print((int)g);Serial.print(" | B : "); Serial.println((int)b);
    Serial.print("R : ");Serial.print(gammatable[(int)r]);Serial.print(" | G : "); Serial.print(gammatable[(int)g]);Serial.print(" | B : "); Serial.println(gammatable[(int)b]);
    Serial.print("RFUNC : ");Serial.print(color_sensor.RedValue(gammatable));Serial.print(" | GFUNC : "); Serial.print(color_sensor.GreenValue(gammatable));Serial.print(" | BFUNC : "); Serial.println(color_sensor.BlueValue(gammatable));
    //lcd.setRGB(gammatable[(int)r], gammatable[(int)g], gammatable[(int)b]);
    lcd.setRGB(color_sensor.RedValue(gammatable),color_sensor.GreenValue(gammatable),color_sensor.BlueValue(gammatable));
    lcd.clear();
    /*Serial.print("C:\t"); Serial.println(clear);
    Serial.print("\tR:\t"); Serial.println(red);
    Serial.print("\tG:\t"); Serial.println(green);
    Serial.print("\tB:\t"); Serial.println(blue);*/

    delay(100);
}
