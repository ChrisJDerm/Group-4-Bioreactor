#include <lib/Stirring.h>
#include <Arduino.h>

Stirring::Stirring(int pwmPin, int encoderPin, double kP, double kI, double kD) : Subsystem(kP, kI, kD) {
    outPin = pwmPin;
    inPin = encoderPin;
    pinMode(encoderPin, INPUT);
    pinMode(pwmPin, OUTPUT);
}

void Stirring::loop(double currTime, double prevTime, double frequency, int setpoint){
    currVal = frequency;
    double effort = constrain(controller.loop(setpoint, currVal, currTime, prevTime), 0, 5);
   
    analogWrite(outPin, effort*(255/5));

    Serial.print(">Speed (RPM):");
    Serial.println(currVal);

    Serial.print(">StirSet:");
    Serial.println(setpoint);
}