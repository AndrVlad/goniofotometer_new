/*
 * Timer.h
 *
 *  Created on: 18 апр. 2026 г.
 *      Author: Admin
 */

#ifndef TIMER_TIMER_H_
#define TIMER_TIMER_H_

#include "Common.h"

void resetKeepAliveTimer();
void startCalibrationTimer();
void stopCalibrationTimer();
void startPollingEncoderTimer();
void stopPollingEncoderTimer();
void startEncoderTimer();
void setEncoderTimerParams(uint16_t poll_freq_mcs);

#endif /* TIMER_TIMER_H_ */
