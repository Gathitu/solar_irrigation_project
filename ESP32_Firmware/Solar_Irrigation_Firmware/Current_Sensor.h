#pragma once
#ifndef Current_Sensor_h
#define Current_Sensor_h
#include "Constants.h"
#include "Arduino.h"

class Current_Sensor
{
  public:
    Current_Sensor(); //constructor
    bool readSolarPVCurrent(unsigned long now);
    float solarPVCurrent();
  
  private:
    unsigned long sensorPinReadPreviousMs = 0;
    bool _canCheckSensorReading(unsigned long now);

};

#endif 