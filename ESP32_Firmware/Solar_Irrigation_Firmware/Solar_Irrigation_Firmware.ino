#include "Constants.h"
#include "Voltage_Sensor.h"
#include "Current_Sensor.h"
#include "PH_Sensor.h"
#include "Humidity_Sensor.h"
#include "Moisture_Sensor.h"
#include "Rainfall_Sensor.h"
#include "Temperature_Sensor.h"
#include "Ultrasonic_Level_Sensor.h"
#include <DHT.h>
#include "WiFiManager.h"
#include "Firebase_RTD.h"  //Firebase Real-Time-DB

Voltage_Sensor voltageSensor;
Current_Sensor currentSensor;
PH_Sensor pHSensor;
Humidity_Sensor humiditySensor;
Moisture_Sensor moistureSensor;
Rainfall_Sensor rainfallSensor;
Temperature_Sensor temperatureSensor;
Ultrasonic_Level_Sensor tankLevelSensor;
WiFiManager wiFiManager;
Firebase_RTD firebaseRTD;

DHT dhtSensor(DHT_PIN, DHT_TYPE); //DHT22-> HUMIDITY& TEMPERATURE SENSOR
bool dontInitializePins = true;

void setup() {  
  Serial.begin(115200);
  while (!Serial); // Waiting for Serial Monitor
  Serial.setDebugOutput(true);
  
  wiFiManager.init();
  firebaseRTD.initialize(streamCallbackRTD, streamTimeoutCallbackRTD);//Initialize Firebase Real-Time-DB

  if(dontInitializePins) return;
  dhtSensor.begin();
  pHSensor.init();
  rainfallSensor.init();
  tankLevelSensor.init();
}

void streamCallbackRTD(MultiPathStreamData stream){
  firebaseRTD.streamCallback(stream,pumpButtonTappedByUser);
}

void pumpButtonTappedByUser(bool turnPumpOn){
  firebaseRTD.updatePumpStateInRTD(turnPumpOn);
}

void streamTimeoutCallbackRTD(bool timeout){
  firebaseRTD.streamTimeoutCallback(timeout);
}

void loop() {
  unsigned long now = millis();
  wiFiManager.checkWiFiConnection(now);

  if(dontInitializePins) return;
  bool aValueHasChanged = false;
  if(voltageSensor.readSolarPVVoltage(now)) aValueHasChanged = true;
  if(currentSensor.readSolarPVCurrent(now)) aValueHasChanged = true;
  if(humiditySensor.readHumidity(dhtSensor,now)) aValueHasChanged = true;
  if(temperatureSensor.readEnvTemperature(dhtSensor,now)) aValueHasChanged = true; ///DHT sensor
  if(temperatureSensor.readSoilTemperature(now)) aValueHasChanged = true;
  if(pHSensor.readPH(now)) aValueHasChanged = true;
  if(moistureSensor.readSoilMoisture(now)) aValueHasChanged = true;
  if(rainfallSensor.readRainfall(now)) aValueHasChanged = true;
  if(tankLevelSensor.readOverheadTankLevel(now)) aValueHasChanged = true;
  if(tankLevelSensor.readUndergroundTankLevel(now)) aValueHasChanged = true;
  
  if(aValueHasChanged) {
    firebaseRTD.updateSensorsValuesInRTD(
      String(temperatureSensor.currentEnvTemperature()),
      String(temperatureSensor.currentSoilTemperature()),
      String(humiditySensor.currentHumidity()),
      String(pHSensor.currentPH()),
      String(tankLevelSensor.currentOverheadTankLevel()),
      String(tankLevelSensor.currentUndergroundTankLevel()),
      String(rainfallSensor.currentRainfall()),
      String(currentSensor.solarPVCurrent()),
      String(voltageSensor.solarPVVoltage())
    );
  }

}

  //TODO: SINGLETONS IN EVERY SENSOR AND FIREBASE RTD THEN UPDATE GIT WHILE REMOVING CREDENTIALS ,then COLLABORATE,

