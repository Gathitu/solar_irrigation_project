#pragma once
#ifndef WiFiManager_h
#define WiFiManager_h

#include <WiFi.h>
#include <WiFiMulti.h>
#include "Constants.h"

class WiFiManager{
  public:
    WiFiManager();
    void init();
    void checkWiFiConnection(unsigned long now);
    bool isConnectedToWifi();

  private:
    void _systemIsConnectedToWifi();
    void _systemIsDisconnectedFromWiFi();  
    bool _canCheckWiFiConnectionState(unsigned long now);  

};

#endif