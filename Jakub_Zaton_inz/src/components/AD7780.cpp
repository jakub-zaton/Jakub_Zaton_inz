#include "../include/components/AD7780.h"
#include <Arduino.h>

void AD7780::begin(int AD7780_SCK_, int AD7780_MISO_, int AD7780_PWDOWN_) {
	AD7780_SCK = AD7780_SCK_;
	AD7780_MISO = AD7780_MISO_;
    AD7780_PWDOWN = AD7780_PWDOWN_;

    pinMode(AD7780_PWDOWN, OUTPUT);
	pinMode(AD7780_SCK, OUTPUT);	// SCK is output
	pinMode(AD7780_MISO, INPUT);	// MISO ist read
	digitalWrite(AD7780_PWDOWN, LOW);		// AD7080 in Standby
	Serial.println("AD7780 initialisation finnished");
}




int AD7780::readDataRaw(){

    digitalWrite(AD7780_SCK, HIGH);				// Clock high from Arduino
    vTaskDelay(1/portTICK_PERIOD_MS);
    digitalWrite(AD7780_PWDOWN, HIGH);			// AD7080 Turn on	

    while(digitalRead(AD7780_MISO)==HIGH);	// Wait until AD7780 sets RDY LOW
    // Serial.println("MISO turned low Measuring is finnished, and we get the result");


    uint32_t adc_read = 0;
    uint8_t stat = 0;
    for(int i=0; i< 32; i++)
    {
    digitalWrite(AD7780_SCK, LOW);
    delayMicroseconds(10);
    digitalWrite(AD7780_SCK, HIGH);

    if(digitalRead(AD7780_MISO)) {
        adc_read |= 1;
    }
    adc_read <<= 1;
    delayMicroseconds(10);
    }

    adc_read >>= 1;
    stat = adc_read & 0xff;
    adc_read >>= 8;

    // Serial.print("Control bits: ");
    // Serial.println(stat, BIN);

    digitalWrite(AD7780_PWDOWN, LOW);    // AD7080 Turn off	
    return adc_read;
}




float AD7780::calibration(int knownMass){

  Serial.println("Remove aything from a scale");
  vTaskDelay(1000/portTICK_PERIOD_MS);
  Serial.println("Tare - looking for offset");
  //  for(int i = 0; i < 10; i++)
  //   calZero += readDataRaw();

  // calZero = calZero/10;
  // Serial.print("Cal Zero = ");
  // Serial.println(calZero);

  Serial.println("PUT weight on the scale");
  vTaskDelay(1000/portTICK_PERIOD_MS);
  for(int i = 0; i < 10; i++)
    calLoad += readDataRaw();
  
  long calLoadAverage = calLoad/10;
  calCoeff = (calLoadAverage-calZero)/knownMass;

  Serial.println("Cal coeff settled");
//   Serial.println("REMOVE OBJECT FROM THE SCALE");

//   vTaskDelay(2000/portTICK_PERIOD_MS);
//   tare();
  
  return calCoeff;
}



float AD7780::readData(){
  outputWeight = ((long double)readDataRaw()-(long double)calZero)/calCoeff;
  int outputWeightInt = (int32_t) outputWeight;
  return outputWeightInt;
}

void AD7780::set_calCOeff(long calCoeff_){
    calCoeff = calCoeff_;
}

void AD7780::set_offset(long calZero_){
    calZero = calZero_;
}

void AD7780::tare(){
    for(int i = 0; i < 10; i++)
        calZero += readDataRaw();
    calZero = calZero/10;
}

long AD7780::get_offset() {
	return calZero;
}

long AD7780::get_calFactor() {
	return calCoeff;
}

