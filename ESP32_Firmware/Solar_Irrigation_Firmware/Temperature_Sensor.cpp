#include "Temperature_Sensor.h"

Temperature_Sensor::Temperature_Sensor(){}

float _currentSoilTemperature;
float _currentEnvTemperature; //Environment


//SOIL TEMPERATURE

///Returns true if temp value changed
bool Temperature_Sensor::readSoilTemperature(unsigned long now){
  if(!_canCheckSoilSensorReading(now))  return false;
 
  float temperature;
  bool tempChanged = _currentSoilTemperature == temperature;
  _currentSoilTemperature = temperature;
  return tempChanged;
}

//Check if enough time has passed before a sensor pin is read
bool Temperature_Sensor::_canCheckSoilSensorReading(unsigned long now){
  if(soilSensorPinReadPreviousMs == 0){
    soilSensorPinReadPreviousMs = now;
    return false;
  }else{
    unsigned long timePassed = now - soilSensorPinReadPreviousMs;
    if (timePassed >= TSensePinReadInterval) { 
      soilSensorPinReadPreviousMs = 0;                  
      return true;
    }
  }
  return false;
}

float Temperature_Sensor::currentSoilTemperature(){
  return _currentSoilTemperature;
}


//ENVIRONMENT TEMPERATURE

///Returns true if temp value changed
bool Temperature_Sensor::readEnvTemperature(DHT dhtSensor,unsigned long now){
  if(!_canCheckEnvSensorReading(now))  return false;
  
  int temperature = dhtSensor.readHumidity();
  bool tempChanged = _currentEnvTemperature == temperature;
  _currentEnvTemperature = temperature;
  return tempChanged;
}

//Check if enough time has passed before a sensor pin is read
bool Temperature_Sensor::_canCheckEnvSensorReading(unsigned long now){ 
  if(envSensorPinReadPreviousMs == 0){
    envSensorPinReadPreviousMs = now;
    return false;
  }else{
    unsigned long timePassed = now - envSensorPinReadPreviousMs;
    if (timePassed >= T_DHT_SensePinReadInterval) { 
      envSensorPinReadPreviousMs = 0;                  
      return true;
    }
  }
  return false;
}

float Temperature_Sensor::currentEnvTemperature(){
  return _currentEnvTemperature;
}
