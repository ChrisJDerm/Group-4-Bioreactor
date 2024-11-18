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

double PID::loop(double setpoint, double currVal, double prevTime, double currTime){
    int error = setpoint - currVal;

    pEffort = kP * error;
    iEffort = constrain(iEffort + kI * error * (currTime - prevTime), 0, 5);
    dEffort = kD * (error / (currTime - prevTime));

    return constrain(pEffort + iEffort + dEffort, 0, 5);
}