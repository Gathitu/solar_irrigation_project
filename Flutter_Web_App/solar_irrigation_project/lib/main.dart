import 'package:flutter/material.dart';
import 'package:solar_irrigation_project/constants.dart';
import 'package:solar_irrigation_project/util.dart';
import 'package:solar_irrigation_project/widget_tree.dart';
import 'package:firebase_core/firebase_core.dart';
import 'firebase_options.dart';

void main() async{
  WidgetsFlutterBinding.ensureInitialized();
  await Firebase.initializeApp(
    options: DefaultFirebaseOptions.currentPlatform,
  );
  runApp(MyApp());
}

class MyApp extends StatelessWidget {
  // final Future<FirebaseApp>_firebaseInit = Firebase.initializeApp();
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      debugShowCheckedModeBanner: false,
      title: 'Solar Irrigation Project',
      theme: ThemeData(
          scaffoldBackgroundColor: Colors.white24,
          primarySwatch: Colors.blue,
          canvasColor: Colors.white24,//applies e.g in the chips of listTiles
          ),
      home: WidgetTree(),
      // home: FutureBuilder(
      //   future: _firebaseInit,
      //   builder: (context, snapshot) {
      //     if(snapshot.connectionState == ConnectionState.done){
      //       return WidgetTree();
      //     }
      //     if(snapshot.hasError) customLog("Firebase Init Error"+snapshot.error.toString());
      //     return const CircularProgressIndicator();
      //   }
      // ),
    
    );
    
  }
}

