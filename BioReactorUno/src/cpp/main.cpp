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

void parseInputString(const char *input);

const int bufferSize = 65; // Maximum buffer size for one line of input
char inputBuffer[bufferSize];
int bufferIndex = 0;

// Software UART instance
AltSoftSerial telemetry;

Stirring* stir;
Heating* heat;
pH*  pHSys;

double stirSetpoint = 0;
double heatSetpoint = 23;
double pHSetpoint = 7;

// put function declarations here:
void freqCount();

void setup() {
    Serial.begin(230400);
    telemetry.begin(9600);
    attachInterrupt(digitalPinToInterrupt(2), freqCount, CHANGE);

    stir = new Stirring(MOTOR_PWM, FREQ_PIN, stirKP, stirKI, stirKD);
    heat = new Heating(THERMISTOR_PIN, HEATER_PWM, heatKP, heatKI, heatKD);
    pHSys = new pH(A3, 6, 5, 1, 0, 0);
}

void loop() {
    delayTime++;
    prevTime = currTime;
    currTime = micros();
    deltaT = (currTime - prevTime);

    Serial.print(">DelayTime:");
    Serial.println(delayTime);

    if (telemetry.available() > 0) {
        
        char incomingChar = telemetry.read(); // Read one character
        if (incomingChar == '\n') {
            // End of the current line, process the buffer
            inputBuffer[bufferIndex] = '\0'; // Null-terminate the string
            parseInputString(inputBuffer);
            bufferIndex = 0; // Reset the buffer index for the next input
        } else if (bufferIndex < bufferSize - 1) {
            inputBuffer[bufferIndex++] = incomingChar;
        } else {
            bufferIndex = 0;
        }
    }

    // Stirring
    speed = frequency*FREQ_TO_RPM; // measured speed in RPM (N pulses per revolution)
    
    stir->loop(currTime, prevTime, frequency, stirSetpoint);
    pHSys->loop(currTime, prevTime, pHSetpoint);
    heat->loop(currTime, prevTime, heatSetpoint);
    if (delayTime > 200)
    {
        telemetry.print(pHSys->getpH());
        telemetry.print(",");
        telemetry.print(heat->getTemp());
        telemetry.print(",");
        telemetry.println(speed);
        flag = !flag;
        delayTime = 0;
    }
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

void parseInputString(const char *input) {

    // Ensure the input ends with '\n' before processing
    String inputStr = String(input);
    inputStr.trim(); // Removes any extra whitespace including '\n'

    // Split the string using commas as delimiters
    int firstComma = inputStr.indexOf(',');
    int secondComma = inputStr.indexOf(',', firstComma + 1);

    if (firstComma > 0 && secondComma > firstComma) {
        // Extract the substrings and convert them to doubles
        String pHStr = inputStr.substring(0, firstComma);
        String temperatureStr = inputStr.substring(firstComma + 1, secondComma);
        String rpmStr = inputStr.substring(secondComma + 1);

        // Convert strings to doubles
        pHSetpoint = pHStr.toDouble();
        heatSetpoint = temperatureStr.toDouble();
        stirSetpoint = rpmStr.toDouble();
    }
}