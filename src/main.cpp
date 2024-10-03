#include <Arduino.h>
#include <PCA9685.h>
#include <Wire.h>
// put function declarations here:
PCA9685 servoDriver = PCA9685(0x40);


void setup() {
  Serial.begin(9600);
  Wire.begin();
  servoDriver.init();
  
}

void loop() {
  servoDriver.servoWriteMicros(700,0);
  Serial.println("hello");
}

