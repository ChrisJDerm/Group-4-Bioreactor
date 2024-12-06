#include <lib/pH.h>
#include <Arduino.h>

pH::pH(int inPin, int alkaPin, int acidPin, double kP, double kI, double kD) : Subsystem(kP, kI, kD) {
  this->inPin = inPin;
  this->alkaPin = alkaPin;
  this->acidPin = acidPin;
  pinMode(inPin, INPUT);
  pinMode(alkaPin, OUTPUT);
  pinMode(acidPin, OUTPUT);
}

float pH::calculateMedian(float arr[], int size) {
  float temp[size];
  memcpy(temp, arr, size * sizeof(float));
  
  for (int i = 0; i < size - 1; i++) {
    for (int j = 0; j < size - i - 1; j++) {
      if (temp[j] > temp[j + 1]) {
        float swap = temp[j];
        temp[j] = temp[j + 1];
        temp[j + 1] = swap;
      }
    }
  }
  // Return the median (middle value in the sorted array)
  return temp[size / 2];
}

void pH::loop(double currTime, double prevTime, double setPoint){
    int sensorValue = analogRead(inPin);

    float voltage = sensorValue * (5.0 / 1024.0);

    voltageReadings[currentIndex] = voltage;
    currentIndex = (currentIndex + 1) % NUM_READINGS;

    // float medianVoltage = calculateMedian(voltageReadings, NUM_READINGS);
    float medianVoltage = voltage;

    float pHVal = 7.0 - ((neutralV - medianVoltage) / slope);

    // Serial.println(pHVal);

    double effort = controller.loop(setPoint, pHVal, prevTime, currTime);

    int outPin = effort < 0 ? alkaPin : acidPin; 

    effort = abs(effort) < 0.4 ? 0 : 255;

    Serial.print(">pH:");
    Serial.println(pHVal);
    
    analogWrite(outPin, effort);
}
