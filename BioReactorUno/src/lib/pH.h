#pragma once
#include <lib/Subsystem.h>
#include <lib/Constants.h>

class pH : Subsystem {
    public:
    pH(int inPin, int alkaPin, int acidPin, double kP, double kI, double kD);
    float calculateMedian(float arr[], int size);
    void loop(double currTime, double prevTime, double setPoint);
    inline double getpH(){
        return currVal;
    }

    private:

    int inPin;
    int alkaPin;
    int acidPin;
    double setPoint; //write a makeSetPoint function
    double currVal;

    const float neutralV = 0.977; // Voltage at pH 7 (calculated from raw 207)
    const float slope = -0.10516;  // Slope of pH sensor (V/pH)

    float voltageReadings[NUM_READINGS]; // Array to store the readings

    int currentIndex = 0;
};