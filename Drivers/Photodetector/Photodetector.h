/*
 * Photodetector.h
 *
 *  Created on: 15 апр. 2026 г.
 *      Author: vlado
 */

#ifndef PHOTODETECTOR_PHOTODETECTOR_H_
#define PHOTODETECTOR_PHOTODETECTOR_H_

#include <stdint.h>
#include <stdbool.h>

void pollPhotodetector();
void sendDataPD(uint8_t* data);
uint8_t* getPDData();

#endif /* PHOTODETECTOR_PHOTODETECTOR_H_ */
