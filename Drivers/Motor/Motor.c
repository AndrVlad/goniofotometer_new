/*
 * Motor.c
 *
 *  Created on: 15 апр. 2026 г.
 *      Author: vlado
 */

#include "Motor.h"
#include "Timer.h"

motor_t h_motor = {.timer = &htim2}, v_motor = {.timer = &htim3};

void accelerateMotor(motor_t* motor) {
	tim4_ovflw = false;

	 if (motor->target_frequency > (motor->target_frequency + MOTOR_FREQUENCY_STEP_HZ)) {
		 setMotorFrequency(motor,motor->cur_frequency + MOTOR_FREQUENCY_STEP_HZ);
		// __HAL_TIM_SET_COUNTER(&htim4, 0);

	 } else { // требуемая частота достигнута
		 stopTimer(&htim4);
		 // добавить частоту до целевой
		 setMotorFrequency(motor,motor->target_frequency);
		 HAL_TIM_Base_Stop_IT(&htim4);
		 return;
	 }
}

void decelerateMotor(motor_t* motor) {

	tim12_ovflw = false;

	if (getTimerStatus(motor->timer) == HAL_TIM_STATE_READY) {
		startTimer(&htim12);
		return;
	}

	 if (motor->cur_frequency <= DECELERATION_STEP_HZ) {
		stopTimer(motor->timer);
		motor->cur_frequency = 0;
		 } else {
			setMotorFrequency(motor,motor->cur_frequency - DECELERATION_STEP_HZ);
		 }
	return;
}

bool isMotorStopped(motor_t* motor) {
	if (motor->cur_frequency != 0) {
		return false;
	}
    return true;
}

bool isMotorAccelerated(motor_t* motor) {
	if (motor->target_frequency != motor->cur_frequency) {
		return false;
	}
    return true;
}

void setTargetMotorFrequency(motor_t* motor, uint16_t freq) {
	motor->target_frequency = freq;
	return;
}

void setMotorFrequency(motor_t* motor, uint16_t freq) {
	setTimerARR(motor->timer, freq*2);
	motor->cur_frequency = freq;
	return;
}

void setPeriodAccelTimer(motor_t* motor,uint16_t target_freq) {
	uint32_t result_freq;

	float ovflw_period_seconds = (MOTOR_FREQUENCY_STEP_HZ / 2);

	ovflw_period_seconds *= ACCELERATION_TIME_SEC;
	ovflw_period_seconds /= motor->target_frequency;
	result_freq = 1 / ovflw_period_seconds;

	setTimerARR(&htim4, result_freq);
	return;
}

void startMotorRotation(motor_t* motor) {

	// установка частоты, равной частоте приемистости
	setMotorFrequency(motor,PICK_UP_MOTOR_FREQUENCY_HZ);
	// установка частоты таймера, выполняющего увеличение частоты ШД для разгона
	setPeriodAccelTimer(motor,motor->target_frequency);
	// включение таймера для опроса энкодеров
	startPollingEncoderTimer();
	// включение таймера формирования импульса шага
	startTimer(motor->timer);
	// включение таймера для вызова функции увеличения частоты ШД
	startTimer(&htim4);
	return;
}

void stopMotorRotation(motor_t* motor) {
	stopTimer(motor->timer);
	stopTimer(&htim4);
	stopTimer(&htim12);
	stopPollingEncoderTimer();
	return;
}

enum dir_t getMotorDirection(motor_t* motor) {
    return motor->direction;
}

void setMotorDirection(motor_t* motor, enum dir_t direction) {
	if (direction == FORWARD) {
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_SET);
		motor->direction = FORWARD;
	} else {
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_RESET);
		motor->direction = BACKWARD;
	}
	return;
}
