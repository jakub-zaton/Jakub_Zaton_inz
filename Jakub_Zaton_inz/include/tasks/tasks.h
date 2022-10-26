#ifndef TASKS_HH
#define TASKS_HH
#include "../structs/SoftToolsManagment.h"
#include "../config/pinout.h"
#include "LoRa.h"
#include "../config/config.h"
#include "../components/SDcard.h"
#include <HX711_ADC.h>
#include "../components/hx711.h"
#include "../structs/commStructs.h"

extern SoftwareToolsManagment stm;
extern Hx711 rckWeight;
extern Hx711 tankWeight;


//pro_cpu
void loraTask(void *arg);
void rxHandlingTask(void *arg);


//app_cpu
// void sdTask(void *arg);
void dataTask(void *arg);

#endif