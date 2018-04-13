/*
 * xadc.h
 *
 *  Created on: 2017Äê9ÔÂ11ÈÕ
 *      Author: BeatsGr
 */

#ifndef SRC_XADC_H_
#define SRC_XADC_H_

#define XadcEnabled 1

#if XadcEnabled
#include "xil_io.h"
#include "xparameters.h"
#include "xsysmon.h"

void Init_XADCW();
float GetV();
float GetT();


#endif

#endif /* SRC_XADC_H_ */
