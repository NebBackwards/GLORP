#include <stdio.h>
#include <Wire.h>
#include <stdint.h>
#include <PCA9685.h>


PCA9685::PCA9685(uint8_t address)
{
    i2c_address = address;
    Wire.begin();
    return;
}

void PCA9685::setClkFreq(int freq, int pin){

    Wire.beginTransmission(i2c_address);
    Wire.write(8);
    return;
}

void PCA9685::writeReg(uint8_t reg, uint8_t value)
{
    Wire.beginTransmission(i2c_address);
    Wire.write(reg);
    Wire.write(value);
    last_status = Wire.endTransmission();
}

uint8_t PCA9685::getServoReg(uint8_t servoNum){ //returns register address for 

    return 6 + servoNum*4;

}
