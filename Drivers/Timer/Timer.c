/*
 * Timer.c
 *
 *  Created on: 18 апр. 2026 г.
 *      Author: Admin
 */
#include "Timer.h"
#include "Encoder.h"

#define IS_TIMER_RUNNING(htim) (((htim)->Instance->CR1 & TIM_CR1_CEN) != 0)

void startKeepAliveTimer() {
	__HAL_TIM_SET_COUNTER(&htim11, 0);
	HAL_TIM_Base_Start_IT(&htim11);
}

void resetKeepAliveTimer() {
	__HAL_TIM_SET_COUNTER(&htim11, 0);
	return;
};

void startCalibrationTimer() {
	HAL_TIM_Base_Start_IT(&htim10);
	return;
};

void stopCalibrationTimer() {
	HAL_TIM_Base_Stop_IT(&htim10);
	__HAL_TIM_SET_COUNTER(&htim10, 0);
	return;
};

void startPollingEncoderTimer() {
	HAL_TIM_Base_Start_IT(&htim7);
};

void stopPollingEncoderTimer() {
	HAL_TIM_Base_Stop_IT(&htim7);
	__HAL_TIM_SET_COUNTER(&htim7, 0);
};

void startIntervalTimer() {
	HAL_TIM_Base_Start_IT(&htim5);
};

void stopIntervalTimer() {
	HAL_TIM_Base_Stop_IT(&htim5);
	__HAL_TIM_SET_COUNTER(&htim5, 0);
}

void startResolutionTimer() {
	HAL_TIM_Base_Start_IT(&htim14);
}

void stopResolutionTimer() {
	HAL_TIM_Base_Stop_IT(&htim14);
	__HAL_TIM_SET_COUNTER(&htim14, 0);
}

void setEncoderTimerParams(uint16_t poll_freq_mcs) {
	htim7.Instance->ARR = poll_freq_mcs-1;
};

void setTimeIntervalTimerParams(uint32_t period) {
	htim5.Instance->ARR = period;
	__HAL_TIM_SET_COUNTER(&htim5, 0);
}
void setTimeResolutionTimerParams(uint32_t period) {
	htim14.Instance->ARR = period;
	__HAL_TIM_SET_COUNTER(&htim14, 0);
}

void setTimerARR(TIM_HandleTypeDef* timer, uint32_t freq) {
	uint32_t tim_clock = (AHB1_TIMER_CLOCK_MHz * 1000000);
	__HAL_TIM_SET_COUNTER(timer, 0);
	timer->Instance->ARR = ((tim_clock/(timer->Instance->PSC + 1))/freq) - 1;
};

HAL_TIM_StateTypeDef getTimerStatus(TIM_HandleTypeDef* timer) {
	return HAL_TIM_Base_GetState(timer);
}

void startTimer(TIM_HandleTypeDef* timer) {
	HAL_TIM_Base_Start_IT(timer);
}

void stopTimer(TIM_HandleTypeDef* timer) {
	HAL_TIM_Base_Stop_IT(timer);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM2) {
    	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
    	__HAL_TIM_SET_COUNTER(&htim2, 0);
    }
    if (htim->Instance == TIM3) {
    	HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);
    	__HAL_TIM_SET_COUNTER(&htim3, 0);
    }
    if (htim->Instance == TIM4) {
    	tim4_ovflw = true;
    }

    if (htim->Instance == TIM5) {
    	tim5_ovflw = true;
    	stopResolutionTimer();
    	stopIntervalTimer();
    }

    if (htim->Instance == TIM7) {
    	pollEncoder(0);
    	pollEncoder(1);
    	__HAL_TIM_SET_COUNTER(&htim7, 0);
    }

    if (htim->Instance == TIM10) {
    	tim10_ovflw = true;
    	__HAL_TIM_SET_COUNTER(&htim10, 0);
    }

    if (htim->Instance == TIM11) {
    	tim11_ovflw = true;
    	__HAL_TIM_SET_COUNTER(&htim11, 0);
    }

    if (htim->Instance == TIM12) {
    	tim12_ovflw = true;
    	__HAL_TIM_SET_COUNTER(&htim12, 0);
    }

    if (htim->Instance == TIM14) {
    	if (!IS_TIMER_RUNNING(&htim5)) {
    		startIntervalTimer();
    	}
    	tim14_ovflw = true;
    	pollEncoder(0);
    	pollEncoder(1);
    	__HAL_TIM_SET_COUNTER(&htim14, 0);
    }
}

