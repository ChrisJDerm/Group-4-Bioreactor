#pragma once
#include <lib/Subsystem.h>

class Heating : Subsystem {
    void setup(int inPin, int outPin);
    double getTemp();
    void loop(double currTime, double prevTime);

    private:

    int inPin;
    int outPin;
    double setPoint; //write a makeSetPoint function
    double currVal;
};