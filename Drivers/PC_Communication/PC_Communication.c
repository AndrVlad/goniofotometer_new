/*
 * PC_Communication.c
 *
 *  Created on: Apr 14, 2026
 *      Author: Admin
 */
#include "Common.h"
#include "main.h"

bool checkCRC_PCData() {
	return true;
};

void setErrorResponse() {
	return;
};

void parserCMD() {

	  if (!checkCRC_PCData()) {
		  setErrorResponse();
		  return;
	  }

	  __HAL_TIM_SET_COUNTER(&htim11, 0);




}
