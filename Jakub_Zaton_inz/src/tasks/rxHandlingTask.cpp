#include "../include/tasks/tasks.h"
#include <string>
#include <iostream>

using namespace std;
extern char data[SD_FRAME_SIZE];

enum FrameStates {
    TARE_RCK_,
    CALIBRATE_RCK_,
    TARE_TANK_,
    CALIBRATE_TANK_,
    SOFT_RESTART_ESP_,
    SOFT_RESTART_STM_,
    SET_CAL_FACTOR_,
    INVALID
};


FrameStates resolveOption(string input) {
    if( input == "TARE_RCK" ) return TARE_RCK_;
    if( input == "CALIBRATE_RCK" ) return CALIBRATE_RCK_;
    if( input == "TARE_TANK" ) return TARE_TANK_;
    if( input == "CALIBRATE_TANK" ) return CALIBRATE_TANK_;
    if( input == "SOFT_RESTART_ESP" ) return SOFT_RESTART_ESP_;
    if( input == "SET_CAL_FACTOR" ) return SET_CAL_FACTOR_;
    //...
    return INVALID;
 }


void rxHandlingTask(void* arg){
  
  char loraRx[LORA_RX_FRAME_SIZE];

  while(1){
    //LORA 
    if(xQueueReceive(stm.loraRxQueue, (void*)&loraRx, 0) == pdTRUE){
      Serial.print("LORAAAAAAAAAAAAAAAAAAAAAAA: ");
      
      Serial.println(loraRx);
    
      //TODO parser
      string frame_array [50];
      string loraRx_frame = loraRx;
      string delimiter = ";";
      string frame_elem;
      string frame_function;
      
      frame_elem = loraRx_frame.substr(0, loraRx_frame.find(delimiter));
      frame_array[0] = frame_elem;
      loraRx_frame = loraRx_frame.substr(frame_elem.length());
      loraRx_frame = loraRx_frame.erase(0, 1);
     

      if(frame_array[0]=="R4T" || frame_array[0]=="R4A"){  
         int i = 1;
        do {//decomposition of the frame
          
              frame_elem = loraRx_frame.substr(0, loraRx_frame.find(delimiter));
              frame_array[i] = frame_elem;
              loraRx_frame = loraRx_frame.substr(frame_elem.length());
              loraRx_frame = loraRx_frame.erase(0, 1);
              i++;
              cout<<"lora = "<<frame_elem<<endl;

          } while (loraRx_frame.compare("") != 0);

          frame_function = frame_array[1];

          switch(resolveOption(frame_function)){
             case TARE_RCK_:
              ADC1_Sparkfun.tare();
              break;
            
            case CALIBRATE_RCK_:
              Serial.print("CAL FACTOR ROCKET: "); Serial.println(ADC1_Sparkfun.CustomCalibration(atoi(frame_array[2].c_str())));
              break;

            case TARE_TANK_:
              ADC2_China.tare();
              break;

            case CALIBRATE_TANK_:
              // ADC2_China.CustomCalibration(atoi(frame_array[3].c_str()),0);
              // ADC2_China.CustomCalibration(atoi(frame_array[2].c_str()));
              Serial.print("CAL FACTOR TANK: "); Serial.println(ADC2_China.CustomCalibration(atoi(frame_array[2].c_str())));

              break;

            case SOFT_RESTART_ESP_:
              //RESET ESP COMMAND
              ESP.restart();
              break;

          case SET_CAL_FACTOR_:
            if(frame_array[2]=="RCK"){
              ADC1_Sparkfun.setCalFactor(atoi(frame_array[3].c_str()));
              Serial.print("CAL FACTOR RCK = "); Serial.println(atoi(frame_array[3].c_str()));
            }
            else if (frame_array[2]=="TANK"){
              ADC2_China.setCalFactor(atoi(frame_array[3].c_str()));
              Serial.print("CAL FACTOR TANK = "); Serial.println(atoi(frame_array[3].c_str()));
            }
            break;

          default:
            break;
          }
      }
    }
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}