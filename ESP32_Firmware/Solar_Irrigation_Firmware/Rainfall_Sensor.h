#pragma once
#ifndef Rainfall_Sensor_h
#define Rainfall_Sensor_h
#include "Constants.h"
#include "Arduino.h"

class Rainfall_Sensor
{
  public:
    Rainfall_Sensor(); //constructor
    void init();
    bool readRainfall(unsigned long now); 
    int currentRainfall();
  
  private:
    unsigned long sensorPinReadPreviousMs = 0;
    bool _canCheckSensorReading(unsigned long now);

};


#endif 