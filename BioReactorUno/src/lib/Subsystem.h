#pragma once
#include <lib/PID.h>

class Subsystem {

    Subsystem();


    private:
    double setpoint;
    double currVal;

    PID controller;
};