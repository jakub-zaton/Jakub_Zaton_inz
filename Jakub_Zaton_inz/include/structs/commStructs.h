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
  uint8_t tanWaState;
  uint16_t pressureSensor;
  bool tankHeating : 1;
  bool abortButton : 1;
  bool armButton : 1;
  bool igniterContinouity_1;
  bool igniterContinouity_2;
  float vbat;
  uint8_t motorState_1;
  uint8_t motorState_2;
  uint8_t motorState_3;
  uint8_t motorState_4;
  uint8_t motorState_5;
  float rocketWeight;
  float tankWeight; 
  uint32_t rocketWeightRaw;
  uint32_t tankWeightRaw;
  float thermocouple_1;
  float thermocouple_2;
  float thermocouple_3;

  DataFrame():
    tanWaState(States::INIT),
    tankHeating(0),
    abortButton(0),
    armButton(0),
    igniterContinouity_1(0),
    igniterContinouity_2(0),
    vbat(0),
    motorState_1(0),
    motorState_2(0),
    motorState_3(0),
    motorState_4(0),
    motorState_5(0),
    rocketWeight(0),
    tankWeight(0),
    rocketWeightRaw(0),
    tankWeightRaw(0),
    thermocouple_1(0),
    thermocouple_2(0),
    thermocouple_3(0)

  {}
};

void createDataFrame(DataFrame dataFrame, char *data);

#endif