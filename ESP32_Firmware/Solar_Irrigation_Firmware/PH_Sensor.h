#pragma once
#ifndef PH_Sensor_h
#define PH_Sensor_h
#include "Constants.h"
#include "Constants.h"
#include "Arduino.h"

class PH_Sensor
{
  public:
    PH_Sensor(); //constructor
    void init();
    bool readPH(unsigned long now);
    float currentPH();
  
  private:
    unsigned long sensorPinReadPreviousMs = 0;
    bool _canCheckSensorReading(unsigned long now);

};

#endif 
