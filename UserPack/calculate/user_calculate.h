#ifndef CALCULATE_H
#define CALCULATE_H

#include "main.h"


void BubbleSort(float* a, int n);
void AD_calcuate(float *newdata,uint16_t *data,int len);

//struct ECGData{
//	float ECG_ADCValue[256];
//	uint8_t BMP;

//};

struct ECGdata_InitTypeDef
{
//    int first;
//    double second;
//    char* third;
//    float four;
	float EGC_ADCVaule[NPT];
	uint8_t BMP;
	
};

#endif