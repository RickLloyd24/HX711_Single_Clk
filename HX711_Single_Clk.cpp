/*
//-------------------------------------------------------------------------------------
// HX711_Single_Clk.h
// Arduino library for HX711 24-Bit Analog-to-Digital Converter
// Created by Rick Lloyd February 2024
// Tested with      : HX711 module on channel A and 5kg load cell
// Tested with MCU  : Arduino Uno, Mega ESP32, ESP8266 
//-------------------------------------------------------------------------------------
*/

#include <Arduino.h>
#include "HX711_Single_Clk.h"


HX711O::HX711O (int SizeofArray)   					//constructor number of devices and size of array
{
	numDevices = SizeofArray;
}
 
void HX711O::begin(int clkpin, int outpin[], int Gain)  //Intialize pins, set Gain and powerUp HX711
{   
  ClkPin = clkpin;              
  if (numDevices > 8) numDevices = 8;
  if (numDevices < 1) numDevices = 1;
  for(int i = 0; i < numDevices; i++) {
	DataPins[i] = outpin[i];
  }	
  pinMode(ClkPin, OUTPUT);
  for (int i = 0; i < numDevices; i++) {
    pinMode(DataPins[i], INPUT);
  }
  Gain = 1;                     					//128, channel A
  if (Gain == 32) Gain = 2;    						//32, channel B
  if (Gain == 64) Gain = 3;    						//64, channel A                 
  digitalWrite(ClkPin, LOW);   						//powerUp HX711;
}

//void HX711::conversion24bit()                    //read 24 bit data, store in dataset and start the next conversion
void HX711O::getData(long data[]) {                //getData
  uint8_t dout;  boolean TimeOutFlag[8];
  
  if (numDevices > 8) numDevices = 8;
  if (numDevices < 1) numDevices = 1;

  for (int j = 0; j < numDevices; j++) {
    TimeOutFlag[j] = true;
    data[j] = 0;
    dout = digitalRead(DataPins[j]);                 //check if conversion is ready
    if (dout) {                                      
      TimeOutFlag[j] = false;                        //data is ready
    }
  }  
  
  for (uint8_t i = 0; i < (24 + Gain); i++) {   //read 24 bit data + set Gain and start next conversion
    digitalWrite(ClkPin, HIGH);
    delayMicroseconds(1);      
    digitalWrite(ClkPin, LOW);
    if (i < (24)) {
      for (int j = 0; j < numDevices; j++) {
        dout = digitalRead(DataPins[j]);
        data[j] = (data[j] << 1) | dout;
      }
    }  
    else {
      delayMicroseconds(1);    
    }
  }
  for (int j = 0; j < numDevices; j++) {
    data[j] = data[j] ^ 0x800000;                // flip the 24th bit 
    if (TimeOutFlag[j] = false) data[j] = -1;
  }
}