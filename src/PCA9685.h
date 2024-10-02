#include <stdint.h>
#include <Wire.h>
#include <stdio.h>

class PCA9685
{
private:
    uint8_t i2c_address;
    uint8_t last_status;
public:
    PCA9685(uint8_t address);
    void servoSetFreq(int freq, int pin);
    void writeReg(uint8_t reg, uint8_t value);
    uint8_t getServoReg(uint8_t servoNum);
    void servoWriteMicros(int mircos, int servoNum);
    void setAngle(float angle, int servoNum);
};