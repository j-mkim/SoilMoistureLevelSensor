/*
 * The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
 */

// include the library code:
#include <LiquidCrystal.h>
#define SensorPin A0

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);              //Initialize the library with the numbers of the interface pins

//Define variables
float sensorValue = 0;                              //Initialize the value of the sensor to 0
double percentValue = 0;                            //Initialize the value of the percent to 0
int LEDPin = 13;                                    //Initialize Pin 13 for the LED
int waterPumpPin = 10;                              //Initialize Pin 10 for the water pump
int buttonState1 = 0;                               //Initialize buttonState1 to 0
int buttonState2 = 0;                               //Initialize buttonState2 to 0
int increase = 8;                                   //Initialize Pin 8 for increase button
int decrease = 7;                                   //Initialize Pin 7 for decrease button
double minThreshold = 50;                           //Minimum value of the soil level
double maxThreshold = minThreshold+35;              //Maximum value of the soil level

void setup() 
{
  Serial.begin(9600);
  lcd.begin(16,2);
  pinMode(LEDPin, OUTPUT);                          //LED Pin
  pinMode(waterPumpPin, OUTPUT);                    //Water Pump Pin
  pinMode(increase, INPUT);                         //Increase Pin
  pinMode(decrease, INPUT);                         //Decrease Pin
}

void loop() 
{
  sensorValue = analogRead(SensorPin);              //Read the data from the sensor
  Serial.print("\nAnalog Value: ");                 //Print the message on the serial port
  Serial.print(sensorValue);                        //Print the value on the serial port
  percentValue = map(sensorValue, 635, 316, 0, 100);//Converting value read from the sensor to percent value
  Serial.print("\nMoisture Level: ");               //Print the message on the serial port
  Serial.print(percentValue);                       //Print the value on the serial port
  Serial.print("%");                                //
  lcd.setCursor(0,0);                               //Setting the cursor on the LCD
  lcd.print("Moisture: ");                          //Print the message on the LCD
  lcd.print(percentValue);                          //Print the value on the LCD
  lcd.print("%");                                   //
  lcd.setCursor(0,1);                               //
  lcd.print("Low Thrshld: ");                       //Print the message on the LCD
  lcd.print(minThreshold);                          //Print the value of minimum threshold on the LCD
  delay(500);                                       //Wait
  configureThreshold();                             //Call configureThreshold function
  checkMoistureLevel(percentValue);                 //Call checkMoistureLevel function
}

void configureThreshold()                           //Function to configure the lower threshold
{
  buttonState1 = digitalRead(increase);             //Read the increase button's state
  buttonState2 = digitalRead(decrease);             //Read the decrease button's state
  if(buttonState1 == HIGH)                          //If the increase button's state is HIGH
    minThreshold+=1;                                //Increment the minimum threshold
  if(buttonState2 == HIGH)                          //If the decrease button's state is HIGH
    minThreshold-=1;                                //Decement the minimum thresohld
}

void checkMoistureLevel(double percentValue)        //Function to check the moisture level
{
  if(percentValue < minThreshold)                   //If the gathered data is lower than the minimum threshold
  {
    lcd.setCursor(20, 0);                           //Setting the cursor on the LCD
    lcd.print("Water level is low!");               //Display message on the LCD
    delay(1000);                                    //Wait
    digitalWrite(LEDPin, HIGH);                     //Turn LED on
    delay(50);                                      //Wait
    digitalWrite(LEDPin, LOW);                      //Turn LED off
    delay(50);                                      //Wait
    digitalWrite(waterPumpPin, HIGH);               //Turn on the pump  
  }
  
  if(percentValue > minThreshold)                   //If the gathered data is greater than the maximum threshold
  {
    lcd.setCursor(20, 0);                           //Setting the cursor on the LCD
    lcd.print("Sufficient moisture");               //Display message on the LCD
    lcd.setCursor(20, 5);                           //Setting the cursor on the LCD
    lcd.print("level is reached.");                 //Display message on the LCD
    delay(1000);                                    //Wait
    digitalWrite(LEDPin, LOW);                      //Turn LED off
    digitalWrite(waterPumpPin, LOW);                //Turn off the pump
  }
  lcd.clear();                                      //Clear LCD display
}
