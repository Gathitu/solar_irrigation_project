#pragma once
#ifndef Temperature_Sensor_h
#define Temperature_Sensor_h
#include <DHT.h>
#include "Constants.h"
#include "Arduino.h"

class Temperature_Sensor
{
  public:
    Temperature_Sensor(); //constructor
    
    bool readSoilTemperature(unsigned long now);
    float currentSoilTemperature();
    bool readEnvTemperature(DHT dhtSensor,unsigned long now);
    float currentEnvTemperature();
  
  private:
    unsigned long soilSensorPinReadPreviousMs = 0;
    unsigned long envSensorPinReadPreviousMs = 0;
    bool _canCheckSoilSensorReading(unsigned long now);
    bool _canCheckEnvSensorReading(unsigned long now);

};

#endif 

