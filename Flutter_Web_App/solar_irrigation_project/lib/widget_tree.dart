import 'dart:async';
import 'package:firebase_core/firebase_core.dart';
import 'package:firebase_database/firebase_database.dart';
import 'package:flutter/foundation.dart';
import 'package:flutter/material.dart';

import 'package:solar_irrigation_project/responsive_layout.dart';
import 'package:solar_irrigation_project/screens/drawer.dart';
import 'package:solar_irrigation_project/screens/homepage/homepage.dart';
import 'package:solar_irrigation_project/util.dart';

class WidgetTree extends StatefulWidget {
  @override
  _WidgetTreeState createState() => _WidgetTreeState();
}

class _WidgetTreeState extends State<WidgetTree> {
  ///use nullables instead of late initializers as late promises to initialize this variable later but this promise doesn't mean a thing when using that variable inside the build method
  final database = FirebaseDatabase.instance;
  DatabaseReference? _esp32DatabaseRef;
  DatabaseReference? _webClientDatabaseRef;

  ///Firebase Real time database
  void initFirebaseRTD() async{
    _esp32DatabaseRef = database.ref('fromESP32');
    _webClientDatabaseRef = database.ref('fromWebClient');
    if(kReleaseMode) database.setLoggingEnabled(false);
    if (!kIsWeb) { //from package example in pub.dev
      database.setPersistenceEnabled(true);
      database.setPersistenceCacheSizeBytes(10000000);
    }
  }

  @override
  void initState() {
    super.initState();
    initFirebaseRTD();
  }

  @override
  //Called When Widget build method is called after initState or after a configuration(size) change
  void didChangeDependencies() {///Dependent widgets are rebuilt on changes in MaterialApp size/theme
    calculateSizeUtils(MediaQuery.of(context).size);
    super.didChangeDependencies();
  }

  static const String envTempDBPath = "envTemperature";
  static const String humidityDBPath = "humidity";
  static const String pHDBPath = "pH";
  static const String overheadTankLevelDBPath = "overheadTankLevel";
  static const String undergroundTankLevelDBPath = "undergroundTankLevel";
  static const String rainfallValueDBPath = "rainfallValue";
  static const String soilMoistureDBPath = "soilMoisture";
  static const String soilTempDBPath = "soilTemperature";
  static const String solarPVCurrentDBPath = "solarPVCurrent";
  static const String solarPVVoltageDBPath = "solarPVVoltage";
  static const String waterPumpIsOnDBPath = "waterPumpIsOn";

  @override
  Widget build(BuildContext context) {
    return StreamBuilder<DatabaseEvent>(
      stream: _esp32DatabaseRef?.onValue,
      builder: (context, snapshot) {
        final dataSnapshot = snapshot.data?.snapshot;
        if(snapshot.hasData) {
          customLog("Data Present");
          // customLog("${dataSnapshot?.child(envTempDBPath).value}");
        }
        else customLog("Data Absent");

        Widget homePageWidget = HomePage(
          webClientDatabaseRef: _webClientDatabaseRef,
          envTemperature: dataSnapshot?.child(envTempDBPath).value,
          humidity: dataSnapshot?.child(humidityDBPath).value,
          pHValue: dataSnapshot?.child(pHDBPath).value,
          rainfallValue: dataSnapshot?.child(rainfallValueDBPath).value,
          soilMoisture: dataSnapshot?.child(soilMoistureDBPath).value,
          soilTemperature: dataSnapshot?.child(soilTempDBPath).value,
          solarPVCurrent: dataSnapshot?.child(solarPVCurrentDBPath).value,
          solarPVVoltage: dataSnapshot?.child(solarPVVoltageDBPath).value,
          overheadTankLevel: dataSnapshot?.child(overheadTankLevelDBPath).value,
          undergroundTankLevel: dataSnapshot?.child(undergroundTankLevelDBPath).value,
          waterPumpIsOn: dataSnapshot?.child(waterPumpIsOnDBPath).value,
        );


        return Scaffold(
          appBar: PreferredSize(
            preferredSize: Size(double.infinity, titleTextSize*1.8),
            child: Container(
              color: Colors.black,
              alignment: Alignment.center,
              child: Text("Beyond Grades Solar Irrigation",style: TextStyle(fontSize: titleTextSize,color: Colors.white),)),
          ),
          body: ResponsiveLayout(
            tiny: Container(),
            phone: Container(),
            tablet: Container(),
            largeTablet: homePageWidget,
            computer: homePageWidget,
          ),
          drawer: DrawerPage(),
        );
      }
    );
  }
}


class DataFromEsp32 {
  double solarPVVoltage;
  double solarPVCurrent;
  double pHValue;
  double humidity;
  double soilMoisture;
  double rainfallValue;
  double soilTemperature;
  double envTemperature;
  double overheadTankLevel;
  double undergroundTankLevel;

  DataFromEsp32({
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
  });
}
