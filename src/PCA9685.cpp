#include <stdio.h>
#include <Wire.h>
#include <stdint.h>
#include <PCA9685.h>
#include <Arduino.h>


PCA9685::PCA9685(uint8_t address)
{
    i2c_address = address;
    oscClock = 25000000; //25MHz internal oscillator clock
    Wire.begin(); 
    return;
}

void PCA9685::init(){

    setFrequency(200);
}
void PCA9685::setFrequency(int freq){ //set frequency of control signal in Hz

    int prescale_value = round(oscClock/(4096*freq)) - 1;
    writeReg(PRE_SCALE, prescale_value);
    frequency = freq;
    return;
}

void PCA9685::writeReg(uint8_t reg, uint8_t value)
{
    Wire.beginTransmission(i2c_address);
    Wire.write(reg);
    Wire.write(value);
    last_status = Wire.endTransmission();
}

uint8_t PCA9685::getServoReg(int servoNum){ //returns register address of SERVOn_ON_L

    return SERVO0_ON_L + servoNum*4; //4 addresses per servo

}

void PCA9685::servoWriteMicros(int micros, int servoNum)
{
    float microsPerCycle = (1000000/frequency);
    float microsPerBit = microsPerCycle/4096;
    int bitsOn = micros/(int)microsPerBit;
    uint16_t onTime = 0; //arbitrary, so long as onTime + bitsOn < 4095
    uint16_t offTime = onTime + bitsOn;
    //Following values are shifted & masked because onTime & offTime, 12 bit numbers, are each stored in 2 8-bit registers
    //SERVOn_ON_L stores 8 LSB of onTime in all 8 of its bits, SERVOn_ON_H stores 4 MSB of onTime in its 4 LSB
    //Same logic governs offTime & SERVOn_OFF
    uint8_t writeVals[4];
    writeVals[0] = onTime & 0xFF; //SERVOn_ON_L
    writeVals[1] = (onTime & 0xF00)>>8; //SERVOn_ON_H
    writeVals[2] = offTime & 0xFF; //SERVOn_OFF_L
    writeVals[3] = (offTime & 0xF00)>>8; //SERVOn_OFF_H
    
    int SERVOn_ON_L = getServoReg(servoNum);
    for(int i=0;i<4;i++){
        writeReg(SERVOn_ON_L+i, writeVals[i]);
        Serial.println(writeVals[i]);
    }
    return;
}

void PCA9685::setAngle(float angle, int servoNum){
    
}