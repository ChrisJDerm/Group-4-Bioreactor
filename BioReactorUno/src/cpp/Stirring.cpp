#include <lib/Stirring.h>
#include <Arduino.h>

Stirring::Stirring(int pwmPin, int encoderPin, double kP, double kI, double kD)
{
    this->controller.kP = kP;
    outPin = pwmPin;
    inPin = encoderPin;
    pinMode(encoderPin, INPUT);
    pinMode(pwmPin, OUTPUT);
}

void Stirring::loop(double currTime, double prevTime, double frequency){
    setPoint = 900; //to be changed
    currVal = frequency;
    double effort = controller.loop(setPoint, currVal, currTime, prevTime);
    if (effort < 0){
        analogWrite(outPin, 0);
        Serial.println("Less than zero");
    }
    else {
        analogWrite(outPin, effort*(255/5));
    }
}