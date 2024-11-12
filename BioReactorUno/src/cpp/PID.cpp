#include <lib/PID.h>

PID::PID(){
    kP = 0;
    kI = 0;
    kD = 0;
}

PID::PID(double kP, double kI, double kD){
    this->kP = kP;
    this->kI = kI;
    this->kD = kD;
}

double PID::loop(double setpoint, double curVal, double prevTime, double currTime){
    int error = setpoint - curVal;

    double pEffort = kP * error;
    double iEffort = kI * 0; // derivative of error;
    double dEffort = kD * 0; // itegral of error;

    return pEffort + iEffort + dEffort;
}