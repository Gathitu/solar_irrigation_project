#include "WiFiManager.h"

WiFiMulti wifiMulti;
const char* wifiSSID = "";
const char* wifiPassword = "";
bool _connectedToWifi = false;
unsigned long wifiConnectionCheckPreviousMs = 0;

WiFiManager::WiFiManager(){}

void WiFiManager::init(){
  WiFi.mode(WIFI_AP_STA);
  wifiMulti.addAP("HOT","123456789");
  Serial.println("Connecting to Wifi...");
  if(wifiMulti.run() == WL_CONNECTED) _systemIsConnectedToWifi();
  else _systemIsDisconnectedFromWiFi();
}



///Returns true if ESP32 is connected to WiFi
void WiFiManager::checkWiFiConnection(unsigned long now){
  if(!_canCheckWiFiConnectionState(now)) return;
  
  int wStatus = wifiMulti.run();///255-No WiFi available; 3- Connected to a WiFi
  // Serial.printf("Connecting to WiFi Status => %s\n", String(wStatus));
  
  if (wStatus == WL_CONNECTED) _systemIsConnectedToWifi();
  else if(WiFi.status()!= WL_CONNECTED) _systemIsDisconnectedFromWiFi();
}

//Check if enough time has passed before a checking WiFi Connection State
bool WiFiManager::_canCheckWiFiConnectionState(unsigned long now){
  if(wifiConnectionCheckPreviousMs == 0){
    wifiConnectionCheckPreviousMs = now;
    return false;
  }else{
    unsigned long timePassed = now - wifiConnectionCheckPreviousMs;
    if (timePassed >= CheckWiFiConnectionStateInterval) { 
      wifiConnectionCheckPreviousMs = 0;                  
      return true;
    }
  }
  return false;
}


void WiFiManager::_systemIsConnectedToWifi(){
  //DONT LOG THESE REPEATEDLY AS THERE ARE INTERNAL ERRORS GOING ON WHICH ARENT BEING LOGGED
  if(!_connectedToWifi){
    Serial.println("\nConnected to WiFi: ");
    Serial.print(WiFi.SSID());
    Serial.println("IP address = ");
    Serial.println(WiFi.localIP()); //Dont log using concatenation as it will result in this error: 'Guru Meditation Error: Core  1 panic'ed (StoreProhibited). Exception wasGuru Meditation Error: Core  1 panic'ed (LoadProhibited)'
  }
  _connectedToWifi = true;
}

void WiFiManager::_systemIsDisconnectedFromWiFi(){
  if(_connectedToWifi) Serial.println(F("Could not connect to any WiFi"));
  _connectedToWifi = false;
}

bool WiFiManager::isConnectedToWifi(){
  return _connectedToWifi;
}