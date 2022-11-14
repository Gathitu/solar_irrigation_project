#include "PH_Sensor.h"

PH_Sensor::PH_Sensor(){}

float _PHValue;
const float calibration_value = 21.34; 
int buffer_arr[10],temp;

void PH_Sensor::init(){
  pinMode(PH_SENSE_ANALOGUE, INPUT);
}

///Returns true if ph Value changed
bool PH_Sensor::readPH(unsigned long now){
  if(!_canCheckSensorReading(now))  return false;

  for(int i=0;i<10;i++) { 
    buffer_arr[i]=analogRead(PH_SENSE_ANALOGUE);
    delay(30);
  }
  for(int i=0;i<9;i++){
    for(int j=i+1;j<10;j++){
      if(buffer_arr[i]>buffer_arr[j]){
        temp=buffer_arr[i];
        buffer_arr[i]=buffer_arr[j];
        buffer_arr[j]=temp;
      }
    }
  }
  unsigned long int avgval=0;
  for(int i=2;i<8;i++)  avgval+=buffer_arr[i];
  float volt=(float)avgval*5.0/1024/6;
  float ph_val = -5.70 * volt + calibration_value;
  bool phValueChanged = ph_val == _PHValue;
  _PHValue = ph_val;
  return phValueChanged;
}

//Check if enough time has passed before a sensor pin is read
bool PH_Sensor::_canCheckSensorReading(unsigned long now){
  if(sensorPinReadPreviousMs == 0){
    sensorPinReadPreviousMs = now;
    return false;
  }else{
    unsigned long timePassed = now - sensorPinReadPreviousMs;
    if (timePassed >= PHSensePinReadInterval) { 
      sensorPinReadPreviousMs = 0;                  
      return true;
    }
  }
  return false;
}

float PH_Sensor::currentPH(){
  return _PHValue;
}
