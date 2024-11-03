#include <Arduino.h>
#include <FunctionalInterrupt.h>

class HC_SR04{
    private:
        int echoPin;
        int trigPin;
        uint32_t lastPing = 0;
        uint32_t pingInterval = 10;
        float distance;
        volatile uint32_t pingStart;
        volatile uint32_t pingEnd;
        enum state{
            ECHO_RECD,
            ECHO_WAIT,
        };

    public:
        HC_SR04(int echo, int trig);
        void init(void(*isr)(void));
        /**
         *distance: pass by refrence a value to hold distance 
         *returns true when a reading is available
         *must be called continuously in loop
        */
        bool getDistance (float& distance);
        void IRAM_ATTR echoISR();
        state State = ECHO_WAIT;
        int checkEcho(void);
        void sendPing(void);
};