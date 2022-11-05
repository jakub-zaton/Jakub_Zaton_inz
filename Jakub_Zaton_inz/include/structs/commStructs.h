#ifndef DATA_HH
#define DATA_HH

#include "../config/config.h"

struct TxData{
  uint8_t command;
  uint16_t commandValue;
};


struct Options{
  uint16_t loraFreqMHz;
  uint32_t bitToGramsRatioTank;
  uint32_t bitToGramsRatioRocket;

  Options():
    loraFreqMHz(LORA_FREQ_MHZ),
    bitToGramsRatioTank(BIT_TO_GRAM_RATIO_TANK),
    bitToGramsRatioRocket(BIT_TO_GRAM_RATIO_RCK)
  {}
};

struct DataFrame{
  float vbat;
  float ADC1_Sparkfun;
  float ADC2_China; 
  uint32_t ADC1_SparkfunRaw;
  uint32_t ADC2_ChinaRaw;


  DataFrame():
    vbat(0),
    ADC1_Sparkfun(0),
    ADC2_China(0),
    ADC1_SparkfunRaw(0),
    ADC2_ChinaRaw(0)
  {}
};

void createDataFrame(DataFrame dataFrame, char *data);

#endif