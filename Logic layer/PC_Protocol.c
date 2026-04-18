#include "FSMGonio.h"
#include "PC_Protocol.h"
#include "MeasurementController.h"
#include "PC_Communication.h"
#include <stdint.h>
#include <stdbool.h>

enum status_current_action_t {
	NONE,
	EQUATORIAL_ACTION,
	MERIDIONAL_ACTION,
	STATIC = 4,
	CALIBRATION,
	TEST_TURN,
	TEST_ANGLE_OFFSET = 8,
};

enum work_status_t {
	ERROR_STATUS,
	READY_STATUS,
	BUSY_STATUS
};

enum response_t {
	CMD_ERROR,
	CMD_ACCEPTED
};

uint8_t cmd_buf[CMD_FRAME_LEN] = {0};
uint8_t* cmd_buf_ptr = NULL;
uint8_t response_buf[RESPONSE_FRAME_LEN];
enum status_current_action_t cur_action;
enum work_status_t work_status;


bool checkCRC(uint8_t* buf) {
	return true;
};

void calculateCRC(uint8_t* buf) {
	return;
}

void setErrorResponse() {
	return;
};

void stopUpdatePDData() {
	return;
}

void sendResponseOnCMD(uint8_t cmd_code, enum response_t response) {
	return;
}

void parserCMD() {
	cmd_buf_ptr = getPCCommand();
	if (!checkCRC(cmd_buf)) {
	  setErrorResponse();
	  return;
	}

	resetKeepAliveTimer();

	switch(cmd_buf[0]) {
	case CRC_ERROR:

		break;
	case GET_STATUS:
		break;
	case EQUATORIAL_MEASUREMENT:
		sendResponseOnCMD(EQUATORIAL_MEASUREMENT, CMD_ACCEPTED);
		stopUpdatePDData();
		initDynamicMeasurement(EQUATORIAL,cmd_buf[1],cmd_buf[2],cmd_buf[3]);

		// set current action
		cur_action = EQUATORIAL_ACTION;

		// set status
		work_status = BUSY_STATUS;

		break;
	case MERIDIONAL_MEASUREMENT:
		sendResponseOnCMD(MERIDIONAL_MEASUREMENT, CMD_ACCEPTED);
		stopUpdatePDData();
		initDynamicMeasurement(MERIDIONAL,cmd_buf[1],cmd_buf[2],cmd_buf[3]);
		// set current action
		cur_action = MERIDIONAL_ACTION;

		// set status
		work_status = BUSY_STATUS;
		break;
	case ACTIVE_HORIZONTAL_PLATFORM:
		setActivePlatform(cmd_buf[1]);
		break;

	}
}
