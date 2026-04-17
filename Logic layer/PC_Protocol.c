#include "FSMGonio.h"
#include "PC_Protocol.h"

uint8_t cmd_buf[COMMAND_FRAME_LEN] = {0};
uint8_t response_buf[RESPONSE_FRAME_LEN];

bool checkCRC(uint8_t* buf) {
	return true;
};

void calculateCRC(uint8_t* buf) {
	return;
}

void setErrorResponse() {
	return;
};

void parserCMD() {
	cmd_buf = getPCCommand();
	if (!checkCRC(cmd_buf)) {
	  setErrorResponse();
	  return;
	}

	__HAL_TIM_SET_COUNTER(&htim11, 0);

	switch(cmd_buf[0]) {
	case CRC_ERROR:

		break;
	case GET_STATUS:
		break;
	case EQUATORIAL_MEASUREMENT:
		break;

	}




}
