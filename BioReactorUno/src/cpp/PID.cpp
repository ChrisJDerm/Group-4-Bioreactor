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
    iEffort = constrain(iEffort + (kI * error * ((currTime - prevTime)/1000000)), 0, 10000000);
    if (kD != 0)
    {
        float firstGrad = (prevPrevError - prePrevPrevError) / ((prevPrevTime - prevPrevPrevTime)/1000000);
        float secondGrad = (prevError - prevPrevError) / ((prevTime - prevPrevTime)/1000000);
        float thirdGrad = (error - prevError) / ((currTime - prevTime)/1000000);
        dEffort = kD * ((firstGrad+secondGrad+thirdGrad)/3);
    } else {
        dEffort = 0;
    }
    
    // Serial.println((error - prevError) / ((currTime - prevTime)/1000000));
    prePrevPrevError = prevPrevError;
    prevPrevError = prevError;
    prevError = error;

    prevPrevPrevTime = prevPrevTime;
    prevPrevPrevTime = prevTime;

    return constrain(pEffort + iEffort + dEffort, -5, 5);
}