#include "../include/tasks/tasks.h"

char data[SD_FRAME_SIZE] = {};

void dataTask(void *arg){

  DataFrame dataFrame;

  //HX711
  rckWeight.begin();
  rckWeight.start(STABILIZNG_TIME, true); //start without tare
  rckWeight.setCalFactor(BIT_TO_GRAM_RATIO_RCK);
  // rckWeight.setTareOffset(OFFSET_RCK);
  rckWeight.setSamplesInUse(1);

  tankWeight.begin();
  tankWeight.start(STABILIZNG_TIME, true); //start without tare
  tankWeight.setCalFactor(BIT_TO_GRAM_RATIO_TANK);
  // tankWeight.setTareOffset(OFFSET_TANK);
  tankWeight.setSamplesInUse(1);
  while (tankWeight.getTareTimeoutFlag() && rckWeight.getTareTimeoutFlag())
  {
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }



  // !!!//DEBUG

  vTaskDelay(100 / portTICK_PERIOD_MS);
 
   
  while(1){

    if(tankWeight.update() == 1){
      dataFrame.tankWeight = tankWeight.getData();
      dataFrame.tankWeightRaw = (uint32_t) tankWeight.getRawData();
    }

    if(rckWeight.update() == 1){
      dataFrame.rocketWeight = rckWeight.getData();
      dataFrame.rocketWeightRaw = (uint32_t) rckWeight.getRawData();
    }

    dataFrame.vbat = voltageMeasure(VOLTAGE_MEASURE);
    // memcpy(dataFrame.motorState, pwrData.motorState, sizeof(uint8_t[5]));

    createDataFrame(dataFrame, data);

    Serial.println(data);
    // xQueueSend(stm.loraTxQueue, (void*)data, 0);

    // xQueueSend(stm.sdQueue, (void*)data, 0); 

    
    Serial.println("\n\n\nCOM DATA:");
    Serial.print("Module VOLTAGE: "); Serial.println(voltageMeasure(VOLTAGE_MEASURE));
    Serial.print("TANK WEIGHT: "); Serial.println(dataFrame.tankWeight);
    Serial.print("TANK WEIGHT RAW: "); Serial.println(dataFrame.tankWeightRaw);
    Serial.print("ROCKET WEIGHT: "); Serial.println(dataFrame.rocketWeight);
    Serial.print("ROCKET WEIGHT RAW: "); Serial.println(dataFrame.rocketWeightRaw);
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}