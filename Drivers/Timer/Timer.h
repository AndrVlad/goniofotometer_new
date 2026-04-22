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
void startIntervalTimer();
void stopIntervalTimer();
void startResolutionTimer();
void stopResolutionTimer();
void setEncoderTimerParams(uint16_t poll_freq_mcs);
void setTimeIntervalTimerParams(uint32_t period);
void setTimeResolutionTimerParams(uint32_t period);

#endif /* TIMER_TIMER_H_ */
