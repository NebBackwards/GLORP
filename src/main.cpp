#include <Arduino.h>
#include <PCA9685.h>
#include <Servo.h>
#include <MPU6050.h>
#include <Motor.h>
#define __DEBUG_IMU__

//Servo servo1 = Servo(19, 1);
MPU6050 imu = MPU6050(0x68);
float pitchAngle = 0.0;
Motor motor = Motor(16,17,1);


hw_timer_t *control_timer = NULL;

void IRAM_ATTR update(){
  motor.control_update();
}

void setup() {
  Serial.begin(9600);
  imu.init_default();
  control_timer = timerBegin(0, 80, true);
  timerAttachInterrupt(control_timer, &update, true);
  timerAlarmWrite(control_timer, 2000, true);
  timerAlarmEnable(control_timer);
}

void loop() {
  if(imu.checkForPitchUpdate(pitchAngle)){
    float x = imu.a.x;
    float y = imu.a.y;
    float z = imu.a.z;
    
    Serial.print(">x:");
    Serial.print(x);
    Serial.print(",");
    Serial.print("y:");
    Serial.print(y);
    Serial.print(",");
    Serial.print("z:");
    Serial.print(z);
    Serial.println();
  }
}

