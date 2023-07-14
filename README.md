The project's purpose was to automate a solar irrigation plant. 
It involved:
- Designing a custom ESP32-WROOM-32 microcontroller-based Printed Circuit Board(PCB) that could be easily connected to pH, moisture, temperature, humidity, voltage and current sensors.
- Designing of an electrical circuit that used a MPTT(Solar Charge) controller to charge a 12V Li-Po Battery power and power the PCB from power received from solar panels.
- Writing of C++ firmware that would be uploaded to the ESP32 chip in the PCB and carry out reading and storage of sensor values.
- Developing a web application using Dart; whose purpose was to monitor and performing data analytics on the irrigation plant’s sensor readings.
- Integration of Firebase database in the ESP32 and in the web application.


A pdf containing the PCB Design Schematic:
[Schematic_PDF](/Solar_Irrigation_PCB/Schematic_PDF/Solar_Irrigation_PCB.pdf)

A snip of the web application UI:

![Web application Snipp](/Flutter_Web_App/WebsiteSnip.png)


