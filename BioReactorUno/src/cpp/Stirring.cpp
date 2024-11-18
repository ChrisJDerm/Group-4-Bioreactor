#include <lib/Stirring.h>
#include <Arduino.h>

Stirring::Stirring(int pwmPin, int encoderPin, double kP, double kI, double kD, void (*IR)(void))
{
    Subsystem(kP, kI, kD);
    pinMode(encoderPin, INPUT);
    pinMode(pwmPin, OUTPUT);
    attachInterrupt(digitalPinToInterrupt(encoderPin), IR, RISING);
}

void Stirring::loop(double currTime, double prevTime, double frequency){
    setPoint = 23; //to be changed
    currVal = frequency;
    double effort = controller.loop(setPoint, currVal, currTime, prevTime);
    if (effort < 0){
        analogWrite(outPin, 0);
    }
    else {
        analogWrite(outPin, effort*(255/5));
    }
}