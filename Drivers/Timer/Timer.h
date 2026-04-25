/*
 * Timer.h
 *
 *  Created on: 18 апр. 2026 г.
 *      Author: Admin
 */

#ifndef TIMER_TIMER_H_
#define TIMER_TIMER_H_

#include "Common.h"

#define AHB1_TIMER_CLOCK_MHz 108

void resetKeepAliveTimer();
void startCalibrationTimer();
void stopCalibrationTimer();
void startPollingEncoderTimer();
void stopPollingEncoderTimer();
void startIntervalTimer();
void stopIntervalTimer();
void startResolutionTimer();
void stopResolutionTimer();
void setEncoderTimerParams(uint16_t poll_freq_mcs);
void setTimeIntervalTimerParams(uint32_t period);
void setTimeResolutionTimerParams(uint32_t period);
void setAccelPeriodTimer(TIM_HandleTypeDef* timer, uint32_t freq);
void setTimerARR(TIM_HandleTypeDef* timer, uint32_t freq);
void startTimer(TIM_HandleTypeDef* timer);
void stopTimer(TIM_HandleTypeDef* timer);
HAL_TIM_StateTypeDef getTimerStatus();
#endif /* TIMER_TIMER_H_ */
