#ifndef TANWA_CONFIG_H
#define TANWA_CONFIG_H

#include <Arduino.h>

//#define __DEBUG

#ifdef __DEBUG
  #define DEBUGL(x) Serial.println(x)
  #define DEBUG(x) Serial.print(x)
#else
  #define DEBUGL(x) {}
  #define DEBUG(x) {}
#endif

//RTOS QUEUE
#define SD_FRAME_SIZE 256
#define SD_QUEUE_LENGTH 10
#define LORA_TX_FRAME_SIZE 256
#define LORA_TX_QUEUE_LENGTH 10

#define LORA_RX_QUEUE_LENGTH 10
#define LORA_RX_FRAME_SIZE 512
#define DATA_PREFIX "R4T;"

//SD FILE PATH
static String dataFileName= "/data_";


#define LORA_FREQ_MHZ 867    //927

//WEIGHTING
#define BIT_TO_GRAM_RATIO_RCK 53.13
#define BIT_TO_GRAM_RATIO_TANK 37.78// USA 32.73
#define OFFSET_TANK 1
#define STABILIZNG_TIME 4000

#endif