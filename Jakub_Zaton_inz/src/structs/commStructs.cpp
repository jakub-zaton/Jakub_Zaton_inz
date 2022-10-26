#include "../include/structs/commStructs.h"

void createDataFrame(DataFrame df, char *data){
  size_t loraDataSize;

  loraDataSize = snprintf(NULL, 0, "%0.2f;%0.2f;%0.2f;%d;%d",
   df.vbat, df.rocketWeight, df.tankWeight, df.rocketWeightRaw, df.tankWeightRaw) + 1;
  
  char loraFrame[loraDataSize];

  
  snprintf(loraFrame, loraDataSize, "%0.2f;%0.2f;%0.2f;%d;%d",
   df.vbat, df.rocketWeight, df.tankWeight, df.rocketWeightRaw, df.tankWeightRaw);
  
  strcpy(data, DATA_PREFIX);
  strcat(data, loraFrame);
  strcat(data, "\n");
}