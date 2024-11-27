#include <lib/Heating.h>
#include <Arduino.h>
#include "lib/Constants.h"

 // Thermistor parameters
#define SERIES_RESISTOR 10000.0
#define NOMINAL_TEMP 25.0          
#define NOMINAL_RESISTANCE 10000.0
#define B_COEFFICIENT 4220.0       

Heating::Heating(int inPin, int outPin, double kP, double kI, double kD)
    : Subsystem(kP, kI, kD) {
    this->inPin = THERMISTOR_PIN;
    this->outPin = outPin;
    pinMode(inPin, INPUT);
    pinMode(outPin, OUTPUT);
    analogWrite(outPin, 0);
}

double Heating::getTemp() {
    int rawADC = analogRead(inPin);
    Serial.print("ADC: ");
    Serial.print(rawADC);
    
    float resistance = SERIES_RESISTOR / ((1015.0 / rawADC) - 1);
    
    float temp = resistance / NOMINAL_RESISTANCE;     
    temp = log(temp);                     
    temp /= B_COEFFICIENT;                     
    temp += 1.0 / (NOMINAL_TEMP + 273.15);     
    temp = 1.0 / temp;                    
    temp -= 273.15;   
    
    return temp;
}

void Heating::loop(double currTime, double prevTime) {
    setPoint = TARGET_TEMP; 

    currVal = getTemp();
    
    if (currVal == -999) {
        analogWrite(outPin, 0); // Safety shutoff on sensor error
        return;
    }
    
    double effort = controller.loop(setPoint, currVal, currTime, prevTime);
    int pwmValue;
    
    if (effort < 0 || currVal >= MAX_TEMP) {
        pwmValue = 0;
    } else {
        pwmValue = effort * (255.0/5.0);
        pwmValue = constrain(pwmValue, 0, 201);
    }
    
    analogWrite(outPin, pwmValue);

    
    Serial.print(", Temperature: ");
    Serial.print(currVal);
    Serial.print("°C, Target: ");
    Serial.print(setPoint);
    Serial.print("°C, Effort: ");
    Serial.print(effort);
    Serial.print(", PWM: ");
    Serial.println(pwmValue);
}