/*
 * Encoder.c
 *
 *  Created on: 15 апр. 2026 г.
 *      Author: vlado
 */
#include "Encoder.h"
#include "Timer.h"
#include <stdint.h>

encoder_t h_encoder, v_encoder;
uint32_t encoder_val = 0;

uint8_t dma_spi4_buf[5], dma_spi3_buf[5] = {0};

void pollEncoder(uint8_t encoder_num) {
	if (encoder_num) {
		HAL_SPI_Receive_DMA(&hspi4, dma_spi4_buf, 5);
	} else {
		HAL_SPI_Receive_DMA(&hspi3, dma_spi3_buf, 5);
	}
}

uint32_t getInvVal(uint8_t encoder_num) {
	if (encoder_num) {
		return h_encoder.inv_value;
	} else {
		return v_encoder.inv_value;
	}
};

void startPollingEncoder() {
	startPollingEncoderTimer();
};

void stopPollingEncoder() {
	stopPollingEncoderTimer();
};


void setEncoderPollFrequency(uint16_t poll_freq) {
	setEncoderTimerParams(poll_freq);
	return;
};


void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi)
{
	encoder_val = 0;
	// first encoder
	if (hspi->Instance == SPI4) {
		encoder_val =  (dma_spi4_buf[2] >> 5) & 0x07;
		encoder_val |=  ((uint32_t)dma_spi4_buf[1] << 3);
		encoder_val |=  (((uint32_t)dma_spi4_buf[0] & 0x3F) << 11);
		h_encoder.cur_value = encoder_val;
		h_encoder.inv_value = ENCODER_RESOLUTION - encoder_val;
	}

	// second encoder
	if (hspi->Instance == SPI3) {
		encoder_val  =  (dma_spi3_buf[2] >> 5) & 0x07;
		encoder_val |=  ((uint32_t)dma_spi3_buf[1] << 3);
		encoder_val |=  (((uint32_t)dma_spi3_buf[0] & 0x3F) << 11);
		v_encoder.cur_value = encoder_val;
		v_encoder.inv_value = ENCODER_RESOLUTION - encoder_val;
	}
}
