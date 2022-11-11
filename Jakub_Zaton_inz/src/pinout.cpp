#include "../include/config/pinout.h"
#include <Wire.h>

float voltageMeasure(uint8_t batteryPin)
{
    // reverseDividerVal = (R1 + R2) / R2 = 58/11
    // return (analogReadMilliVolts(batteryPin) / 4095) * 3300 * (58/11);//TODO sprawdizc rezystor
    return (analogReadMilliVolts(batteryPin)*0.005528);
    
}

void pinInit()
{
    pinMode(BT_JUMP, PULLUP); 
    //VOLTAGE
    pinMode(VOLTAGE_MEASURE, INPUT);
}