#include "../include/tasks/tasks.h"


// extern Hx711 rckWeight;
// extern Hx711 tankWeight;
// extern MCP23017 expander;
char data[SD_FRAME_SIZE] = {};
 PWRData pwrData;
//kod w tym tasku jest tylko do debugu 
void dataTask(void *arg){
  uint32_t abort_count = 0;
  int turnVar = 0;
  DataFrame dataFrame;
 
  expander.setPinMode(0,B,INPUT); //input for abort button

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
    Serial.print("TANWA VOLTAGE 4: "); Serial.println(voltageMeasure(VOLTAGE_MEASURE));
    Serial.print("TANK WEIGHT: "); Serial.println(dataFrame.tankWeight);
    Serial.print("ROCKET WEIGHT: "); Serial.println(dataFrame.rocketWeight);
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}