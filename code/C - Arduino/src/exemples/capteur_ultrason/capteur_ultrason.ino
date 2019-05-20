#include "OF_capteur_ultrason.h"

Ultrasonic ultrasonic(10);
void setup()
{
  Serial.begin(9600);
}

void loop()
{
  long RangeInCentimeters;

  RangeInCentimeters = ultrasonic.MeasureInCentimeters();
  Serial.print(RangeInCentimeters);
  Serial.println(" cm");
  delay(250);
}
