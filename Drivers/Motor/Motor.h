/*
 * Motor.h
 *
 *  Created on: 15 апр. 2026 г.
 *      Author: vlado
 */

#ifndef MOTOR_MOTOR_H_
#define MOTOR_MOTOR_H_

#include <stdint.h>
#include "stm32f7xx_hal.h"

enum dir_t {
	FORWARD,
	BACKWARD
};

typedef struct {
	enum dir_t direction;
	uint16_t cur_frequency;
	uint16_t target_frequency;
	TIM_HandleTypeDef timer;
} motor_t;

extern motor_t h_motor, v_motor;

#endif /* MOTOR_MOTOR_H_ */
