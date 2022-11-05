#include "../include/tasks/tasks.h"

char data[SD_FRAME_SIZE] = {};

void dataTask(void *arg){

  DataFrame dataFrame;

  //HX711ADC1_Sparkfun
  ADC1_Sparkfun.begin();
  ADC1_Sparkfun.start(STABILIZNG_TIME, true); //start without tare
  ADC1_Sparkfun.setCalFactor(BIT_TO_GRAM_RATIO_RCK);
  // ADC1_Sparkfun.setTareOffset(OFFSET_RCK);
  ADC1_Sparkfun.setSamplesInUse(4);

  // ADC2_China.begin();
  // ADC2_China.start(STABILIZNG_TIME, true); //start without tare
  // ADC2_China.setCalFactor(BIT_TO_GRAM_RATIO_TANK);
  // // ADC2_China.setTareOffset(OFFSET_TANK);
  // ADC2_China.setSamplesInUse(1);

  // while (ADC2_China.getTareTimeoutFlag())
  // {
  //   vTaskDelay(1000 / portTICK_PERIOD_MS);
  // }

   while (ADC1_Sparkfun.getTareTimeoutFlag())
  {
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }


  vTaskDelay(100 / portTICK_PERIOD_MS);
 
  int counter = 0;
  bool var = true;
  while(1){

    // if(ADC2_China.update() == 1){
    //   dataFrame.ADC2_China = ADC2_China.getData();
    //   dataFrame.ADC2_ChinaRaw = (uint32_t) ADC2_China.getRawData();
    // }

    if(ADC1_Sparkfun.update() == 1){
      dataFrame.ADC1_Sparkfun = ADC1_Sparkfun.getData();
      dataFrame.ADC1_SparkfunRaw = (uint32_t) ADC1_Sparkfun.getRawData();
    }

    dataFrame.vbat = voltageMeasure(VOLTAGE_MEASURE);
    // memcpy(dataFrame.motorState, pwrData.motorState, sizeof(uint8_t[5]));

    createDataFrame(dataFrame, data);

    Serial.println(data);
    // xQueueSend(stm.loraTxQueue, (void*)data, 0);

    // xQueueSend(stm.sdQueue, (void*)data, 0); 
    if(var==true && counter==200){
        // ADC1_Sparkfun.CustomCalibration(500);
        ADC1_Sparkfun.getNewCalibration(500);
        Serial.println("CALIIIIIIIIIIIBRAAAAAAAAAAAAAAAAAAAAAAAAAAAAAATE");
        var = false;
    }
    counter++;
  
    
    Serial.println("\n\n\nCOM DATA:");
    Serial.print("Module VOLTAGE: "); Serial.println(voltageMeasure(VOLTAGE_MEASURE));
    Serial.print("ADC2_China WEIGHT: "); Serial.println(dataFrame.ADC2_China);
    Serial.print("ADC2_China RAW: "); Serial.println(dataFrame.ADC2_ChinaRaw);
    Serial.print("ADC1_Sparkfun WEIGHT: "); Serial.println(dataFrame.ADC1_Sparkfun);
    Serial.print("ADC1_Sparkfun RAW: "); Serial.println(dataFrame.ADC1_SparkfunRaw);
    Serial.print("ADC1_Sparkfun CAL FACTOR: "); Serial.println(ADC1_Sparkfun.getCalFactor());
    vTaskDelay(50 / portTICK_PERIOD_MS);
  }
}