#include <lib/Heating.h>
#include <Arduino.h>
#include "lib/Constants.h"

 // Thermistor parameters
#define SERIES_RESISTOR 10000.0
#define NOMINAL_TEMP 25.0          
#define NOMINAL_RESISTANCE 10000.0
#define B_COEFFICIENT 4220.0       

Heating::Heating(int inPin, int outPin, double kP, double kI, double kD) : Subsystem(kP, kI, kD) {
    this->inPin = inPin;
    this->outPin = outPin;
    pinMode(inPin, INPUT);
    pinMode(outPin, OUTPUT);
    analogWrite(outPin, 0);
}

double Heating::getTemp() {
    int rawADC = analogRead(inPin);
    
    float resistance = SERIES_RESISTOR / ((1040.0 / rawADC) - 1);
    
    float temp = resistance / NOMINAL_RESISTANCE;     
    temp = log(temp);                     
    temp /= B_COEFFICIENT;                     
    temp += 1.0 / (NOMINAL_TEMP + 273.15);     
    temp = 1.0 / temp;                    
    temp -= 273.15;   
    
    return temp;
}

void Heating::loop(double currTime, double prevTime, double setPoint) {

    currVal = getTemp();
    
    double effort = controller.loop(setPoint, currVal, currTime, prevTime);
    int pwmValue;
    
    if (effort < 0 || currVal >= MAX_TEMP) {
        pwmValue = 0;
    } else {
        pwmValue = effort * (255.0/5.0);
        pwmValue = constrain(pwmValue, 0, 201);
    }
    
    analogWrite(outPin, pwmValue);

    Serial.print(">Temperature (C):");
    Serial.println(currVal);
    Serial.print(">TempSet:");
    Serial.println(setPoint);
}