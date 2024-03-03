//-------------------------------------------------------------------------------------
// HX711SingleClk.h
// Arduino library for HX711 24-Bit Analog-to-Digital Converter
// Created by Rick Lloyd February 2024
// Tested with      : HX711 module on channel A and 5kg load cell
// Tested with MCU  : Arduino Uno, Mega ESP32, ESP8266 
//-------------------------------------------------------------------------------------
// This is an example sketch on how to use this library for two HX711 modules as Weight scales

#include <HX711_Single_Clk.h>

//pins:
#define numscales 2                           //Number of scales in this example
int ScaleClkPin = 25;                         //Processor Clock Pin  
int ScaleInPins[] = {34, 35};                 //Processor Input Pins from Scale (maximum 8)
int Gain = 128;                               //Gain options are 128, 64, 32 (Gain of 32 uses Channel B)
long ScaleReadings[2];                        //Array to hold HX711 readings
unsigned long ReadTime = 2000;

HX711O Scales(numscales);                     //constructor number of devices and size of array passed

void setup() {
/* Setup Serial Ports */
  Serial.begin(115200);
  delay(500);                                               // avoid garbage into the UART
  Serial.write("\r\n\nReset\r\n");
  Serial.println();
  Serial.println("Starting...");
  Scales.begin(ScaleClkPin, ScaleInPins, Gain);             //Intialize the Scales and set the gain
  delay(400);                                               // Scale is not ready to read for 400 ms
  Serial.println("Startup is complete");
}

void loop() {
  unsigned long curtime = millis();
  
  if (curtime > ReadTime) {                                                     
    ReadTime = curtime + 3000;                    //Scale should not be read more often than 1 per second                              
    Scales.getData(ScaleReadings);
    Serial.print("Scale Readings: ");
    Serial.printf("%8d %8d", ScaleReadings[0], ScaleReadings[1]);
    Serial.println();
  }
}
