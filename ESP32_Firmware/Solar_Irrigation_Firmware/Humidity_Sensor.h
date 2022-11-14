#pragma once
#ifndef Humidity_Sensor_h
#define Humidity_Sensor_h
#include <DHT.h>
#include "Constants.h"
#include "Arduino.h"

class Humidity_Sensor
{
  public:
    Humidity_Sensor(); //constructor
    bool readHumidity(DHT dhtSensor,unsigned long now);
    float currentHumidity();
  
  private:
    unsigned long hSensorPinReadPreviousMs = 0;
    bool _canCheckSensorReading(unsigned long now);

};

#endif 

