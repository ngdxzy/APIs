/*
 * AxiUart.h
 *
 *  Created on: 2017Äê9ÔÂ28ÈÕ
 *      Author: Administrator
 */

#ifndef SRC_AXIUART_H_
#define SRC_AXIUART_H_


#include "xparameters.h"

#define AxiUartEnabled 0

#if AxiUartEnabled

#include "xil_io.h"
typedef void (*IntrFuncHandle)(void*);
typedef struct{
	u32 BaseAddr;
	u32 RxFifo;
	u32 TxFifo;
	u32 CtrlReg;
	u32 StatusReg;

	u8* txbuffer;
	u8 bytes2send;
	u8 bytesSended;

	u8* rxbuffer;
	u8 bytes2read;
	u8 bytesReaded;

	IntrFuncHandle TxHandle;
	IntrFuncHandle RxHandle;
}UartLite;

//Regester
#define RxFifoOffset 	0x00000000
#define TxFifoOffset 	0x00000004
#define StateRegOffset 	0x00000008
#define CtrlRegOffset	0x0000000c
//flags
#define TxFifoFull 		0x00000008
#define TxFifoEmpty		0x00000004
#define RxFifoFull		0x00000002
#define RxValid			0x00000001

#define EnableIntr  	0x00000010
#define ResetRxFifo		0x00000002
#define ResetTxFifo		0x00000001

//Api Functions
void InitUartLite(UartLite* Config,u32 BaseAddr,u8* sbuf,u8* rbuf);
void SetTxIntrHandle(UartLite* Config,IntrFuncHandle Func);
void SetRxIntrHandle(UartLite* Config,IntrFuncHandle Func);
void UartIntrHandle(void *CallBackRef);
void UartLiteSend(UartLite* Config,u8 *buf,u8 size);
u8 UartLiteRead(UartLite* Config,u8 *buf);

void RxIntr(void *CallBackRef);
void TxIntr(void *CallBackRef);


#endif 
#endif /* SRC_AXIUART_H_ */
