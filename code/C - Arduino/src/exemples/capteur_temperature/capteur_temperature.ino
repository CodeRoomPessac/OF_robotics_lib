
#include "OF_capteur_temperature.h"

Temp_sensor TempSensor;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // initialize serial communications at 9600 bps
  TempSensor.setup(A0,A1);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("Temp Environnante : ");
  Serial.print(TempSensor.measureSurTemp());//measure the Surrounding temperature around the sensor
  Serial.print(" | Temp Objet : ");
  Serial.println(TempSensor.measureObjectTemp());
}
