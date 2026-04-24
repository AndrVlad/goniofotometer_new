/*
 * Photodetector.c
 *
 *  Created on: 15 апр. 2026 г.
 *      Author: vlado
 */
#include "Photodetector.h"
#include "Common.h"
#include <string.h>

uint8_t adc_data[5], adc_raw[5] = {0};

void pollPhotodetector() {
	__HAL_TIM_ENABLE(&htim1);
	HAL_UART_Receive_DMA(&huart1, adc_raw, 5);
	return;
};

void sendDataPD(uint8_t* data) {
	HAL_UART_Transmit(&huart1, data, 1,100);
}

uint8_t* getPDData() {
	return adc_data;
};

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if (huart->Instance == USART3) {
		uart3_rx_complete = 1;
	}

	if (huart->Instance == USART1) {
		uart1_rx_complete = 1;
		memcpy(adc_data, adc_raw, 5);
	}
}
