#pragma once
#include <lib/PID.h>

class Subsystem {

    public:

    Subsystem();

    Subsystem(float kP, float kI, float kD);

    PID* getController(){
        return &controller;
    }

    protected:
    double setpoint;
    double currVal;

    PID controller;
};