/*
 * PC_Communication.c
 *
 *  Created on: Apr 14, 2026
 *      Author: Admin
 */
#include "Common.h"
#include "PC_Communication.h"

uint8_t uart3_rx_buf[6] = {0};

uint8_t* getPCCommand() {
	return uart3_rx_buf;
}

void sendAnswerToPC(uint8_t* data, uint8_t size) {
	HAL_UART_Transmit(&huart3, data,size,100);
	return;
}


