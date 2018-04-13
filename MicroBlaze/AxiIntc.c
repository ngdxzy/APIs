/*
 * AxiIntc.c
 *
 *  Created on: 2017Äê10ÔÂ12ÈÕ
 *      Author: Beats
 */
#include "AxiIntc.h"

#if AxiIntcEnabled

XIntc SysIntc;

void InitAxiIntc()
{
	XIntc_Initialize(&SysIntc,SysIntcID);
	//Init Exception
	Xil_ExceptionInit();
	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT,XIntc_InterruptHandler,&SysIntc);
	//microblaze_register_handler(XIntc_DeviceInterruptHandler, XIntc_InterruptHandler);
	Xil_ExceptionEnable();
	XIntc_Start(&SysIntc,XIN_REAL_MODE);
}
void AxiIntcConnect(u8 Id,XInterruptHandler Funcptr,void* CallBackRef)
{
	XIntc_Disable(&SysIntc,Id);
	XIntc_Connect(&SysIntc,Id,Funcptr,CallBackRef);
	XIntc_Enable(&SysIntc,Id);
}
void AckIntr(u8 id)
{
	XIntc_Acknowledge(&SysIntc,id);
}
#endif

