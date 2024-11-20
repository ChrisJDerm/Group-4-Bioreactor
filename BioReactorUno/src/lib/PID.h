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

    double prevError = 0;
    double prevPrevError = 0;
    double prePrevPrevError = 0;

    double prevPrevTime = 0;
    double prevPrevPrevTime = 0;

    double integral;

    bool prevSign;

};