#include "Current_Sensor.h"

Current_Sensor::Current_Sensor(){}

float _solarCurrent;

///Returns true if solarPV current changed
bool Current_Sensor::readSolarPVCurrent(unsigned long now){
  if(!_canCheckSensorReading(now))  return false;
  float curr;
  bool currentChanged = _solarCurrent == curr;
  _solarCurrent = curr;
  return currentChanged;
}

//Check if enough time has passed before a sensor pin is read
bool Current_Sensor::_canCheckSensorReading(unsigned long now){
  if(sensorPinReadPreviousMs == 0){
    sensorPinReadPreviousMs = now;
    return false;
  }else{
    unsigned long timePassed = now - sensorPinReadPreviousMs;
    if (timePassed >= ISensePinReadInterval) { 
      sensorPinReadPreviousMs = 0;                  
      return true;
    }
  }
  return false;
}

float Current_Sensor::solarPVCurrent(){
  return _solarCurrent;
}
