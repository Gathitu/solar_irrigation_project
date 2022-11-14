#include "Humidity_Sensor.h"

Humidity_Sensor::Humidity_Sensor(){}

float _humidity;

bool Humidity_Sensor::readHumidity(DHT dhtSensor,unsigned long now){
  if(!_canCheckSensorReading(now))  return false;

  float humidity = dhtSensor.readHumidity();
  bool humidityValueChanged = _humidity == humidity;
  _humidity = humidity;
  return humidityValueChanged;
}

//Check if enough time has passed before a sensor pin is read
bool Humidity_Sensor::_canCheckSensorReading(unsigned long now){
  if(hSensorPinReadPreviousMs == 0){
    hSensorPinReadPreviousMs = now;
    return false;
  }else{
    unsigned long timePassed = now - hSensorPinReadPreviousMs;
    if (timePassed >= HSensePinReadInterval) { 
      hSensorPinReadPreviousMs = 0;                  
      return true;
    }
  }
  return false;
}

float Humidity_Sensor::currentHumidity(){
  return _humidity;
}
