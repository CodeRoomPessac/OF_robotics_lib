#include <Wire.h>
#include "OF_moteur.h"

// default I2C address is 0x0f
#define I2C_ADDRESS 0x0f

void setup() {
  Motor.begin(I2C_ADDRESS); 
}

void loop() {
  // Set the speed of a motor, speed is equal to duty cycle here
  Motor.stop(MOTOR2);
  Motor.speed(MOTOR1, 100);
  delay(1000);
  // Stop one motor
  Motor.stop(MOTOR1);
  Motor.speed(MOTOR2, 100);
  delay(1000);

}
