#pragma once
#ifndef Firebase_RTD_h
#define Firebase_RTD_h
#include "FirebaseESP32.h"

class Firebase_RTD{
  public:
    Firebase_RTD();
    void initialize(void (*streamCallback)(MultiPathStreamData), void (*streamTimeoutCallback)(bool));
    void streamCallback(MultiPathStreamData stream,void (*pumpButtonTappedByUser)(bool));
    void streamTimeoutCallback(bool timeout);
    void updateSensorsValuesInRTD(
      String currentEnvTemperature,
      String currentSoilTemperature,
      String currentHumidity,
      String currentPH,
      String currentOverheadTankLevel,
      String currentUndergroundTankLevel,
      String currentRainfall,
      String solarPVCurrent,
      String solarPVVoltage
    );
    void updatePumpStateInRTD(bool turnPumpOn);
    
  private:
    bool _canSendDataToDB();

};

#endif