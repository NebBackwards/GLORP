#include <Arduino.h>
#include <servo.h>

class Leg
{
    private:
    Servo hipJoint;
    Servo kneeJoint;
    public:
    void servo_js();
    void ik();
    void runTrajectory();

};