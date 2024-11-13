#include <lib/PID.h>
#include <Arduino.h>

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
    double iEffort = constrain(iEffort + kI * error * (currTime - prevTime), 0, 5);
    double dEffort = kD * (error / (currTime - prevTime));

    return pEffort + iEffort + dEffort;
}