#include <Arduino.h>
#include <math.h>


class Servo
{
private:
int gpioPin;
int servoChannel;
int frequency = 200;
bool attached;
int max_write = 2500;
int min_write = 500;
int resolution = 12;
public:
Servo(int pinNum, int channel);
Servo(int pinNum, int channel, int min, int max);
void init();
void setFrequency(int freq);
void setResolution(int res);
void setAngle(float angle);
void writeMicros(int micros);
void setMaxWrite(int max);
void setMinWrite(int min);
void attach(void);
void detach(void);
};