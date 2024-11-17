#pragma once
#include <lib/PID.h>

class Subsystem {

    Subsystem();

    PID* getController(){
        return &controller;
    }

    protected:
    double setpoint;
    double currVal;

    PID controller;
};