/*
 * xadc.c
 *
 *  Created on: 2017Äê9ÔÂ11ÈÕ
 *      Author: BeatsGr
 */
#include "xadc.h"

#if XadcEnabled
#include "xil_io.h"
#include "xparameters.h"
#include "xsysmon.h"

XSysMon ADC_Wiz;

void Init_XADCW()
{
	XSysMon_Config* Config;
	Config = XSysMon_LookupConfig(XPAR_XADC_WIZ_0_DEVICE_ID);
	XSysMon_CfgInitialize(&ADC_Wiz,Config,Config->BaseAddress);
	XSysMon_Reset(&ADC_Wiz);
	XSysMon_SetSequencerMode(&ADC_Wiz,XSM_SEQ_MODE_CONTINPASS);
	//XSysMon_SetExtenalMux(&ADC_Wiz,18);
}
float GetV()
{
	float vol;
	u16 AdcData = XSysMon_GetAdcData(&ADC_Wiz,18);
	vol = AdcData >> 4;
	vol = vol * 1.25 / 4096;
	return vol;
}
float GetT()
{
	return XSysMon_RawToTemperature(XSysMon_GetAdcData(&ADC_Wiz,0));
}


#endif
