/*
 * RingBuffer.h
 *
 *  Created on: 21 апр. 2026 г.
 *      Author: Admin
 */

#ifndef RINGBUFFER_H_
#define RINGBUFFER_H_

#include <stdint.h>

#define ADC_BUF_LEN	300

typedef struct {
	uint8_t* buf;
	int16_t write_ptr; 	// указатель на элемент, в который будет выполнена запись
	int16_t read_ptr;	// указатель на элемент, с которого будет считано
} ring_buf_t;

void saveToRingBuf(uint8_t* in_buf, uint16_t size);
void clearRingBuf();
uint16_t getAvailableNumRingBuf();
void readRingBuf(uint8_t* in_buffer, uint8_t start_pos);

#endif /* RINGBUFFER_H_ */
