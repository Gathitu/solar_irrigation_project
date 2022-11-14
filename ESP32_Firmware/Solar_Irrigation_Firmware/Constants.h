#pragma once
#ifndef Constants_h
#define Constants_h

#define DHT_TYPE DHT22
#define DHT_PIN 4 
#define TRIG_PIN_UTL 5  //Trigger pin of Underground Tank Level sensor
#define ECHO_PIN_UTL 6  //Trigger pin of Overhead Tank Level sensor
#define TRIG_PIN_OTL 17  //Trigger pin of Underground Tank Level sensor
#define ECHO_PIN_OTL 18  //Trigger pin of Overhead Tank Level sensor
#define RAINFALL_SENSE 7  //Rainfall sensor digital pin
#define RAINFALL_SENSE_ANALOGUE 13  //Rainfall sensor analogue pin
#define MOISTURE_SENSE_ANALOGUE 0  
#define PH_SENSE_ANALOGUE 14  //pH sensor analogue pin

//in ms
static const unsigned long VSensePinReadInterval = 60000; //Solar PV Voltage Sensor; 1 minutes
static const unsigned long ISensePinReadInterval = 60000; //Solar PV Currrent Sensor; 1 minutes
static const unsigned long MSensePinReadInterval = 300000; //Moisture Sensor; 5 minutes
static const unsigned long TSensePinReadInterval = 300000; //Soil Temp Sensor; 5 minutes
static const unsigned long T_DHT_SensePinReadInterval = 300000; //Env Temp Sensor(DHT); 5 minutes
static const unsigned long HSensePinReadInterval = 300000; //Env Humidity Sensor(DHT); 5 minutes
static const unsigned long PHSensePinReadInterval = 300000; //Soil pH Sensor; 5 minutes
static const unsigned long RSensePinReadInterval = 300000; //Rainfall Sensor; 5 minutes
static const unsigned long L_O_SensePinReadInterval = 1000; //Ultrasonic Level Sensor 4 Overhead tank; 1 second
static const unsigned long L_U_SensePinReadInterval = 1000; //Ultrasonic Level Sensor 4 Underground tank; 1 second
static const unsigned long CheckWiFiConnectionStateInterval = 1000; //Ultrasonic Level Sensor 4 Underground tank; 1 second

#endif 


///TODO: CHECK MEMORY CONSERVATION WAY OF DECLARING CONSTANTS SO THAT THEY HAVE A PERMANENT ADDRESS NO MATTER HOW MANY TIMES CALLED

