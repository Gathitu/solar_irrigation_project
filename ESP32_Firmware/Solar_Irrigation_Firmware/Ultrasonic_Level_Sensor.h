#pragma once
#ifndef Ultrasonic_Level_Sensor_h
#define Ultrasonic_Level_Sensor_h
#include "Constants.h"
#include "Arduino.h"

class Ultrasonic_Level_Sensor
{
    
  public:
    Ultrasonic_Level_Sensor(); //constructor
    void init();
    bool readOverheadTankLevel(unsigned long now);
    float currentOverheadTankLevel();
    bool readUndergroundTankLevel(unsigned long now);
    float currentUndergroundTankLevel();
  
  private:
    unsigned long overheadSensorPinReadPreviousMs = 0;
    unsigned long undergroundSensorPinReadPreviousMs = 0;
    bool _canCheckOverheadSensorReading(unsigned long now);
    bool _canCheckUndergroundSensorReading(unsigned long now);
    float _waterLevelDistFromTankTop(bool isOverheadTank = true); //to allow for no param to be passed inside

};

#endif 