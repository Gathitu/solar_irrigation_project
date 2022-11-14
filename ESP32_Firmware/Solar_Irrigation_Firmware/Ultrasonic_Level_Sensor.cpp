#include "Ultrasonic_Level_Sensor.h"

#define SOUND_SPEED 0.034
#define CM_TO_METRE 0.01
float _overheadTankLevel; //in metres
float _undergroundTankLevel; //in metres


Ultrasonic_Level_Sensor::Ultrasonic_Level_Sensor(){}


void Ultrasonic_Level_Sensor::init(){
  pinMode(TRIG_PIN_UTL, OUTPUT);
  pinMode(TRIG_PIN_OTL, OUTPUT);
  pinMode(ECHO_PIN_UTL, INPUT);
  pinMode(ECHO_PIN_OTL, INPUT);
}

///OVERHEAD TANK

///Returns true if level value changed
bool Ultrasonic_Level_Sensor::readOverheadTankLevel(unsigned long now){
  if(!_canCheckOverheadSensorReading(now))  return false;
 
  float overheadTankLevel = _waterLevelDistFromTankTop();
  bool levelChanged = _overheadTankLevel == overheadTankLevel;
  _overheadTankLevel = overheadTankLevel;
  return levelChanged;
}

//Check if enough time has passed before a sensor pin is read
bool Ultrasonic_Level_Sensor::_canCheckOverheadSensorReading(unsigned long now){
  if(overheadSensorPinReadPreviousMs == 0){
    overheadSensorPinReadPreviousMs = now;
    return false;
  }else{
    unsigned long timePassed = now - overheadSensorPinReadPreviousMs;
    if (timePassed >= L_O_SensePinReadInterval) { 
      overheadSensorPinReadPreviousMs = 0;                  
      return true;
    }
  }
  return false;
}

float Ultrasonic_Level_Sensor::currentOverheadTankLevel(){
  return _overheadTankLevel;
}

float Ultrasonic_Level_Sensor::_waterLevelDistFromTankTop(bool isOverheadTank){//Dist->Distance
  long duration = 0;
  if(isOverheadTank){
    digitalWrite(TRIG_PIN_OTL, LOW);// Clear TRIG_PIN_UTL
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN_OTL, HIGH);
    // Set the TRIG_PIN_UTL on HIGH state for 10 micro seconds
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN_OTL, LOW);

    // Read the ECHO_PIN_UTL which returns the sound wave travel time in microseconds
    duration = pulseIn(ECHO_PIN_OTL, HIGH);
  }
  else{
    digitalWrite(TRIG_PIN_UTL, LOW);// Clear TRIG_PIN_UTL
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN_UTL, HIGH);
    // Set the TRIG_PIN_UTL on HIGH state for 10 micro seconds
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN_UTL, LOW);

    // Read the ECHO_PIN_UTL which returns the sound wave travel time in microseconds
    duration = pulseIn(ECHO_PIN_UTL, HIGH);
  }
  
  // Calculating the distance
  float distanceInCm = duration * SOUND_SPEED/2;
  return distanceInCm * CM_TO_METRE;
}

///UNDERGROUND TANK

///Returns true if level value changed
bool Ultrasonic_Level_Sensor::readUndergroundTankLevel(unsigned long now){
  if(!_canCheckUndergroundSensorReading(now))  return false;
 
  float undergroundTankLevel = _waterLevelDistFromTankTop();
  bool levelChanged = _undergroundTankLevel == undergroundTankLevel;
  _undergroundTankLevel = undergroundTankLevel;
  return levelChanged;
}

//Check if enough time has passed before a sensor pin is read
bool Ultrasonic_Level_Sensor::_canCheckUndergroundSensorReading(unsigned long now){
  if(undergroundSensorPinReadPreviousMs == 0){
    undergroundSensorPinReadPreviousMs = now;
    return false;
  }else{
    unsigned long timePassed = now - undergroundSensorPinReadPreviousMs;
    if (timePassed >= L_U_SensePinReadInterval) { 
      undergroundSensorPinReadPreviousMs = 0;                  
      return true;
    }
  }
  return false;
}

float Ultrasonic_Level_Sensor::currentUndergroundTankLevel(){ //in metres
  return _undergroundTankLevel;
}
