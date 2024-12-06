#include <Arduino.h>
#include "lib/Stirring.h"
#include "lib/Heating.h"
#include "lib/Constants.h"
#include "lib/Subsystem.h"
#include "lib/pH.h"

#include "AltSoftSerial.h"

// Variables
long currTime, prevTime, pulse, prevPulse, T1;
int Vmotor, trig;
float speed, meanSpeed, frequency, deltaT;
int delayTime;

int flag = 0;

// Software UART instance
AltSoftSerial telemetry;

Stirring* stir;
Heating* heat;
pH*  pHSys;

// put function declarations here:
void freqCount();

void setup() {
    Serial.begin(230400);
    telemetry.begin(115200);
    attachInterrupt(digitalPinToInterrupt(2), freqCount, CHANGE);

    stir = new Stirring(MOTOR_PWM, FREQ_PIN, stirKP, stirKI, stirKD);
    heat = new Heating(THERMISTOR_PIN, HEATER_PWM, heatKP, heatKI, heatKD);
    pHSys = new pH(A3, 5, 6, 1, 0, 0);
}

void loop() {
    delayTime++;
    prevTime = currTime;
    currTime = micros();
    deltaT = (currTime - prevTime);


    // Stirring
    speed = frequency*FREQ_TO_RPM; // measured speed in RPM (N pulses per revolution)

    int stirSetpoint = flag ? 500 : 1000;
    // int stirSetpoint = 400;
    int heatSetpoint = 30;
    stir->loop(currTime, prevTime, frequency, stirSetpoint);
    pHSys->loop(currTime, prevTime, 7.0);
    if (delayTime > 1000)
    {
        flag = !flag;
        heat->loop(currTime, prevTime, heatSetpoint);
        delayTime = 0;
    }

    telemetry.print(speed);
    telemetry.print(",");
    telemetry.print(heat->getTemp());
    telemetry.print(",");
    telemetry.println(pHSys->getpH());

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