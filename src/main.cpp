#include <Arduino.h>
#include <PCA9685.h>
#include <servo.h>
// put function declarations here:
Servo servo1 = Servo(19, 1);


void setup() {
  Serial.begin(9600);
  servo1.init();
  
}

void loop() {
  servo1.setAngle(120);
  delay(3000);
  servo1.setAngle(0);
  delay(3000);
  servo1.setAngle(-120);
  delay(3000);

}

