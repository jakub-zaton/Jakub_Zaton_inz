#ifndef PINOUT_H
#define PINOUT_H

#include "FreeRTOS.h"
#include "Arduino.h"

//LORA
#define LORA_D0 39
#define LORA_CS 5
#define LORA_RS 4

//HX711 Sparkfun
#define HX1_SDA 15
#define HX1_SCL 2

//HX711 chinol
#define HX2_SDA 14
#define HX2_SCL 12

//AD7780
#define AD_SCLK 32
#define AD_DOUT 33
#define AD_NPDRST 25

//SPI
#define SPI_MOSI 23
#define SPI_MISO 19
#define SPI_SCK 18

#define TX 1
#define RX 3

//BT jumper
#define BT_JUMP 16

//BOOT
#define BOOT 0 

//Voltage measure
#define VOLTAGE_MEASURE 34

float voltageMeasure(uint8_t batteryPin);
void pinInit();

#endif