/*
 * Common.h
 *
 *  Created on: Apr 14, 2026
 *      Author: Admin
 */

#ifndef INC_COMMON_H_
#define INC_COMMON_H_

#include <stdbool.h>
#include <stdint.h>
#include "stm32f7xx_hal.h"


extern bool uart1_rx_complete, uart3_rx_complete, spi3_rx_complete, spi4_rx_complete, tim12_ovflw, tim4_ovflw, tim10_ovflw, tim11_ovflw;
extern bool tim14_ovflw, tim5_ovflw;
extern SPI_HandleTypeDef hspi3;
extern SPI_HandleTypeDef hspi4;

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart3;

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim7;
extern TIM_HandleTypeDef htim11;
extern TIM_HandleTypeDef htim5;
extern TIM_HandleTypeDef htim14;
extern TIM_HandleTypeDef htim12;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;

#endif /* INC_COMMON_H_ */
