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
  float rocketWeight;
  float tankWeight; 
  uint32_t rocketWeightRaw;
  uint32_t tankWeightRaw;


  DataFrame():
    vbat(0),
    rocketWeight(0),
    tankWeight(0),
    rocketWeightRaw(0),
    tankWeightRaw(0)
  {}
};

void createDataFrame(DataFrame dataFrame, char *data);

#endif