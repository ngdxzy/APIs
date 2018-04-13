/*
 * AxiVDMA.h
 *
 *  Created on: 2017Äê9ÔÂ27ÈÕ
 *      Author: BeatsGr
 */

#ifndef SRC_AXIVDMA_H_
#define SRC_AXIVDMA_H_
#include "xparameters.h"
#include "xil_io.h"

#define DDR_BASEADDR        0x00000000
//#define UART_BASEADDR       0xe0001000
#define VDMA_BASEADDR       XPAR_AXI_VDMA_0_BASEADDR
#define EN_ADDR 0x41200000
#define VIDEO_LENGTH  (H_STRIDE*V_ACTIVE)
#define VIDEO_BASEADDR0 DDR_BASEADDR + 0x2000000
#define VIDEO_BASEADDR1 DDR_BASEADDR + 0x3000000
#define VIDEO_BASEADDR2 DDR_BASEADDR + 0x4000000

void InitVDMA();
void GetVal(u32 addr);
void print_framcount();
void RxIntr(void* CallBackRef);

#endif /* SRC_AXIVDMA_H_ */
