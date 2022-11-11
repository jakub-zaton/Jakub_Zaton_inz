#ifndef TASKS_HH
#define TASKS_HH
#include "../structs/SoftToolsManagment.h"
#include "../config/pinout.h"
#include "LoRa.h"
#include "../config/config.h"
#include "../components/SDcard.h"
// #include <HX711_ADC.h>
#include "HX711.h"
#include "../components/hx711.h"
#include "../include/components/AD7780.h"
#include "../structs/commStructs.h"

extern SoftwareToolsManagment stm;


extern HX711 ADC1_Sparkfun;
extern HX711 ADC2_China;
extern AD7780 ADC3_AD;


//pro_cpu
void loraTask(void *arg);
void rxHandlingTask(void *arg);


//app_cpu
// void sdTask(void *arg);
void dataTask(void *arg);

#endif