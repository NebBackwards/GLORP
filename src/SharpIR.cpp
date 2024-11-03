#include <SharpIR.h>

SharpIR::SharpIR(int adc){
    adcPin = adc;
    pinMode(adcPin, INPUT);
}

bool SharpIR::getDistance(float& distance){
    bool newReading = false;
    uint32_t currTime = millis();
    if(currTime - last_read_time >= read_interval)
    {
        last_read_time = currTime;

        uint16_t adcResult = analogRead(adcPin);
        float voltage = ((float)adcResult/4096.0)*3.3;
        distance = 19.4/(voltage-0.137);

#ifdef __SHARP_DEBUG__
        Serial.println(distance);
#endif

        newReading = true;
    }

    return newReading;
}