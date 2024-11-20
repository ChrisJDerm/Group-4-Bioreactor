#include <lib/pH.h>
#include <Arduino.h>

pH::pH(int inPin, int outPin, double kP, double kI, double kD){
    Subsystem(kP, kI, kD);
    pinMode(inPin, INPUT);
    pinMode(outPin, OUTPUT);
}

double pH::get_pH(){
    return analogRead(inPin);
}

void pH::loop(double currTime, double prevTime){
    setPoint = 7; //to be changed
    currVal = get_pH();
    double effort = controller.loop(setPoint, currVal, currTime, prevTime);
    if (effort < 0){
        analogWrite(outPin, 0);
    }
    else {
        analogWrite(outPin, effort*(255/5));
    }
}
