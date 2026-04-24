/*
 * Encoder.h
 *
 *  Created on: 15 апр. 2026 г.
 *      Author: vlado
 */

#include <stdint.h>
#include "Common.h"

#ifndef ENCODER_ENCODER_H_
#define ENCODER_ENCODER_H_

#define ENCODER_RESOLUTION 131071

typedef struct  {
	uint32_t cur_value; // текущее значение энкодера
	uint32_t inv_value;	// инвертированное значение энкодера
} encoder_t;

extern encoder_t h_encoder, v_encoder;

void setEncoderPollFrequency(uint16_t poll_freq);
void startPollingEncoder();
void pollEncoder(uint8_t encoder_num);
uint32_t getInvVal(uint8_t encoder_num);

#endif /* ENCODER_ENCODER_H_ */
