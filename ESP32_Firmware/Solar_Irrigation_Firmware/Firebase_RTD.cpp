#include "Firebase_RTD.h"
#include "FirebaseESP32.h"
//FirebaseESP32.h is included in .cpp bcoz unknown error "error: 'firebaseConfig' was not declared in this scope" occurs
// Provide the token generation process info.
#include "addons/TokenHelper.h"
// Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

#define WEB_API_KEY "AIzaSyD9RZ1Bt4DNhVs-v1cWhJA2U5Cx076iIJE" ///Project Settings/General
#define FIREBASE_PROJECT_ID "elevator-iot-project-fa043"  ///Project Settings/General
#define DATABASE_URL "elevator-iot-project-fa043-default-rtdb.firebaseio.com" //firebaseio.com or firebasedatabase.app. Found in RTD section
#define USER_EMAIL "esp32@project.com" 
#define USER_PASSWORD "esp32esp32"
FirebaseConfig firebaseConfig;
FirebaseAuth firebaseAuth;
FirebaseData firebaseData;
FirebaseData stream;
String acknowledgeDeviceRequestEvent= "acknowledgeDeviceRequest";
String acknowledgeDeviceResponseEvent= "acknowledgeDeviceResponse";
String clientInfoUpdateEvent= "clientInfoUpdate";
String elevatorInfoUpdateEvent = "elevatorInfoUpdate";
static const String esp32ID = "ESP32";
bool debugFirebaseStatus = true;
// void firebaseTokenStatusCallback(TokenInfo info){
//  Serial.printf("FirebaseStatus-> Token Info: type = %s, status = %s\n", getTokenType(info).c_str(), getTokenStatus(info).c_str());
// }
static const String sensorsValuesPath = "/sensorValues";
static const String envTempDBPath = "envTemperature";
static const String soilTempDBPath = "soilTemperature";
static const String humidityDBPath = "humidity";
static const String pHDBPath = "pH";
static const String overheadTankLevelDBPath = "overheadTankLevel";
static const String undergroundTankLevelDBPath = "undergroundTankLevel";
static const String rainfallValueDBPath = "rainfallValue";
static const String soilMoistureDBPath = "soilMoisture";
static const String solarPVCurrentDBPath = "solarPVCurrent";
static const String solarPVVoltageDBPath = "solarPVVoltage";
static const String waterPumpIsOnDBPath = "waterPumpIsOn";

bool pumpIsOn = false;

Firebase_RTD::Firebase_RTD(){}

void Firebase_RTD::initialize(void (*streamCallback)(MultiPathStreamData), void (*streamTimeoutCallback)(bool)){
  firebaseConfig.api_key = WEB_API_KEY;
  firebaseAuth.user.email = USER_EMAIL;
  firebaseAuth.user.password = USER_PASSWORD;
  firebaseConfig.database_url = DATABASE_URL; 
  // firebaseConfig.token_status_callback = firestoreTokenStatusCallback;
  if(debugFirebaseStatus) firebaseConfig.token_status_callback = tokenStatusCallback;
  
  Firebase.begin(&firebaseConfig,&firebaseAuth);
  Firebase.reconnectWiFi(true);

  //SinglePathStream
//  if (!Firebase.beginStream(stream, "/fromWebClient"))
//    Serial.printf("Firebase stream begin error, %s\n\n", stream.errorReason().c_str());
//  Firebase.setStreamCallback(stream, _streamCallback, _streamTimeoutCallback);

  // The MultiPathStream works as normal stream with the payload parsing function.
  if (!Firebase.beginMultiPathStream(stream, "/fromWebClient"))
    Serial.printf("Firebase stream begin error, %s\n\n", stream.errorReason().c_str());


  Firebase.setMultiPathStreamCallback(stream, streamCallback, streamTimeoutCallback);
  //About callbcaks in .cpp files -> Read bottom of file
}

  
///Multiple paths callback 
void Firebase_RTD::streamCallback(MultiPathStreamData stream,void (*pumpButtonTappedByUser)(bool)){
// MultiPathStreamEventCallback FirebaseData::_streamCallback(MultiPathStreamData stream){
  String lastUpdatedByEvent = "/lastUpdatedBy";
  String pumpButtonTappedEvent = "/pumpButtonTapped";

  String childPath[2] = {lastUpdatedByEvent, pumpButtonTappedEvent};
  String updatedBy = esp32ID;
  bool pumpButtonTapped;
  
  size_t numChild = sizeof(childPath) / sizeof(childPath[0]);
  for (size_t i = 0; i < numChild; i++){ 
    if (stream.get(childPath[i])){
      Serial.printf("Data path: %s, Data type: %s, Data value: %s, Event type: %s%s", 
        stream.dataPath.c_str(), stream.type.c_str(), stream.value.c_str(), stream.eventType.c_str(), i < numChild - 1 ? "\n" : "");
        
      if(stream.dataPath == lastUpdatedByEvent){
        if (stream.type == "string") updatedBy = stream.value;
      }else if(stream.dataPath == pumpButtonTappedEvent){
        if (stream.type == "boolean") pumpButtonTapped = stream.value == "true" ? true : false;
      }    
    }
  }

  if(updatedBy == esp32ID) return;
  //TODO: TURN PUMP OFF OR ON DEPENDING ON COMMAND RECEIVED

  Serial.println();
  // This is the size of stream payload received (current and max value)
  // Max payload size is the payload size under the stream path since the stream connected
  // and read once and will not update until stream reconnection takes place.
  // This max value will be zero as no payload received in case of ESP8266 which
  // BearSSL reserved Rx buffer size is less than the actual stream payload.
  Serial.printf("Received stream payload size: %d (Max. %d)\n\n", stream.payloadLength(), stream.maxPayloadLength());
  if(pumpButtonTapped == false && pumpIsOn) {
    pumpIsOn = false;
    Serial.println("/nPump turned off");
    pumpButtonTappedByUser(false);
  }
  else if(pumpButtonTapped == true && !pumpIsOn) {
    pumpIsOn = true;
    Serial.println("/nPump turned on");
    pumpButtonTappedByUser(true);
  }
  else Serial.println("/nERROR: Pump command unavailable");
}



void Firebase_RTD::updateSensorsValuesInRTD(
  String currentEnvTemperature,
  String currentSoilTemperature,
  String currentHumidity,
  String currentPH,
  String currentOverheadTankLevel,
  String currentUndergroundTankLevel,
  String currentRainfall,
  String solarPVCurrent,
  String solarPVVoltage
){
  if(_canSendDataToDB()){
    FirebaseJson json;
    json.add(envTempDBPath, currentEnvTemperature);
    json.add(soilTempDBPath, currentSoilTemperature);
    json.add(humidityDBPath, currentHumidity);
    json.add(pHDBPath, currentPH);
    json.add(overheadTankLevelDBPath, currentOverheadTankLevel);
    json.add(undergroundTankLevelDBPath, currentUndergroundTankLevel);
    json.add(rainfallValueDBPath, currentRainfall);
    json.add(solarPVCurrentDBPath, solarPVCurrent);
    json.add(solarPVVoltageDBPath, solarPVVoltage);

    ///Patching existing Node
    if (Firebase.updateNode(firebaseData, sensorsValuesPath, json)) {
      Serial.printf("RTD Patched %s\n", firebaseData.payload().c_str()); //printf bcoz of the 2 parameters. println accepts only 1
      Serial.printf("Data path %s\n", firebaseData.dataPath());
      Serial.printf("Data type %s\n", firebaseData.dataType());
      Serial.printf("JSON string %s\n", firebaseData.jsonString());
    } else {
      Serial.printf("Error patching RTD. %s\n",firebaseData.errorReason());
    }
    
    ///Append New Node
//    if (Firebase.pushJSON(firebaseData, "/fromWebClient", json)) {
//      Serial.printf("RTD Appended\n%s\n", firebaseData.payload().c_str()); //printf bcoz of the 2 parameters. println accepts only 1
//      Serial.printf("Data path\n%s\n", firebaseData.dataPath() + "  / "+ firebaseData.pushName());
//    } else {
//      Serial.println("Error Appending RTD. "+firebaseData.errorReason());
//    }
  }

}

void Firebase_RTD::updatePumpStateInRTD(bool turnPumpOn){
    if(!_canSendDataToDB()) return;
    FirebaseJson json;
    json.add(waterPumpIsOnDBPath, turnPumpOn); //TODO: Send current pump state

    ///Patching existing Node
    if (Firebase.updateNode(firebaseData, sensorsValuesPath, json)) {
      Serial.printf("RTD Patched %s\n", firebaseData.payload().c_str()); //printf bcoz of the 2 parameters. println accepts only 1
      Serial.printf("Data path %s\n", firebaseData.dataPath());
      Serial.printf("Data type %s\n", firebaseData.dataType());
      Serial.printf("JSON string %s\n", firebaseData.jsonString());
    } else {
      Serial.printf("Error patching RTD. %s\n",firebaseData.errorReason());
    }
}

void Firebase_RTD::streamTimeoutCallback(bool timeout){
// StreamTimeoutCallback FirebaseData::_streamTimeoutCallback(bool timeout){
//  On disconnecting from Firebase server,log for example
//  Stream timed out, resuming...
//  Http is not connected. Stream Error code: -3, reason: not connected
 if (timeout)  Serial.println("Stream timed out, resuming...\n");

 if (!stream.httpConnected())
   Serial.printf("Http is not connected. Stream Error code: %d, reason: %s\n\n", stream.httpCode(), stream.errorReason().c_str());
}


bool Firebase_RTD::_canSendDataToDB(){///C++ doesnt use get function
  return Firebase.ready();  
  //if esp32 is not connected to WiFi, could make this function not run courtesy to main.ino but not sure if firebase has data persistence in esp32
}


///Single path callback - Listen to only one field
//void streamCallback(StreamData data){
//  Serial.println("Accessing RTDB Stream..");
//  Serial.printf("Stream path, %s\nData path, %s\nData type, %s\nEvent type, %s\n\n",
//                data.streamPath().c_str(),
//                data.dataPath().c_str(),
//                data.dataType().c_str(),
//                data.eventType().c_str());
//  
//  Serial.println("Stream data is:");
//  printResult(data); // see addons/RTDBHelper.h
//  Serial.println();
//
 // This is the size of stream payload received (current and max value)
 // Max payload size is the payload size under the stream path since the stream connected
 // and read once will not update until stream reconnection takes place.
 // This max value will be zero as no payload received in case of ESP8266 which
 // BearSSL reserved Rx buffer size is less than the actual stream payload.
//  Serial.printf("Received stream payload size: %d (Max. %d)\n\n", data.payloadLength(), data.maxPayloadLength());
//}


//Callback functions in .cpp files work only if they are called by a static function e.g void setup n loop, so error below occurs
// Error: invalid use of non-static member function 'void Firebase_RTD::streamCallback(MultiPathStreamData)'
//So the callback function has been directed back to the main.ino file for it to call the callback function indirectly
//Also any custom class function called inside the callback function cant be called inside the cbk function. Has to be another cbk function to be called in main.ino
//e.g how updateSensorsValuesInRTD() is called by void streamCallback(MultiPathStreamData stream,void (*updateSensorsValuesInRTD)())
