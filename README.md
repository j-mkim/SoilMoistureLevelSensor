# SoilMoistureLevelSensor
Components implemented in this project consists of: capacitive soil moisture sensor, water pump, Liquid Crystal Display (LCD), and Arduino Uno Rev 3. 

Arduino Uno Rev 3 was used to convert the analog data collected by the capacitive soil moisture sensor to a percentage using an algorithm. Along with data conversion, the Arduino was responsible for displaying various informations on the LCD, which includes the soil moisture level in percentage, as well as user-defined lower threshold. 

If the soil moisture level was below the threshold, the Arduino displayed a message on the LCD, which prompted the user that the soil moisture level is low. The Arduino also turned on the water pump, which supplied the soil with water until the minimum threshold was achieved. When the moisture level surpassed the minimum threshold, the Arduino turned off the water pump and displayed a message informing the user that the sufficient moisture level was achieved.
