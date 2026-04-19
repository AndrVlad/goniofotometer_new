/*
 * Encoder.h
 *
 *  Created on: 15 апр. 2026 г.
 *      Author: vlado
 */

#include <stdint.h>

#ifndef ENCODER_ENCODER_H_
#define ENCODER_ENCODER_H_

#define ENCODER_RESOLUTION 131071

typedef struct  {
	uint32_t cur_value;
	uint32_t inv_value;
} encoder_t;

extern encoder_t h_encoder, v_encoder;

void setEncoderPollFrequency(encoder_t* encoder, uint16_t poll_freq);

#endif /* ENCODER_ENCODER_H_ */
