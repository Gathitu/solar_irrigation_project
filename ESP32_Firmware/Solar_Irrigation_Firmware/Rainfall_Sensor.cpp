#include "Rainfall_Sensor.h"

int _rainfallAnalogueValue;
bool rainfallState;

Rainfall_Sensor::Rainfall_Sensor(){}


void Rainfall_Sensor::init(){
  pinMode(RAINFALL_SENSE, INPUT);//configure rainfall sensor pins as inputs//
  pinMode(RAINFALL_SENSE_ANALOGUE, INPUT);
}

///Returns true if rainfall value changed
bool Rainfall_Sensor::readRainfall(unsigned long now){//TODO: Max rainfall to be updated in DB
  if(!_canCheckSensorReading(now))  return false;

  bool isCurrentlyRaining = digitalRead(RAINFALL_SENSE) == HIGH;
  if(!isCurrentlyRaining)  return false;
 
  int rainfallV = analogRead(RAINFALL_SENSE_ANALOGUE);
  bool rainfallValueChanged = _rainfallAnalogueValue > rainfallV;
  _rainfallAnalogueValue = rainfallV;
  return rainfallValueChanged;
}

//Check if enough time has passed before a sensor pin is read
bool Rainfall_Sensor::_canCheckSensorReading(unsigned long now){
  if(sensorPinReadPreviousMs == 0){
    sensorPinReadPreviousMs = now;
    return false;
  }else{
    unsigned long timePassed = now - sensorPinReadPreviousMs;
    if (timePassed >= RSensePinReadInterval) { 
      sensorPinReadPreviousMs = 0;                  
      return true;
    }
  }
  return false;
}

int Rainfall_Sensor::currentRainfall(){
  return _rainfallAnalogueValue;
}

