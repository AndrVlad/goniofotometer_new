/*
 * Timer.c
 *
 *  Created on: 18 апр. 2026 г.
 *      Author: Admin
 */
#include "Timer.h"
void resetKeepAliveTimer() {

	return;
};

void startCalibrationTimer() {
	return;
};
void stopCalibrationTimer() {
	return;
};

void startPollingEncoderTimer() {
	HAL_TIM_Base_Start_IT(&htim7);
};

void stopPollingEncoderTimer() {
	HAL_TIM_Base_Stop_IT(&htim7);
	__HAL_TIM_SET_COUNTER(&htim7, 0);
};

void setEncoderTimerParams(uint16_t poll_freq_mcs) {
	htim7.Instance->ARR = poll_freq_mcs-1;
};


