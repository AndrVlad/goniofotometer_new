/*
 * PhotodetectorController.h
 *
 *  Created on: 19 апр. 2026 г.
 *      Author: Admin
 */

#ifndef PHOTODETECTORCONTROLLER_H_
#define PHOTODETECTORCONTROLLER_H_

#include <stdint.h>
#include <stdbool.h>

void setParamsADC(uint8_t coeff_val, uint8_t ADC_freq);
void handleCoeffSetting();

#endif /* PHOTODETECTORCONTROLLER_H_ */
