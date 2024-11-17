#include <lib/Heating.h>
#include <Arduino.h>

void Heating::setup(int inPin, int outPin){
    pinMode(inPin, INPUT);
    pinMode(outPin, OUTPUT);
}

double Heating::getTemp(){
    return analogRead(inPin);
}

void Heating::loop(double currTime, double prevTime){
    setPoint = 23; //to be changed
    currVal = getTemp();
    double effort = controller.loop(setPoint, currVal, currTime, prevTime);
    if (effort < 0){
        analogWrite(outPin, 0);
    }
    else {
        analogWrite(outPin, effort*(255/5));
    }
}

