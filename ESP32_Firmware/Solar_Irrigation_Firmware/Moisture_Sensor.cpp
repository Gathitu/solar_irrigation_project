#include "Moisture_Sensor.h"

int _soilMoisture;

Moisture_Sensor::Moisture_Sensor(){}


void Moisture_Sensor::init(){
  pinMode(MOISTURE_SENSE_ANALOGUE, INPUT);
}

///Returns true if moisture value changed
bool Moisture_Sensor::readSoilMoisture(unsigned long now){
  if(!_canCheckSensorReading(now))  return false;
 
  int moisture = analogRead(MOISTURE_SENSE_ANALOGUE);
  bool moistureValueChanged = _soilMoisture == moisture;
  _soilMoisture = moisture;
  return moistureValueChanged;
}

//Check if enough time has passed before a sensor pin is read
bool Moisture_Sensor::_canCheckSensorReading(unsigned long now){
  if(sensorPinReadPreviousMs == 0){
    sensorPinReadPreviousMs = now;
    return false;
  }else{
    unsigned long timePassed = now - sensorPinReadPreviousMs;
    if (timePassed >= MSensePinReadInterval) { 
      sensorPinReadPreviousMs = 0;                  
      return true;
    }
  }
  return false;
}

int Moisture_Sensor::currentSoilMoisture(){
  return _soilMoisture;
}
