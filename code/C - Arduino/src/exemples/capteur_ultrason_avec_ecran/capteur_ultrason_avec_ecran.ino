#include <Wire.h>
#include "OF_rgb_lcd.h"
#include "OF_capteur_ultrason.h"

rgb_lcd lcd;
Ultrasonic ultrasonic(10);

const int colorR = 0;
const int colorG = 0;
const int colorB = 127;

void setup() 
{
    // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);
    
    lcd.setRGB(colorR, colorG, colorB);
    
    // Print a message to the LCD.
    //lcd.print("hello, world!");
    lcd.print("Distance : ");
    Serial.begin(9600);

    delay(1000);
}

void loop() 
{
    // set the cursor to column 0, line 1
    // (note: line 1 is the second row, since counting begins with 0):
    lcd.setCursor(11, 0);
    // print the number of seconds since reset:
    //lcd.print(millis()/1000);
    long RangeInCentimeters;

    RangeInCentimeters = ultrasonic.MeasureInCentimeters();
    lcd.print(RangeInCentimeters);
    //Serial.println(RangeInCentimeters);
    lcd.print("cm");

    delay(250);
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
