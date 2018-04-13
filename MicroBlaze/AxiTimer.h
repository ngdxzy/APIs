/*
 * AxiTimer.h
 *
 *  Created on: 2017Äê10ÔÂ12ÈÕ
 *      Author: Beats
 */

#ifndef SRC_AXITIMER_H_
#define SRC_AXITIMER_H_

#define AxiTimerEnabled 1

#if AxiTimerEnabled
#include "xtmrctr.h"
#include "AxiIntc.h"
void InitAxiTimer();

void TimerIntrHandle(void *);

void SystemIdle();
#endif

#endif /* SRC_AXITIMER_H_ */
