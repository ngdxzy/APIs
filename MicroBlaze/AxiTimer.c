/*
 * AxiTimer.c
 *
 *  Created on: 2017Äê10ÔÂ12ÈÕ
 *      Author: Beats
 */
#include "AxiTimer.h"

#if AxiTimerEnabled

XTmrCtr SysTimer;
u8 flag = 1;

void InitAxiTimer()
{
	XTmrCtr_Initialize(&SysTimer,0);
	XTmrCtr_SetResetValue(&SysTimer,0,100000);
	XTmrCtr_SetOptions(&SysTimer,0,XTC_DOWN_COUNT_OPTION|XTC_AUTO_RELOAD_OPTION|XTC_INT_MODE_OPTION);
	XTmrCtr_SetHandler(&SysTimer,TimerIntrHandle,&SysTimer);
	AxiIntcConnect(3,XTmrCtr_InterruptHandler,&SysTimer);
	XTmrCtr_Start(&SysTimer,0);
}

void TimerIntrHandle(void *CallBackRef)
{
	XTmrCtr_ClearStats(CallBackRef);
	AckIntr(3);
	flag = 0;
}

void SystemIdle()
{
	while(flag);
	flag = 1;
}
#endif
