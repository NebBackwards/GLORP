#include <stdint.h>
#include <Arduino.h>

class Motor{
    private:
        int in1;
        int in2;
    public:
        Motor(int pin1, int pin2);
        void init();
        void setSpeed(int speed);

};