#pragma once
#ifndef Moisture_Sensor_h
#define Moisture_Sensor_h
#include "Constants.h"
#include "Arduino.h"

class Moisture_Sensor;
static Moisture_Sensor *getInstance();

class Moisture_Sensor
{
  public:
    Moisture_Sensor(); //constructor
    void init();
    bool readSoilMoisture(unsigned long now);
    int currentSoilMoisture();
  
  private:
    unsigned long sensorPinReadPreviousMs = 0;
    bool _canCheckSensorReading(unsigned long now);

};

#endif 
