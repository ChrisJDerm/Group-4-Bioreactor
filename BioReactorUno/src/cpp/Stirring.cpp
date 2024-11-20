#include <lib/Stirring.h>
#include <Arduino.h>

Stirring::Stirring(int pwmPin, int encoderPin, double kP, double kI, double kD)
{
    this->controller.kP = kP;
    this->controller.kI = kI;
    this->controller.kD = kD;
    outPin = pwmPin;
    inPin = encoderPin;
    pinMode(encoderPin, INPUT);
    pinMode(pwmPin, OUTPUT);
}

void Stirring::loop(double currTime, double prevTime, double frequency){
    setPoint = 300; //to be changed
    currVal = frequency;
    double effort = constrain(controller.loop(setPoint, currVal, currTime, prevTime), 0, 5);
    if (effort < 0){
        analogWrite(outPin, 0);
        // Serial.println("Less than zero");
    }
    else {
        analogWrite(outPin, effort*(255/5));
    }
}