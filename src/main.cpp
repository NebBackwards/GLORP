#include <Arduino.h>
#include <PCA9685.h>
#include <Servo.h>
#include <MPU6050.h>
#define __DEBUG_IMU__

//Servo servo1 = Servo(19, 1);
MPU6050 imu = MPU6050(0x68);
float pitchAngle = 0.0;

void setup() {
  Serial.begin(9600);
  //servo1.init();
  imu.init_default();
  imu.setSampleRate(100);
  imu.calibrate(200);
  
}

void loop() {
  if (imu.checkForPitchUpdate(pitchAngle)){
    Serial.println(pitchAngle);
}
}

