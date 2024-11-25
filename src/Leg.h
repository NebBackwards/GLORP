#include <Arduino.h>
#include <Servo.h>
#include <Motor.h>
class Leg
{
    private:
    Servo hipJoint;
    Servo kneeJoint;
    Motor wheelMotor;

    public:
    void servo_js();
    void ik();
    void runTrajectory();

};