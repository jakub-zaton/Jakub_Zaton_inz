#include "../include/tasks/tasks.h"

char data[SD_FRAME_SIZE] = {};

void dataTask(void *arg){

  DataFrame dataFrame;


  // ############################################################################
  // ###########   ADC1    ######################################################

  // ADC1_Sparkfun.begin(HX1_SDA,HX1_SCL);

  // if (ADC1_Sparkfun.is_ready()) {

  //   if(digitalRead(BT_JUMP)==1){
  //     Serial.println("500 grams");
  //     ADC1_Sparkfun.calibration(500);
  //   }
  //   else{
  //     Serial.println("8000 grams");
  //     ADC1_Sparkfun.calibration(8000);
  //   }

  //   // ADC1_Sparkfun.set_scale(111);
  //   // ADC1_Sparkfun.set_offset(-10304);
  //   ADC1_Sparkfun.tare();
  //   Serial.print("ADC1 OFFSEEEEET "); Serial.println(ADC1_Sparkfun.get_offset());
  //   vTaskDelay(1000/portTICK_PERIOD_MS);
  // }

  // // ###########################################################################
  // // ###########################################################################

  // // ############################################################################
  // // ###########   ADC2    ######################################################

  // ADC2_China.begin(HX2_SDA, HX2_SCL);

  // if (ADC2_China.is_ready()) {
  //   if(digitalRead(BT_JUMP)==1){
  //     Serial.println("500 grams");
  //     ADC2_China.calibration(500);
  //   }
  //   else{
  //     Serial.println("8000 grams");
  //     ADC2_China.calibration(8000);
  //   }

  //   // ADC2_China.set_scale(107);
  //   // ADC2_China.set_offset(19746);
  //   ADC2_China.tare();
  //   Serial.print("ADC2 OFFSEEEEET "); Serial.println(ADC2_China.get_offset());
  //   vTaskDelay(1000/portTICK_PERIOD_MS);
  // }

  // ###########################################################################
  // ###########################################################################

  // ############################################################################
  // ###########   ADC3    ######################################################

  ADC3_AD.begin(AD_SCLK, AD_DOUT, AD_NPDRST);

  
  if(digitalRead(BT_JUMP)==1){
      Serial.println("500 grams");
      ADC3_AD.calibration(500,15000);
    }
    else{
      Serial.println("8000 grams");
      ADC3_AD.calibration(8000,45000);
    }

  // ADC3_AD.set_calCOeff(111);
  // ADC3_AD.set_offset(-10304);
  // ADC3_AD.tare();
  // Serial.print("ADC3 OFFSEEEEET "); Serial.println(ADC3_AD.get_offset());
  vTaskDelay(1000/portTICK_PERIOD_MS);


  // ###########################################################################
  // ###########################################################################



  vTaskDelay(100 / portTICK_PERIOD_MS);
 
  // int counter = 0;
  // bool var = true;
  while(1){

    
      // Serial.print("ADC1 read in grams: \t\t");
      // Serial.print(ADC1_Sparkfun.get_units(1));
      // Serial.print(";");
      // Serial.print("ADC1 read RAW: \t\t");
      // Serial.print(ADC1_Sparkfun.read());
      // Serial.print(";\n");

      // Serial.print("ADC2 read in grams: \t\t");
      // Serial.println(ADC2_China.get_units(1));
      // Serial.print("ADC2 read RAW: \t\t");
      // Serial.println(ADC2_China.read());
      // Serial.print(ADC2_China.get_units(1));
      // Serial.print(";");
      // Serial.print(ADC2_China.read());
      // Serial.print(";\n");

      // Serial.print("ADC3 read in grams: ");
      // Serial.println(ADC3_AD.readData());
      // Serial.print("ADC3 read RAW: ");
      // Serial.println(ADC3_AD.readDataRaw());
      Serial.print(ADC3_AD.readData());
      Serial.print(";");
      Serial.print(ADC3_AD.readDataRaw());
      Serial.print(";\n");


    dataFrame.ADC1_Sparkfun = ADC3_AD.readData();
  //   // memcpy(dataFrame.motorState, pwrData.motorState, sizeof(uint8_t[5]));

    createDataFrame(dataFrame, data);

    Serial.print("DATA: ");
    Serial.println(data);


    xQueueSend(stm.loraTxQueue, (void*)data, 0);

  //   // xQueueSend(stm.sdQueue, (void*)data, 0); 
  //   if(var==true && counter==200){
  //       // ADC1_Sparkfun.CustomCalibration(500);
  //       ADC1_Sparkfun.getNewCalibration(500);
  //       Serial.println("CALIIIIIIIIIIIBRAAAAAAAAAAAAAAAAAAAAAAAAAAAAAATE");
  //       var = false;
  //   }
  //   counter++;
  
    
  //   Serial.println("\n\n\nCOM DATA:");
  //   Serial.print("Module VOLTAGE: "); Serial.println(voltageMeasure(VOLTAGE_MEASURE));
  //   Serial.print("ADC2_China WEIGHT: "); Serial.println(dataFrame.ADC2_China);
  //   Serial.print("ADC2_China RAW: "); Serial.println(dataFrame.ADC2_ChinaRaw);
  //   Serial.print("ADC1_Sparkfun WEIGHT: "); Serial.println(dataFrame.ADC1_Sparkfun);
  //   Serial.print("ADC1_Sparkfun RAW: "); Serial.println(dataFrame.ADC1_SparkfunRaw);
  //   Serial.print("ADC1_Sparkfun CAL FACTOR: "); Serial.println(ADC1_Sparkfun.getCalFactor());
    vTaskDelay(200 / portTICK_PERIOD_MS);
  }
}