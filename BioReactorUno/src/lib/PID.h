#pragma once

class PID {
    public:

    PID();
    
    PID(double kP, double kI, double kD);

    double loop(double setpoint, double currVal, double prevTime, double currTime);

    double kP;
    double kI;
    double kD;

    double pEffort = 0;
    double iEffort = 0;
    double dEffort = 0;

    double prevVal;
    double prevError;

    double integral;

    bool prevSign;

};