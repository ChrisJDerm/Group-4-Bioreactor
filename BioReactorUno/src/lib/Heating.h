#pragma once
#include <lib/Subsystem.h>

class Heating : Subsystem {
    public:
    Heating(int inPin, int outPin, double kP, double kI, double kD);
    double getTemp();
    void loop(double currTime, double prevTime, int setPoint);

    private:

    int inPin;
    int outPin;
    double setPoint; //write a makeSetPoint function
    double currVal;
};