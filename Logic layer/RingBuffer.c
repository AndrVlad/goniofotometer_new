/*
 * RingBuffer.c
 *
 *  Created on: 21 апр. 2026 г.
 *      Author: Admin
 */

ring_buf_t adc_buf = {.read_ptr = 0, .write_ptr = 0};

void saveToRingBuf(uint8_t* in_buf, uint16_t size) {

	for (uint8_t i = 0; i < size; i++) {
		if (adc_buf.write_ptr >= ADC_BUF_LEN) {
			adc_buf.write_ptr = 0;
		}
		adc_buf->buf[adc_buf.write_ptr] = in_buf[i];
		adc_buf.write_ptr++;
	}
	return;
}

void clearRingBuf() {
	adc_buf.read_ptr = adc_buf.write_ptr = 0;
}

uint16_t getAvailableNumRingBuf() {

	if (read_ptr < write_ptr) {
		return adc_buf.write_ptr - adc_buf.read_ptr;
	}

	if (read_ptr == write_ptr) {
		return 0;
	}

	if (read_ptr > write_ptr) {
		return (ADC_BUF_LEN - adc_buf.read_ptr) + adc_buf.write_ptr;
	}

	return num;
}
void readRingBuf(uint8_t* in_buffer, uint8_t start_pos) {

};

