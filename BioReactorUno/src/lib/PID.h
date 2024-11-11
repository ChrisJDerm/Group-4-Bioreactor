#pragma once

class PID {

    PID();
    
    PID(double kP, double kI, double kD);

    double loop(double setpoint, double curVal, double prevTime, double currTime);

    private:

    double kP;
    double kI;
    double kD;

    double prevVal;
    double prevPrevVal;

    double integral;

    bool prevSign;

};