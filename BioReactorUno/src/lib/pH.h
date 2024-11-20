#pragma once
#include <lib/Subsystem.h>

class pH : Subsystem {
    public:
    pH(int inPin, int outPin, double kP, double kI, double kD);
    double get_pH();
    void loop(double currTime, double prevTime);

    private:

    int inPin;
    int outPin;
    double setPoint; //write a makeSetPoint function
    double currVal;
};