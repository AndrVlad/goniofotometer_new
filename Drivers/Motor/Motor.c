/*
 * Motor.c
 *
 *  Created on: 15 апр. 2026 г.
 *      Author: vlado
 */

#include "Motor.h"

motor_t h_motor, v_motor;

void accelerateMotor(motor_t* motor) {
	return;
}

void decelerateMotor(motor_t* motor) {
	return;
}

bool isMotorStopped(motor_t* motor) {
    return true;
}

bool isMotorAccelerated(motor_t* motor) {
    return true;
}

void setMotorFrequency(motor_t* motor, uint16_t freq) {
	return;
}

void startMotorRotation(motor_t* motor) {
	return;
}

void stopMotorRotation(motor_t* motor) {
	return;
}

enum dir_t getMotorDirection(motor_t* motor) {
    return FORWARD;
}

void setMotorDirection(motor_t* motor, enum dir_t direction) {
	return;
}
