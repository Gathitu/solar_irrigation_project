import 'dart:math';
import 'dart:ui';

import 'package:fl_chart/fl_chart.dart';
import 'package:flutter/material.dart';
import 'package:solar_irrigation_project/constants.dart';
import 'package:solar_irrigation_project/util.dart';
import 'package:solar_irrigation_project/utils/tuple.dart';


class CustomLineChart extends StatefulWidget {
  @override
  _CustomLineChartState createState() => _CustomLineChartState();
}

class _CustomLineChartState extends State<CustomLineChart> {
  List<Color> gradientColors = [
    const Color(0xff23b6e6),
    const Color(0xff02d39a),
  ];

  //eleven_eleven -> 11th November 
  Tuple7<List<FlSpot>,List<double>,List<double>,double,double,double,double>? eleven_eleven_tuple;

  @override
  void didChangeDependencies() {
    setGraphVariables();
    super.didChangeDependencies();
  }
  
  @override
  void didUpdateWidget(covariant CustomLineChart oldWidget) {
    setGraphVariables();
    super.didUpdateWidget(oldWidget);
  }



  void setGraphVariables(){
    //eleven_eleven -> 11th November 
    List<FlSpot> eleven_eleven_graphVariables = <FlSpot>[];
    eleven_eleven_graphVariables.addAll([
      FlSpot(0, 14.5),
      FlSpot(1, 14.5),
      FlSpot(2, 14.0),
      FlSpot(3, 13.2),
      FlSpot(4, 13.5),
      FlSpot(5, 13.0),
      FlSpot(6, 12.0),
      FlSpot(7, 11.0),
      FlSpot(8, 10.0),
      FlSpot(9, 9.0),
      FlSpot(10, 7.0),
      FlSpot(11, 6.8),
      FlSpot(12, 4.2),
      FlSpot(13, 4.3),
      FlSpot(14, 4.2),
      FlSpot(15, 5.0),
      FlSpot(16, 6.0),
      FlSpot(17, 7.0),
      FlSpot(18, 8.0),
      FlSpot(19, 9.0),
      FlSpot(20, 10.0),
      FlSpot(21, 12.0),
      FlSpot(22, 13.0),
      FlSpot(23, 14.0),
    ]);
    
    List<double> xAxisValues = <double>[];
    List<double> yAxisValues = <double>[];

    for(FlSpot graphSet in eleven_eleven_graphVariables){
      xAxisValues.add(graphSet.x);
      yAxisValues.add(graphSet.y);
    }
    double xValuesMin = xAxisValues.reduce(min);
    double xValuesMax = xAxisValues.reduce(max);
    double yValuesMin = 0.0;
    double yValuesMax = yAxisValues.reduce(max)*2;

    eleven_eleven_tuple = Tuple7<List<FlSpot>,List<double>,List<double>,double,double,double,double>(
      eleven_eleven_graphVariables,xAxisValues,yAxisValues,xValuesMin,xValuesMax,yValuesMin,yValuesMax);

  }


  @override
  Widget build(BuildContext context) {
    final double graphHeight = screenHeight*0.74;
    return Stack(
      children: [
        Align(
          alignment: Alignment.bottomLeft,
          child: Container(
            width: screenWidth,
            height: graphHeight,
            alignment: Alignment.centerLeft,
            // color: Colors.red,
            padding: EdgeInsets.only(left: screenWidth*0.03,top: screenHeight*0.2),
            child: Transform.rotate(
              angle: -pi / 2,
              alignment: Alignment.centerLeft,
              child: Text("Soil Humidity",
              style: textStyleInLBg?.copyWith(fontSize: subHeadingTextSize,fontWeight: FontWeight.w600)),
            ),
          ),
        ),

        Padding(
          padding: EdgeInsets.only(left: screenWidth*0.035,right: kPadding*1.5),
          child: Stack(
            children: [
              Align(
                alignment: Alignment.topCenter,
                child: Text("Humidity Readings on 11/11/2022",
                style: textStyleInLBg?.copyWith(fontSize: headingTextSize,fontWeight: FontWeight.w800)),
              ),
              Align(
                alignment: Alignment.topCenter,
                child: Padding(
                  padding: EdgeInsets.only(top: (graphHeight*1.06)),
                  child: Text("Time (Hours)",
                  style: textStyleInLBg?.copyWith(fontSize: subHeadingTextSize,fontWeight: FontWeight.w600)),
                ),
              ),
              Padding(
                padding: EdgeInsets.only(top: headingTextSize*1.2),
                child: Card(
                  color: Colors.black,
                  // color:Constants.purpleLight
                  shape: RoundedRectangleBorder(borderRadius: BorderRadius.circular(kBorderRadius)),
                  elevation: 3,
                  child: Container(
                    width: screenWidth,
                    height: graphHeight,
                    decoration: BoxDecoration(
                      borderRadius: BorderRadius.all(
                        Radius.circular(kBorderRadius),
                      ),
                    ),
                    child: LineChart(graphData(eleven_eleven_tuple)),
                  ),
                ),
              ),
            ],
          ),
        ),
      
      ],
    );
  }

  LineChartData graphData(Tuple7<List<FlSpot>,List<double>,List<double>,double,double,double,double>? tuple) {
    return LineChartData(
      gridData: FlGridData(
        show: true,
        drawVerticalLine: true,
        getDrawingHorizontalLine: (value) {
          return FlLine(
            color: Colors.white10,
            strokeWidth: 1,
          );
        },
        getDrawingVerticalLine: (value) {
          return FlLine(
            color: Colors.white10,
            strokeWidth: 1,
          );
        },
      ),
      titlesData: FlTitlesData(
        show: true,
        bottomTitles: SideTitles(
          showTitles: true,
          getTextStyles: (context,value) => const TextStyle(
              color: Color(0xff68737d),
              fontWeight: FontWeight.bold,
              fontSize: 16),
          getTitles: (value) {
            if(value<10){
              return '0$value';
            }
            else {
              return '$value';
            }
          },
          reservedSize: kPadding*4,
          margin: kPadding, //margin b2n text and graph line
        ),
        leftTitles: SideTitles(
          showTitles: true,
          getTextStyles: (context,value) => const TextStyle(
            color: Color(0xff67727d),
            fontWeight: FontWeight.bold,
            fontSize: 15,
          ),
          getTitles: (value) {
            int v = value.toInt();
            if((v%2) == 0) {///if v is even, show the value
              return '$v';
            } else {
              return '';
            }
          },
          reservedSize: kPadding*4,
          margin: kPadding, //margin b2n text and graph line
        ),
      ),
      borderData: FlBorderData(
          show: false,
          border: Border.all(color: const Color(0xff37434d), width: 1)),
      minX: tuple?.item4,
      maxX: tuple?.item5,
      minY: tuple?.item6,
      maxY: tuple?.item7,
      lineBarsData: [
        LineChartBarData(
          spots: tuple?.item1,
          isCurved: true,
          colors: gradientColors,
          // color: Colors.blue,
          barWidth: kPadding*0.5,
          isStrokeCapRound: true,
          dotData: FlDotData(
            show: false,
          ),
          belowBarData: BarAreaData(
            show: true,
            // color: Colors.grey,
            colors:
                gradientColors.map((color) => color.withOpacity(0.3)).toList(),
          ),
        ),
      ],
    );
  }

}
