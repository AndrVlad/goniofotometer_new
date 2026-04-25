/*
 * Motor.h
 *
 *  Created on: 15 апр. 2026 г.
 *      Author: vlado
 */

#ifndef MOTOR_MOTOR_H_
#define MOTOR_MOTOR_H_

#include <stdint.h>
#include <stdbool.h>
#include "Common.h"
#include "stm32f7xx_hal.h"

#define PICK_UP_MOTOR_FREQUENCY_HZ 	5
#define MOTOR_FREQUENCY_STEP_HZ 	15
#define ACCELERATION_TIME_SEC		3
#define DECELERATION_STEP_HZ		50

enum dir_t {
	FORWARD,
	BACKWARD
};

typedef struct {
	enum dir_t direction;
	uint16_t cur_frequency;
	uint16_t target_frequency;
	TIM_HandleTypeDef* timer;
} motor_t;

void accelerateMotor(motor_t* motor);
void decelerateMotor(motor_t* motor);
bool isMotorStopped(motor_t* motor);
bool isMotorAccelerated(motor_t* motor);
void setMotorFrequency(motor_t* motor, uint16_t freq);
void startMotorRotation(motor_t* motor);
void stopMotorRotation(motor_t* motor);
enum dir_t getMotorDirection(motor_t* motor);
void setMotorDirection(motor_t* motor, enum dir_t direction);

extern motor_t h_motor, v_motor;

#endif /* MOTOR_MOTOR_H_ */
