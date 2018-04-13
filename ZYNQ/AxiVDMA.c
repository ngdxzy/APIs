/*
 * AxiVDMA.c
 *
 *  Created on: 2017年9月27日
 *      Author: BeatsGr
 */

#include "AxiVDMA.h"
#include "sleep.h"
#include "Gic.h"

u32* frambuffer[3] = {VIDEO_BASEADDR0,VIDEO_BASEADDR1,VIDEO_BASEADDR2};
#define HL 1280
#define VL 720

void InitVDMA()
{
	Xil_Out8(EN_ADDR,0x00);
	usleep(100000);
	Xil_Out32((VDMA_BASEADDR + 0x030), 0x00000004);// enable circular mode

	Xil_Out32((VDMA_BASEADDR + 0x030), 0x0000008b);// enable circular mode
	Xil_Out32((VDMA_BASEADDR + 0x0AC), VIDEO_BASEADDR0);	// start address
	Xil_Out32((VDMA_BASEADDR + 0x0B0), VIDEO_BASEADDR1);	// start address
	Xil_Out32((VDMA_BASEADDR + 0x0B4), VIDEO_BASEADDR2);	// start address
	Xil_Out32((VDMA_BASEADDR + 0x0A8), (HL*4));		// h offset (640 * 4) bytes
	Xil_Out32((VDMA_BASEADDR + 0x0A4), (HL*4));		// h size (640 * 4) bytes
	Xil_Out32((VDMA_BASEADDR + 0x0A0), (VL));		// v size (480)


	//Intr_Connect(int IntrID,Xil_InterruptHandler IntrFunction,void* CallBackRef)

	usleep(330000);
	Xil_Out8(EN_ADDR,0xff);
	usleep(330000);
	/*****************从DDR读数据设置**********************/
	Xil_Out32((VDMA_BASEADDR + 0x000), 0x0000004); 		// enable circular mode
	Xil_Out32((VDMA_BASEADDR + 0x000), 0x000008b); 		// enable circular mode
	Xil_Out32((VDMA_BASEADDR + 0x05c), VIDEO_BASEADDR0); 	// start address
	Xil_Out32((VDMA_BASEADDR + 0x060), VIDEO_BASEADDR1); 	// start address
	Xil_Out32((VDMA_BASEADDR + 0x064), VIDEO_BASEADDR2); 	// start address
	Xil_Out32((VDMA_BASEADDR + 0x058), (HL*4)); 		// h offset (640 * 4) bytes
	Xil_Out32((VDMA_BASEADDR + 0x054), (HL*4)); 		// h size (640 * 4) bytes
	Xil_Out32((VDMA_BASEADDR + 0x050), VL); 			// v size (480)
//	Xil_Out32((VDMA_BASEADDR + 0x000), 0x00000003); 		// enable circular mode

}
void GetVal(u32 addr)
{
	u32 Status;
	char s[32];
	int i;
	Status = Xil_In32(VDMA_BASEADDR + addr);
	for (i = 31;i >= 0;i--)
	{
		s[i] = Status % 2 + '0';

		Status /= 2;
	}
	printf("0x%x:\t",addr);
	for(i = 0;i < 32;i++)
	{
		if(i%8 == 0 && i)
			printf("\n\r\t");
		printf("%c",s[i]);
	}
	printf("\n\r");
}
void print_framcount()
{
	u32 temp;
	temp = *(frambuffer[0]);
	printf("buffer1：%d\t",temp&0xff);
	temp = *(frambuffer[1]);
	printf("buffer2：%d\t",temp&0xff);
	temp = *(frambuffer[2]);
	printf("buffer3：%d\n",temp&0xff);
//
	Xil_DCacheFlush();
}
void RxIntr(void* CallBackRef);
