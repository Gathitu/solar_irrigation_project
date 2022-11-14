import 'package:flutter/foundation.dart';
import 'package:flutter/material.dart';
import 'package:solar_irrigation_project/constants.dart';

//Path for Firebase Real-Time Database
String webClientID = "WebClient";

void customLog(String logString){
  if (kDebugMode) {
    print(logString);
  }
}

//Calculated and set when app initializes
double kPadding = 20.0;
double kBorderRadius = 20.0;
double screenWidth = 500.0;
double screenHeight = 900.0;
double normalTextSize = 10.0;
double subHeadingTextSize = 15.0;
double headingTextSize = 20.0;
double titleTextSize = 40.0;
double tinyTextSize = 8.0;

void calculateSizeUtils(Size size){
  screenWidth = size.width;
  screenHeight = size.height;
  // customLog("Size of screen is "+size.toString());
  double refSize = screenHeight;
  if(screenWidth < screenHeight) refSize = screenWidth;
  kPadding = refSize*0.01;
  kBorderRadius = refSize*0.03;
  normalTextSize = refSize*0.02; 
  subHeadingTextSize = normalTextSize * 1.2;
  headingTextSize = normalTextSize * 1.4;
  titleTextSize = normalTextSize * 2.0;
  tinyTextSize = normalTextSize * 0.75;


}

//get functions are better than adding didChangeDependencies in all widget classes
TextStyle? get textStyleInLBg => TextStyle(fontSize: normalTextSize,color: Constants.purpleLight);//in a Light background
TextStyle? get textStyleInDBg => TextStyle(fontSize: normalTextSize,color: Colors.white);//in a Dark background
