/*
 * PC_Communication.h
 *
 *  Created on: Apr 14, 2026
 *      Author: Admin
 */
#include <stdint.h>
#include "stm32f7xx_hal.h"

uint8_t* getPCCommand();
void sendAnswerToPC(uint8_t* data, uint8_t size);


