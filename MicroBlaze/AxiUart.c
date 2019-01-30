/*
 * AxiUart.c
 *
 *  Created on: 2017Äê9ÔÂ28ÈÕ
 *      Author: Administrator
 */

#include "AxiUart.h"

void InitUartLite(UartLite* Config,u32 BaseAddr,u8* sbuf,u8* rbuf)
{
	Config->BaseAddr = BaseAddr;
	Config->TxFifo = BaseAddr + TxFifoOffset;
	Config->RxFifo = BaseAddr + RxFifoOffset;
	Config->CtrlReg = BaseAddr + CtrlRegOffset;
	Config->StatusReg = BaseAddr + StateRegOffset;
	Config->rxbuffer = rbuf;
	Config->txbuffer = sbuf;
	Config->bytesReaded = 0;
	Config->bytes2read = 0;
	Config->TxHandle = TxIntr;
	Config->RxHandle = RxIntr;

	Xil_Out32(Config->CtrlReg,0x10);
}
void SetTxIntrHandle(UartLite* Config,IntrFuncHandle Func)
{
	Config->TxHandle = Func;
}
void SetRxIntrHandle(UartLite* Config,IntrFuncHandle Func)
{
	Config->RxHandle = Func;
}
void UartIntrHandle(void *CallBackRef)
{
	UartLite *Config = (UartLite*)CallBackRef;
	u8 Status = Xil_In8(Config->StatusReg);
	printf("hello");
	if((Status & RxValid) != 0)
	{
		Config->RxHandle(CallBackRef);
	}
	if((Status & TxFifoEmpty) != 0)
	{
		Config->TxHandle(CallBackRef);
	}
}
void UartLiteSend(UartLite* Config,u8 *buf,u8 size)
{
	u8 i;
	for(i = 0;i < size;i++)
	{
		Config->txbuffer[i] = buf[i];
	}
	Config->bytes2send = size;
	Config->bytesSended = 0;
	Xil_Out8(Config->TxFifo,Config->txbuffer[0]);
}
u8 UartLiteRead(UartLite* Config,u8 *buf)
{
	u8 i = 0;
	while(Config->bytesReaded)
	{
		buf[i] = Config->rxbuffer[i];
		Config->bytesReaded--;
		i++;
	}
	return i;
}
void RxIntr(void *CallBackRef)
{
	UartLite* Config = (UartLite*)CallBackRef;
	u8 Status = Xil_In8(Config->StatusReg);
	while((Status & RxValid) != 0)
	{
		Config->rxbuffer[Config->bytesReaded] = Xil_In8(Config->RxFifo);
		Config->bytesReaded++;
		Status = Xil_In8(Config->StatusReg);
	}
}
void TxIntr(void *CallBackRef)
{
	UartLite* Config = (UartLite*)CallBackRef;
	Config->bytesSended++;
	if(Config->bytesSended < Config->bytes2send)
		Xil_Out8(Config->TxFifo,Config->txbuffer[Config->bytesSended]);
}
