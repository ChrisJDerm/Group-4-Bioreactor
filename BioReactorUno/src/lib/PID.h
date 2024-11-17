#pragma once

class PID {
    public:

    PID();
    
    PID(double kP, double kI, double kD);

    double loop(double setpoint, double currVal, double prevTime, double currTime);

    private:

    double kP;
    double kI;
    double kD;

    double pEffort;
    double iEffort;
    double dEffort;

    double prevVal;
    double prevPrevVal;

    double integral;

    bool prevSign;

};