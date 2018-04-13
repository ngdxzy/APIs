/*
 * AxiIntc.h
 *
 *  Created on: 2017Äê10ÔÂ12ÈÕ
 *      Author: Beats
 */

#ifndef SRC_AXIINTC_H_
#define SRC_AXIINTC_H_

#define AxiIntcEnabled 1

#if AxiIntcEnabled
#include "xintc.h"
#include "xil_exception.h"

#define SysIntcID 0

void InitAxiIntc();
void AxiIntcConnect(u8 Id,XInterruptHandler Funcptr,void* CallBackRef);
void AckIntr(u8 id);
#endif


#endif /* SRC_AXIINTC_H_ */
