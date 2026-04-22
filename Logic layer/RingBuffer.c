/*
 * RingBuffer.c
 *
 *  Created on: 21 апр. 2026 г.
 *      Author: Admin
 */

#include "RingBuffer.h"

uint8_t buffer[ADC_BUF_LEN] = {0};
ring_buf_t adc_buf = {.read_ptr = 0, .write_ptr = 0, .buf = buffer};

void saveToRingBuf(uint8_t* in_buf, uint16_t size) {

	for (uint8_t i = 0; i < size; i++) {
		if (adc_buf.write_ptr >= ADC_BUF_LEN) {
			adc_buf.write_ptr = 0;
		}
		adc_buf.buf[adc_buf.write_ptr] = in_buf[i];
		adc_buf.write_ptr++;
	}
	return;
}

void clearRingBuf() {
	adc_buf.read_ptr = adc_buf.write_ptr = 0;
}

uint16_t getAvailableNumRingBuf() {
	uint16_t num;
	if (adc_buf.read_ptr < adc_buf.write_ptr) {
		num = adc_buf.write_ptr - adc_buf.read_ptr;
		if (num < 3) {
			return 0;
		} else {
			return num;
		}
	}

	if (adc_buf.read_ptr == adc_buf.write_ptr) {
		return 0;
	}

	if (adc_buf.read_ptr > adc_buf.write_ptr) {
		num = (ADC_BUF_LEN - adc_buf.read_ptr) + adc_buf.write_ptr;
		if (num < 3) {
			return 0;
		} else {
			return num;
		}
	}
}
void readRingBuf(uint8_t* in_buffer, uint8_t start_pos) {

	uint16_t count = getAvailableNumRingBuf();

	if (count > 30) {
		count = 30;
	}

	for (uint16_t i = start_pos; i <= count + start_pos; i++) {
		in_buffer[i] = adc_buf.buf[adc_buf.read_ptr];
		if (adc_buf.read_ptr >= ADC_BUF_LEN) {
			adc_buf.read_ptr = 0;
		}
		adc_buf.read_ptr++;
	}
};

