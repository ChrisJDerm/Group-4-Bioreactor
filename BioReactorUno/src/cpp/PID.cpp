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

double PID::loop(double setpoint, double currVal, double currTime, double prevTime){
    double error = setpoint - currVal;

    pEffort = kP * error;

    if (((prevError - setpoint) * (error)) < 0)
    {
        iEffort = 0;
    }

    iEffort = constrain(iEffort + (kI * error * ((currTime - prevTime)/1000000)), 0, 1300);
    dEffort = kD * ((error-prevError)/(currTime-prevTime));
    prevError = error;

    return constrain(pEffort + iEffort + dEffort, -5, 5);
}