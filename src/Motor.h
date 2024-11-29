#include <stdint.h>
#include <Arduino.h>

class Motor{
    private:
        int in1;
        int in2;
        int channel;
        uint8_t resolution = 12;
        int frequency = 200;
        int max_speed = 4095;
        int min_speed = -4095;
        int current_speed = 0;
        enum PINS{IN_1,IN_2};
        PINS attachedPin;
    public:
        Motor(int pin1, int pin2, int channel);
        void init();
        void setSpeed(int speed);
        void attach(int pin);
        void control_update(void);
};