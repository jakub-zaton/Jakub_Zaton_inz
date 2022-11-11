#include <Arduino.h>
#include <SPI.h>
#include "../include/tasks/tasks.h"
#include "../include/config/config.h"
#include "../include/structs/SoftToolsManagment.h"
#include "../include/structs/commStructs.h"
#include <esp_wifi.h>
// #include "HX711.h"


SoftwareToolsManagment stm;
// HX711
// Hx711 ADC1_Sparkfun(HX1_SDA, HX1_SCL);
// Hx711 ADC2_China(HX2_SDA, HX2_SCL);
HX711 ADC1_Sparkfun;
HX711 ADC2_China;
AD7780 ADC3_AD;


void setup() {

  Serial.begin(115200);
  pinInit();


  stm.spi.begin();
  
  Serial.print("DZIAŁA");
  // stm.sdQueue = xQueueCreate(SD_QUEUE_LENGTH, sizeof(char[SD_FRAME_SIZE]));
  // stm.loraTxQueue = xQueueCreate(LORA_TX_QUEUE_LENGTH, sizeof(char[LORA_TX_FRAME_SIZE]));
  // stm.loraRxQueue = xQueueCreate(LORA_RX_QUEUE_LENGTH, sizeof(char[LORA_RX_FRAME_SIZE]));

  vTaskDelay(25 / portTICK_PERIOD_MS);

  // xTaskCreatePinnedToCore(loraTask, "LoRa task", 20000, NULL, 3, &stm.loraTask, PRO_CPU_NUM);
  // xTaskCreatePinnedToCore(rxHandlingTask, "Rx handling task", 20000, NULL, 2, &stm.rxHandlingTask, APP_CPU_NUM);
  // xTaskCreatePinnedToCore(sdTask,   "SD task",   20000, NULL, 3, &stm.sdTask,   APP_CPU_NUM);
  xTaskCreatePinnedToCore(dataTask, "Data task", 20000, NULL, 3, &stm.dataTask, APP_CPU_NUM);

  // if(stm.sdQueue == NULL || stm.loraTxQueue == NULL){
  //   ESP.restart();
  // }

  // if(stm.spiMutex == NULL){
  //   ESP.restart();
  // }

  /*
  if(stm.loraTask == NULL || stm.sdTask == NULL || stm.dataTask == NULL){
   ESP.restart();
  }*/
  
  vTaskDelete(NULL);
}

void loop() {}

//#################################################################################
//#######################################################################
// #define AD7780_PWDOWN 25	// Reset/ Power down pin -> High is on
// #define AD7780_SCK 32		// Clock
// #define AD7780_MISO 33		// MISO

// int calZero = 0;
// int calLoad = 0;
// int calCoeff = 0;
// float outputWeight = 0;

// int readDataRaw(){
//   digitalWrite(AD7780_SCK, HIGH);				// Clock high from Arduino
//   delay(1);
//   digitalWrite(AD7780_PWDOWN, HIGH);			// AD7080 Turn on	

//   while(digitalRead(AD7780_MISO)==HIGH);	// Wait until AD7780 sets RDY LOW
//   // Serial.println("MISO turned low Measuring is finnished, and we get the result");


//   uint32_t adc_read = 0;
//   uint8_t stat = 0;
//   for(int i=0; i< 32; i++)
//   {
//     digitalWrite(AD7780_SCK, LOW);
//     delayMicroseconds(10);
//     digitalWrite(AD7780_SCK, HIGH);

//     if(digitalRead(AD7780_MISO)) {
//       adc_read |= 1;
//     }
//     adc_read <<= 1;
//     delayMicroseconds(10);
//   }

//   adc_read >>= 1;
//   stat = adc_read & 0xff;
//   adc_read >>= 8;

//   // Serial.print("Control bits: ");
//   // Serial.println(stat, BIN);

//   digitalWrite(AD7780_PWDOWN, LOW);    // AD7080 Turn off	
//   return adc_read;
// }

// float calibration(int knownMass){

//   Serial.println("Remove aything from a scale");
//   delay(1000);
//   Serial.println("Tare - looking for offset");
//   //  for(int i = 0; i < 10; i++)
//   //   calZero += readDataRaw();

//   // calZero = calZero/10;
//   // Serial.print("Cal Zero = ");
//   // Serial.println(calZero);

//   Serial.println("PUT weight on the scale");
//   delay(6000);
//   for(int i = 0; i < 10; i++)
//     calLoad += readDataRaw();
  
//   int calLoadAverage = calLoad/10;
//   calCoeff = (calLoadAverage-calZero)/knownMass;

//   Serial.println("Cal coeff settled");
  
//   return calCoeff;

// }

// float readData(){
//   outputWeight = ((long double)readDataRaw()-(long double)calZero)/calCoeff;
//   int outputWeightInt = (int32_t) outputWeight;
//   return outputWeightInt;
// }

// void setup()
// {
//   Serial.begin(115200);
// 	Serial.println("Start...");
 
// 	pinMode(AD7780_PWDOWN, OUTPUT);
// 	pinMode(AD7780_SCK, OUTPUT);	// SCK is output
// 	pinMode(AD7780_MISO, INPUT);	// MISO ist read
// 	digitalWrite(AD7780_PWDOWN, LOW);		// AD7080 in Standby
// 	Serial.println("AD7780 initialisation finnished");
//   calibration(9100);
// }


// void loop()
// {

//   int adc_read = readDataRaw();
//   Serial.print("WEIGHT BIN: ");
//   Serial.println(adc_read, DEC);
  
//   Serial.print("WEIGHT in grams: ");
//   Serial.println(readData());
// }