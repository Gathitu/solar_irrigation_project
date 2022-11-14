#pragma once
#ifndef Voltage_Sensor_h
#define Voltage_Sensor_h
#include "Constants.h"
#include "Arduino.h"

class Voltage_Sensor
{
  public:
    Voltage_Sensor(); //constructor
    bool readSolarPVVoltage(unsigned long now);
    float solarPVVoltage();
  
  private:
    unsigned long sensorPinReadPreviousMs = 0;
    bool _canCheckSensorReading(unsigned long now);

};

#endif 