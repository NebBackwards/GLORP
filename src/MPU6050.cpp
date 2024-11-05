#include <Arduino.h>
#include <MPU6050.h>
#include <Wire.h>

MPU6050::MPU6050(uint8_t i2c_address){
    //defaults to 0x68
    address = i2c_address;
}

uint8_t MPU6050::readReg(regAddr reg)
{
    uint8_t value;

    Wire.beginTransmission(address);
    Wire.write(reg);
    last_status = Wire.endTransmission();
    Wire.requestFrom(address, (uint8_t)1);
    value = Wire.read();
    Wire.endTransmission();

    return value;
}

bool dataAvailStatus(){
   
}

void readAccel(){

}

void readGyro(){

}