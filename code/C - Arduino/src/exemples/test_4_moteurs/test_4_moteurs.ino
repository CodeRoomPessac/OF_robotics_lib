#include <Wire.h>
#include "moteur.h"

// default I2C address is 0x0f
#define ADDRESS_1 0x0f
#define ADDRESS_2 0x07

I2CMotorDriver M1;
I2CMotorDriver M2;

void setup() {
  M1.begin(ADDRESS_1); 
  M2.begin(ADDRESS_2);
  pinMode(8,INPUT);
}

void loop() {
  // Set the speed of a motor, speed is equal to duty cycle here
  while(!(digitalRead(8)==1)){}
  M1.speed(MOTOR1, 100);
  M1.speed(MOTOR2, 100);
  M2.speed(MOTOR1, 100);
  M2.speed(MOTOR2, 100);
}
