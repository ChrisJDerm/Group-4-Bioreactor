#pragma once
#include <lib/Subsystem.h>

class Stirring : Subsystem {
    public:
    Stirring(int pwmPin, int encoderPin, double kP, double kI, double kD);
    void loop(double currTime, double prevTime, double frequency, int setpoint);

    private:
    float frequency;



    int inPin;
    int outPin;
    double setPoint; //write a makeSetPoint function
    double currVal;
};