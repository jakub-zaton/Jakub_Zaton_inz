#ifndef HARDWARE_MANAGMENT_HH
#define HARDWARE_MANAGMENT_HH

#include "FreeRTOS.h"
#include <SPI.h>

struct SoftwareToolsManagment{
  TaskHandle_t loraTask;
  // TaskHandle_t sdTask;
  TaskHandle_t dataTask;
  TaskHandle_t rxHandlingTask;
  //... inne taski
  // QueueHandle_t sdQueue;
  QueueHandle_t loraTxQueue;
  QueueHandle_t loraRxQueue;
  SemaphoreHandle_t spiMutex;

  SPIClass spi = SPIClass(VSPI);
};


#endif