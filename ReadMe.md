# HX711 Single Clock

An Arduino library to interface the HX711 24-Bit Analog-to-Digital Converter (ADC)] for reading load cells / weight scales.  This is a very simple library that uses a single clock for all HX711 devices.  This reduces the number of pins required to work with multiple HX711 devices.

This library supports all the available features on the HX711.   Gain options are 128, 64, and 32.  Access to Channels A  and Channel B.  Sample rates up to 10 Samples per Second.  The library supports upto 8 HX711 devices.

## Code Overview

#include <HX711_Single_Clk.h>

#define number_of_HX711_devices 3

#define  ClockPin 25 

#define Gain 128

int ScaleInPins[] = {34, 35, 36};               //Processor Input Pins from Scale (maximum 8)

long ScaleReadings[number_of_HX711_devices]  //Array to hold HX711 readings

HX711O Scales(number_of_HX711_devices);   //constructor array size

Scales.begin(ClockPin, ScaleInPins, Gain);

Scales.getData(ScaleReadings);    // If time out occurs reading is -1

**See Example for more details**

## Hardware Sample

![](C:\Users\rickl\AppData\Roaming\marktext\images\2024-02-09-09-43-05-image.png)

## Hardware Support

This library should support all Arduino compatible boards.  It was tested on ESP32, ESP8266, Mega and Uno platforms.

## Similar libraries

There are other libraries around, enjoy:

- [GitHub - olkal/HX711_ADC: Arduino library for the HX711 24-bit ADC for weight scales](https://github.com/olkal/HX711_ADC)
