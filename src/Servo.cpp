#include <Servo.h>

Servo::Servo(int pinNum, int channel)
{
    gpioPin = pinNum;
    servoChannel = channel;
}
Servo::Servo(int pinNum, int channel, int min, int max){
    gpioPin = pinNum;
    servoChannel = channel;
    min_write = min;
    max_write = max;
}

void Servo::init(){
        ledcSetup(servoChannel, frequency, resolution);
        attach();
}

void Servo::setMaxWrite(int max){
    max_write = max;
}
void Servo::setMinWrite(int min){
    min_write = min;
}

void Servo::setFrequency(int freq){
    frequency = freq;
    ledcSetup(servoChannel, frequency, resolution);
    attach();
}

void Servo::setResolution(int res){
    resolution = res;
    ledcSetup(servoChannel, frequency, resolution);
    attach();
}

void Servo::writeMicros(int micros){
    if(attached){
        float microsPerCycle = (1000000/frequency);
        float microsPerBit = microsPerCycle/(pow(2,resolution));
        int bitsOn = micros/(int)microsPerBit;
        ledcWrite(servoChannel, bitsOn);
    }else{Serial.println("Error in writeMicros: Servo Not Attached!");}
}

void Servo::setAngle(float angle){//sets angle from -135 to 135
    int micros = 1200 + (round(angle*5.9444));
    writeMicros(micros);
}
void Servo::attach(void){
    ledcAttachPin(gpioPin,servoChannel);
    attached = true;
}

void Servo::detach(void){
    ledcDetachPin(gpioPin);
    attached = false;
}