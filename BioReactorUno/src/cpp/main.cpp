#include <Arduino.h>
#include "lib/Stirring.h"
#include "lib/Heating.h"
#include "lib/Constants.h"
#include "lib/Subsystem.h"

// Variables
long currTime, prevTime, pulse, prevPulse, T1;
int Vmotor, trig;
float speed, meanSpeed, frequency, deltaT;
int delayTime;

int flag = 0;

Stirring* stir;
Heating* heat;

// put function declarations here:
void freqCount();

void setup() {
    Serial.begin(250000);
    stir = &Stirring(MOTOR_PWM, FREQ_PIN, stirKP, stirKI, stirKD);
    attachInterrupt(digitalPinToInterrupt(2), freqCount, CHANGE);

    // heating
    heat = new Heating(1, HEATER_PWM, heatKP, heatKI, heatKD);
}

void loop() {
    delayTime++;
    prevTime = currTime;
    currTime = micros();
    deltaT = (currTime - prevTime);

    // Stirring
    speed = frequency*FREQ_TO_RPM; // measured speed in RPM (N pulses per revolution)

    // int setpoint = flag ? 500 : 1200;
    int stirSetpoint = 400;
    int heatSetpoint = 30;
    stir->loop(currTime, prevTime, frequency, stirSetpoint);
    if (delayTime > 3000)
    {
        flag = !flag;
        heat->loop(currTime, prevTime, heatSetpoint);
        delayTime = 0;
    }
    // Serial.print(speed);
    // Serial.print(",");
    // Serial.print(0);
    // Serial.print(",");
    // Serial.println(1300);
}

void freqCount(void){
    pulse = micros();
    if(abs(pulse-prevPulse)>T_MIN){ // Ignore indicated speeds > RPMmax
        frequency = 0.75*frequency+2.5e5 / float(pulse-prevPulse); // Calculate speed sensor frequency (Hz)
        prevPulse = pulse;
        trig++;
        if (2*trig>=NPULSES) {
            trig=0;
            digitalWrite(13, !digitalRead(13));
        }
    }
}