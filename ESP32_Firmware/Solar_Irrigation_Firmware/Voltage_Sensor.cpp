#include "Voltage_Sensor.h"

Voltage_Sensor::Voltage_Sensor(){}

float _currentSolarV;

///Returns true if solarPV voltage changed
bool Voltage_Sensor::readSolarPVVoltage(unsigned long now){
  if(!_canCheckSensorReading(now))  return false;
  float voltage;
  bool voltageChanged = _currentSolarV == voltage;
  _currentSolarV = voltage;
  return voltageChanged;
}

//Check if enough time has passed before a sensor pin is read
bool Voltage_Sensor::_canCheckSensorReading(unsigned long now){
  if(sensorPinReadPreviousMs == 0){
    sensorPinReadPreviousMs = now;
    return false;
  }else{
    unsigned long timePassed = now - sensorPinReadPreviousMs;
    if (timePassed >= VSensePinReadInterval) { 
      sensorPinReadPreviousMs = 0;                  
      return true;
    }
  }
  return false;
}

float Voltage_Sensor::solarPVVoltage(){
  return _currentSolarV;
}
