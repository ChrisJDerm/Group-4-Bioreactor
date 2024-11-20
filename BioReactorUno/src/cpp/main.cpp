#include <Arduino.h>
#include "lib/Stirring.h"
#include "lib/Heating.h"
#include "lib/Constants.h"
#include "lib/Subsystem.h"

// Variables
long currTime, prevTime, pulse, prevPulse, T1;
int Vmotor, trig;
float speed, meanSpeed, frequency, deltaT;

Stirring* stir;

// put function declarations here:
void freqCount();

void setup() {
    Serial.begin(250000);
    stir = &Stirring(MOTOR_PWM, FREQ_PIN, stirKP, stirKI, stirKD);
    attachInterrupt(digitalPinToInterrupt(2), freqCount, CHANGE);
}

void loop() {
    prevTime = currTime;
    currTime = micros();
    deltaT = (currTime - prevTime);

    // Stirring
    speed = frequency*FREQ_TO_RPM; // measured speed in RPM (N pulses per revolution)
    stir->loop(currTime, prevTime, speed);
    Serial.println(speed);
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