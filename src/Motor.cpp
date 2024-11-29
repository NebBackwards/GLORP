#include <Motor.h>

Motor::Motor(int pin1, int pin2, int pwm_channel){
    in1 = pin1;
    in2 = pin2;
    channel = pwm_channel;
    ledcSetup(channel, frequency, resolution);
}

void Motor::setSpeed(int speed){
    bool in_range = (speed <= max_speed) && (speed >= min_speed);
    try
    {
        if (!in_range){
            throw(speed);
        }else{
            current_speed = abs(speed);
            if (speed >= 0){
                attach(in1);
            }else{
                attach(in2);
            }
        }
    }catch(int speed_OOR){
        Serial.println("Speed input is out of range");
        Serial.println("Speed input: " + speed_OOR);
    }
}

void Motor::attach(int pin){
    try{
    if(pin == in1){
        attachedPin = IN_1;
        ledcDetachPin(in2);
        ledcAttachPin(pin, channel);
    }
    else if (pin == in2){
        attachedPin = IN_2;
        ledcDetachPin(in1);
        ledcAttachPin(pin, channel);
    }
    else {throw(pin);}
    }
    catch(int unused_pin){
        Serial.println("attempted to attach GPIO pin not used by motor class");
        Serial.println("Pin: " + unused_pin);}
}


void Motor::control_update(void){
    ledcWrite(channel, current_speed);
}