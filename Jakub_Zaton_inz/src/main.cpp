#include <Arduino.h>
#include <SPI.h>
#include "../include/tasks/tasks.h"
#include "../include/config/config.h"
#include "../include/structs/SoftToolsManagment.h"
#include "../include/structs/commStructs.h"
#include <esp_wifi.h>


SoftwareToolsManagment stm;
// HX711
Hx711 rckWeight(HX1_SDA, HX1_SCL);
Hx711 tankWeight(HX2_SDA, HX2_SCL);

void setup() {

  Serial.begin(115200);
  pinInit();


  stm.spi.begin();
  

  // stm.sdQueue = xQueueCreate(SD_QUEUE_LENGTH, sizeof(char[SD_FRAME_SIZE]));
  stm.loraTxQueue = xQueueCreate(LORA_TX_QUEUE_LENGTH, sizeof(char[LORA_TX_FRAME_SIZE]));
  stm.loraRxQueue = xQueueCreate(LORA_RX_QUEUE_LENGTH, sizeof(char[LORA_RX_FRAME_SIZE]));

  vTaskDelay(25 / portTICK_PERIOD_MS);

  xTaskCreatePinnedToCore(loraTask, "LoRa task", 20000, NULL, 3, &stm.loraTask, PRO_CPU_NUM);
  xTaskCreatePinnedToCore(rxHandlingTask, "Rx handling task", 20000, NULL, 2, &stm.rxHandlingTask, APP_CPU_NUM);
  // xTaskCreatePinnedToCore(sdTask,   "SD task",   20000, NULL, 3, &stm.sdTask,   APP_CPU_NUM);
  xTaskCreatePinnedToCore(dataTask, "Data task", 20000, NULL, 3, &stm.dataTask, APP_CPU_NUM);

  // if(stm.sdQueue == NULL || stm.loraTxQueue == NULL){
  //   ESP.restart();
  // }

  if(stm.spiMutex == NULL){
    ESP.restart();
  }

  /*
  if(stm.loraTask == NULL || stm.sdTask == NULL || stm.dataTask == NULL){
   ESP.restart();
  }*/
  
  vTaskDelete(NULL);
}

void loop() {}

