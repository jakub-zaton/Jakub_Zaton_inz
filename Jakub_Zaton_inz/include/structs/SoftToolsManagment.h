#ifndef HARDWARE_MANAGMENT_HH
#define HARDWARE_MANAGMENT_HH

#include "FreeRTOS.h"
#include <SPI.h>
#include <Wire.h>

struct SoftwareToolsManagment{
  TaskHandle_t loraTask;
  TaskHandle_t sdTask;
  TaskHandle_t dataTask;
  TaskHandle_t stateTask;
  TaskHandle_t buzzerTask;
  TaskHandle_t rxHandlingTask;
  //... inne taski
  QueueHandle_t sdQueue;
  QueueHandle_t loraTxQueue;
  QueueHandle_t loraRxQueue;
  QueueHandle_t espNowRxQueue;

  SemaphoreHandle_t i2cMutex;
  SemaphoreHandle_t spiMutex;

  TwoWire i2c = TwoWire(0);
  SPIClass spi = SPIClass(VSPI);
};


#endif