#include<Arduino.h>


class SharpIR
{
private:
int adcPin;
uint32_t last_read_time = 0;
uint32_t read_interval = 40;
public:
SharpIR(int adc);
bool getDistance(float& distance);
virtual void init(void) {pinMode(adcPin, INPUT);}
};