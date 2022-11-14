import 'package:firebase_database/firebase_database.dart';
import 'package:flutter/material.dart';
import 'package:solar_irrigation_project/constants.dart';
import 'package:solar_irrigation_project/screens/homepage/charts.dart';
import 'package:solar_irrigation_project/util.dart';



class HomePage extends StatefulWidget {
  final DatabaseReference? webClientDatabaseRef;
  final Object? solarPVVoltage;
  final Object? solarPVCurrent;
  final Object? pHValue;
  final Object? humidity;
  final Object? soilMoisture;
  final Object? rainfallValue;
  final Object? soilTemperature;
  final Object? envTemperature;
  final Object? overheadTankLevel;
  final Object? undergroundTankLevel;
  final Object? waterPumpIsOn;
  
  const HomePage({
    Key? key,
    required this.solarPVVoltage,
    required this.solarPVCurrent,
    required this.pHValue,
    required this.humidity,
    required this.soilMoisture,
    required this.rainfallValue,
    required this.soilTemperature,
    required this.envTemperature,
    required this.overheadTankLevel,
    required this.undergroundTankLevel, 
    required this.waterPumpIsOn, 
    required this.webClientDatabaseRef,
  }) : super(key: key);
  
  @override
  _HomePageState createState() => _HomePageState();
}

class _HomePageState extends State<HomePage> {
  List<SensorPresentValues> sensorPresentValues = <SensorPresentValues>[];

 @override
  void didChangeDependencies() {//When Widget build method is called after initState or after a configuration(size) change
    updateSensorReadings();
    super.didChangeDependencies();
  }
  
  @override
  void didUpdateWidget(covariant HomePage oldWidget) {//if parent widgets rebuilds
    updateSensorReadings();
    super.didUpdateWidget(oldWidget);
  }
  
  void updateSensorReadings(){
    sensorPresentValues.clear();
    sensorPresentValues.add(SensorPresentValues(variable: "Solar PV Voltage", units: "(in Volts)", sensorValue: widget.solarPVVoltage.toString()));
    sensorPresentValues.add(SensorPresentValues(variable: "Solar PV Current", units: "(in Amperes)", sensorValue: widget.solarPVCurrent.toString()));
    sensorPresentValues.add(SensorPresentValues(variable: "Farm Temperature", units: "(in °C)", sensorValue: widget.solarPVCurrent.toString()));
    sensorPresentValues.add(SensorPresentValues(variable: "Soil Temperature", units: "(in °C)", sensorValue: widget.soilTemperature.toString()));
    sensorPresentValues.add(SensorPresentValues(variable: "Soil Humidity", units: "(in g.m-3)", sensorValue: widget.soilTemperature.toString()));
    sensorPresentValues.add(SensorPresentValues(variable: "Soil Moisture", units: "(X%)", sensorValue: widget.soilTemperature.toString()));
    sensorPresentValues.add(SensorPresentValues(variable: "Rainfall Amount", units: "(in mm)", sensorValue: widget.soilTemperature.toString()));
    sensorPresentValues.add(SensorPresentValues(variable: "pH", units: "(logarithmic units)", sensorValue: widget.soilTemperature.toString()));
    sensorPresentValues.add(SensorPresentValues(variable: "Overhead Tank Water Level", units: "(in metres)", sensorValue: widget.soilTemperature.toString()));
    sensorPresentValues.add(SensorPresentValues(variable: "Underground Tank Water Level", units: "(in metres)", sensorValue: widget.soilTemperature.toString()));
  }

  @override
  Widget build(BuildContext context) {
    final pumpSectionHeight = screenHeight*0.11;
    bool waterPumpIsOn = widget.waterPumpIsOn == true;

    return Scaffold(
      body: Stack(
        children: [
            // Container(
            //   color: Constants.purpleLight,
            //   width: 50,
            //   child: Container(
            //     decoration: BoxDecoration(
            //       color: Constants.purpleDark,
            //       borderRadius: BorderRadius.only(
            //         topLeft: Radius.circular(50),
            //       ),
            //     ),
            //   ),
            // ),
          SingleChildScrollView(
            child: Padding(
              padding: EdgeInsets.only(
                  left: kPadding,
                  right: kPadding,
                  top: kPadding,
                  bottom: kPadding,
              ),
              child: Column(
                children: [
                  Align(
                    alignment: Alignment.topRight,
                    child: Container(
                      height: pumpSectionHeight,
                      width: screenWidth*0.19,
                      child: Column(
                        children: [
                          Container(
                              alignment: Alignment.topCenter,
                              // padding: EdgeInsets.only(right:screenWidth*0.09),
                              child: Padding(
                                padding: EdgeInsets.symmetric(horizontal: screenWidth*0.03),
                                child: Row(
                                  mainAxisAlignment: MainAxisAlignment.spaceBetween,
                                  children: [
                                    Text("Pump State", style: textStyleInLBg?.copyWith(fontWeight: FontWeight.w500)),
                                    Text(
                                      waterPumpIsOn ? "ON": "OFF",
                                      style: textStyleInLBg?.copyWith(
                                        color: waterPumpIsOn ? Colors.green :Colors.red,
                                        fontWeight: FontWeight.w600
                                      )),
                                  ],
                                ),
                              ),
                            ),
                          Align(
                            alignment: Alignment.topRight,
                            child: Card(
                              color: Colors.black,
                              elevation: 3,
                              shape: RoundedRectangleBorder(
                                  borderRadius: BorderRadius.circular(kBorderRadius)),
                              child: SwitchListTile.adaptive(
                                title: Text("Water Pump", style: textStyleInDBg,),
                                value: waterPumpIsOn,
                                onChanged: (newValue)async {
                                  String log = "Turning pump ";
                                  newValue ? log+= "ON" : log+= "OFF";
                                  customLog(log);
                                  try{
                                    await widget.webClientDatabaseRef?.update({
                                      // 'pumpButtonTapped': !waterPumpIsOn,
                                      'pumpButtonTapped': newValue,
                                      'lastUpdatedBy': webClientID,
                                    }).then((value) {
                                      customLog("Updated Pump State in Firebase RTD");
                                    });
                                  }catch(e){ customLog("Firebase ERROR when updating WebClientData"+ e.toString()); }
                                },
                              ),
                            ),
                          ),
                        ],
                      ),
                    ),
                  ),
                  Row(
                    crossAxisAlignment: CrossAxisAlignment.start,
                    children: [
                      Column(
                        children: List.generate(
                            sensorPresentValues.length,
                            (index)=> SensorPresentValuesCardWidget(
                              variable: sensorPresentValues[index].variable, 
                              units: sensorPresentValues[index].units,
                              sensorValue: sensorPresentValues[index].sensorValue
                            ),
                          )
                      ),
                      Expanded(child: CustomLineChart()),
                    ],
                  ),
                ],
              ),
            ),
          ),
        ],
      ),
    );
  }

}


class SensorPresentValues {
  String variable;
  String units;
  String sensorValue;
  SensorPresentValues({
    required this.variable,
    required this.units,
    required this.sensorValue,
  });
}

class SensorPresentValuesCardWidget extends StatelessWidget {
  final String variable;
  final String units;
  final String sensorValue;

  const SensorPresentValuesCardWidget({
    Key? key, 
    required this.variable, 
    required this.units, 
    required this.sensorValue,
    }) : super(key: key);

  @override
  Widget build(BuildContext context) {
    final sensorValuesCardWidth = 0.3*screenWidth;

    return GestureDetector(
      onTap: (){},
      child: Card(
        color: Colors.black,
        elevation: 3,
        shape: RoundedRectangleBorder(
          borderRadius: BorderRadius.circular(50),
        ),
        child: Container(
          width: sensorValuesCardWidth,
          child: ListTile(
            //leading: Icon(Icons.monetization_on),
            title: Text(variable,
              style: textStyleInDBg,
            ),
            subtitle: Text(units,
              style: textStyleInDBg?.copyWith(fontSize: tinyTextSize),
            ),
            trailing: Chip(
              label: Text(sensorValue,
                style: textStyleInDBg,
              ),
              // backgroundColor: Colors.black26,
            ),
          ),
        ),
      ),
    );
  }
}