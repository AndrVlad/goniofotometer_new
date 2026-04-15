/*
 * PC_Communication.c
 *
 *  Created on: Apr 14, 2026
 *      Author: Admin
 */
#include "Common.h"

bool checkCRC() {
	return true;
};

void setErrorResponse() {
	return;
};

void parserCMD() {

	  if (!checkCRC()) {
		  setErrorResponse();
		  return;
	  }

	  __HAL_TIM_SET_COUNTER(&htim11, 0);




}
