#include <Arduino.h>
#include "lib/Stirring.h"
#include "lib/Heating.h"
#include "lib/Constants.h"
#include "lib/Subsystem.h"

// Variables
long currTime, prevTime, pulse, prevPulse, T1;
int Vmotor, trig;
float speed, meanSpeed, frequency, deltaT;

// put function declarations here:
void freqCount();

void setup() {
    Serial.begin(250000);
    Stirring stir = Stirring(MOTOR_PWM, FREQ_PIN, stirKP, stirKI, stirKD, &freqCount);
    Heating heat = Heating(HEATER_PWM, THERMISTOR, heatKP, heatKI, heatKD);
    pinMode(10, OUTPUT);
}

void loop() {
    analogWrite(10, 255/2);
    // currTime = micros();
    // deltaT = (currTime - prevTime);
    // if (currTime-T1>0) {
    //     prevTime = currTime;
    //     T1 = T1+10000;
    //     speed = frequency*FREQ_TO_RPM; // measured speed in RPM (N pulses per revolution)
    //     Vmotor = constrain(Vmotor,0,1023); // Limit motor voltage to 5 V - assuming 5 V motor supply
    //     if (Vmotor==255) {
    //         Vmotor=256;
    //     } // Work-around for bug in Nano/Uno with 10-bit configuration
    //     analogWrite(MOTOR_PWM, Vmotor);
    //     if (currTime-pulse>1e5) {
    //         speed = 0; frequency = 0;
    //     } // Indicate zero measured speed if no pulses detected for 0.1 s
    //     meanSpeed = 0.1*speed+0.9*meanSpeed;
    //     Serial.print(0); Serial.print(","); Serial.print(1000); Serial.print(",");
    //     Serial.println(meanSpeed); // for Arduino IDE or CoolTerm etc Serial Plotter
    // }
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