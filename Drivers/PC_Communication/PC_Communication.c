/*
 * PC_Communication.c
 *
 *  Created on: Apr 14, 2026
 *      Author: Admin
 */
#include "Common.h"
#include "PC_Communication.h"

uint8_t cmd_buf[33] = {0};

bool checkCRC(uint8_t* buf) {
	return true;
};

void setErrorResponse() {
	return;
};

void parserCMD() {

	  if (!checkCRC(cmd_buf)) {
		  setErrorResponse();
		  return;
	  }

	  __HAL_TIM_SET_COUNTER(&htim11, 0);

	  switch(cmd_buf[0]) {

	  }




}
