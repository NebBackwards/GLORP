#include <stdint.h>
#include <Wire.h>
#include <stdio.h>
#define PRE_SCALE 0xFE
#define SERVO0_ON_L 0x06

class PCA9685
{
private:
    uint8_t i2c_address;
    uint8_t last_status;
    int oscClock;
    int frequency;
public:
    PCA9685(uint8_t address);
    void init();
    void setFrequency(int freq);
    void writeReg(uint8_t reg, uint8_t value);
    uint8_t getServoReg(int servoNum);
    void servoWriteMicros(int micros, int servoNum);
    void setAngle(float angle, int servoNum);
};