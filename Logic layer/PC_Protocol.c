#include "FSMGonio.h"
#include "PC_Protocol.h"
#include "MeasurementController.h"
#include "PC_Communication.h"
#include "Timer.h"
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

void setError(uint8_t error_code) {
	return;
}

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

void sendPreviousResponse() {
	return;
};

bool isADCDataAvailable() {
	return true;
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
		sendPreviousResponse();
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
	case EMERGENCY_STOP:
		sendResponseOnCMD(EMERGENCY_STOP, CMD_ACCEPTED);
		//stopCurrentAction();
		cur_action = NONE_ACTION;
		work_status = READY_STATUS;
		break;
	case GET_ADC_DATA:
		//sendDataPacket();
		break;
	case GET_ERROR_CODE:
		//sendErrorPacket();
		cur_action = NONE_ACTION;
		work_status = READY_STATUS;
		setFSMGlobalState(INIT_STATE);
		setFSMActionState(NONE_ACTION);
		break;
	case TEST_ANGLE_ROTATION:
		sendResponseOnCMD(TEST_ANGLE_ROTATION, CMD_ACCEPTED);
		initTestRotation(cmd_buf[1], cmd_buf[2], cmd_buf[3]);
		cur_action = TEST_ANGLE_OFFSET;
		work_status = BUSY_STATUS;
		break;
	case SET_ADC_PARAMS:
		sendResponseOnCMD(SET_ADC_PARAMS, CMD_ACCEPTED);
		stopUpdatePDData();
		//initSettingADC();
		cur_action = CALIBRATION;
		work_status = BUSY_STATUS;
		break;
	case SET_PLATFORM_OFFSET:
		sendResponseOnCMD(SET_PLATFORM_OFFSET, CMD_ACCEPTED);
		setOffsetPosition();
		break;
	case START_ADC_CALIBRATION:
		sendResponseOnCMD(START_ADC_CALIBRATION, CMD_ACCEPTED);
		stopUpdatePDData();
		cur_action = CALIBRATION;
		work_status = BUSY_STATUS;
		initADCCalibration();
		setFSMGlobalState(CALIBRATION_STATE);
		setFSMActionState(ACCUMULATION_PD_DATA);
		break;
	case ACTIVE_HORIZONTAL_PLATFORM:
		sendResponseOnCMD(ACTIVE_HORIZONTAL_PLATFORM, CMD_ACCEPTED);
		setActivePlatform(cmd_buf[1]);
		break;
	}
}
