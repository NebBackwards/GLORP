#include <Arduino.h>
#include <HC_SR04.h>
#include <BindArg.h>

HC_SR04::HC_SR04(int echo, int trig){
    echoPin = echo;
    trigPin = trig;
}

void HC_SR04::init(void (*isr)(void)){
    pinMode(echoPin, INPUT);
    pinMode(trigPin, OUTPUT);
    attachInterrupt(echoPin,isr,CHANGE);
    State = ECHO_WAIT;
}
void IRAM_ATTR HC_SR04::echoISR(){
    if (digitalRead(echoPin)){
        pingStart = micros();
    }else{
        pingEnd = micros();
        State = ECHO_RECD;
    }
}

int HC_SR04::checkEcho(void){
    int echoLength = 0;
    if (State == ECHO_RECD)
    {
        cli();
        echoLength = pingEnd - pingStart;
        State = ECHO_WAIT;
        sei();
    }
    return echoLength;
}

void HC_SR04::sendPing(void)
{
    bool toPing = false;
    if(!digitalRead(echoPin)){ toPing = true;}
    
    if (millis() - lastPing > pingInterval){

        lastPing = millis();
        digitalWrite(trigPin,HIGH);
        delayMicroseconds(30);
        digitalWrite(trigPin,LOW);
        cli();
        pingStart = pingEnd = 0;
        sei();
    }
}

bool HC_SR04::getDistance(float& distance)
{
    int echoLength = checkEcho();
    bool retVal = false;
    if(echoLength){
        distance = echoLength/58.0;
        retVal = true;
    }
    sendPing();
    return retVal;
}


