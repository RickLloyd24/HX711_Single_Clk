/*
//-------------------------------------------------------------------------------------
// HX711_Single_Clk.h
// Arduino library for HX711 24-Bit Analog-to-Digital Converter
// Created by Rick Lloyd February 2024
// Tested with      : HX711 module on channel A and 5kg load cell
// Tested with MCU  : Arduino Uno, Mega ESP32, ESP8266 
//-------------------------------------------------------------------------------------
*/

#ifndef HX711_Single_Clk_h
#define HX711_Single_Clk_h

#include "Arduino.h"

class HX711O
{
  public:
	HX711O(int SizeofArray); 		                	//constructor
	void begin(int clkpin, int outpin[], int gain);	                //HX711 clock pin, output pin and gain
	void getData(long data[]);				        //if TimeOut occurs data set to -1
  private:
	uint8_t ClkPin; 						//HX711 Clock pin
	uint8_t DataPins[8]; 						//HX711 Outout pins
	uint8_t Gain;							//HX711 GAIN
	int numDevices;                                                 //Number of HX711 devices and size of array
};

#endif