#include "FSMGonio.h"
#include "PC_Protocol.h"
#include "MeasurementController.h"
#include "PC_Communication.h"
#include "Timer.h"
#include "PhotodetectorController.h"
#include "Platform.h"
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

enum data_status_t {
	DATA_NOT_READY,
	DATA_READY_FULL,
	DATA_READY_NOT_COMPLETELY
};

uint8_t cmd_buf[CMD_FRAME_LEN] = {0};
uint8_t* cmd_buf_ptr = NULL;
uint8_t response_buf[RESPONSE_FRAME_LEN];
enum status_current_action_t cur_action = NONE;
enum work_status_t work_status = READY_STATUS;
enum data_status_t data_status = DATA_NOT_READY;
bool transition_state, stop_poll_PD = 0;
uint8_t last_error_code = 0;

void saveOffsetCalibrationData(uint32_t offset) {
	return;
}

void setError(uint8_t error_code) {
	last_error_code = error_code;
	setFSMGlobalState(ERROR_STATE);
	work_status = ERROR_STATUS;
	return;
}

bool checkCRC(uint8_t* buf) {
	return true;
};

void calculateCRC(uint8_t* buf) {
	return;
}

void clearBuffer(uint8_t *buf, uint8_t size){
	for(uint8_t i = 0; i < size-1; i++) {
		buf[i] = 0;
	}
}

void sendErrorResponse() {
	clearBuffer(response_buf,RESPONSE_FRAME_LEN);

	response_buf[0] = response_buf[31] = CRC_ERROR;

	sendAnswerToPC(response_buf, RESPONSE_FRAME_LEN);
	return;
};

void sendErrorResponseCode() {
	clearBuffer(response_buf,RESPONSE_FRAME_LEN);

	response_buf[0] = response_buf[31] = GET_ERROR_CODE;
	response_buf[1] = response_buf[32] = last_error_code;

	sendAnswerToPC(response_buf, RESPONSE_FRAME_LEN);
	return;
};

void stopUpdatePDData() {
	stop_poll_PD = true;
	return;
}

void resetUpdatePDData() {
	stop_poll_PD = false;
}

uint8_t getWorkStatus() {
	return work_status;
};

uint8_t getADCDataStatus() {

	return data_status;
}

uint8_t getCurrentAction() {
	uint8_t action = 0;
	return action;
};

void sendResponseOnCMD(uint8_t cmd_code, enum response_t response) {

	clearBuffer(response_buf,RESPONSE_FRAME_LEN);
	uint32_t crc;

	if (cmd_code != GET_STATUS) {
		response_buf[0] = cmd_code;
		response_buf[1] = response;
		response_buf[31] = cmd_code;
		response_buf[32] = response;
	} else {
		uint32_t encoder_val1 = getInvertedEncoderVal(0);
		uint32_t encoder_val2 = getInvertedEncoderVal(1);
		uint8_t* pd_data = getADCValue();
		uint32_t offset1 = getOffsetPosition(0);
		uint32_t offset2 = getOffsetPosition(1);

		response_buf[0] = GET_STATUS;
		response_buf[1] = getWorkStatus();
		response_buf[2] = getCurrentAction();
		response_buf[3] = transition_state;
		response_buf[4] = getADCDataStatus();
		response_buf[6] = pd_data[0];
		response_buf[7] = pd_data[1];
		response_buf[8] = pd_data[2];
		response_buf[9] = encoder_val1 & 0xFF;
		response_buf[10] = encoder_val1 >> 8;
		response_buf[11] = encoder_val1 >> 16;
		response_buf[12] = offset1 & 0xFF;
		response_buf[13] = offset1 >> 8;
		response_buf[14] = offset1 >> 16;
		response_buf[15] = encoder_val2 & 0xFF;
		response_buf[16] = encoder_val2 >> 8;
		response_buf[17] = encoder_val2 >> 16;
		response_buf[18] = offset2 & 0xFF;
		response_buf[19] = offset2 >> 8;
		response_buf[20] = offset1 >> 16;
	}

	// CRC calculation
	for (int i = 0; i < 30; i+=2) {
		crc += (uint16_t)response_buf[i] + ((uint16_t)(response_buf[i+1])<<8);
	}
	crc += response_buf[30];
	*(uint16_t*)(response_buf+31) = crc;

	sendAnswerToPC(response_buf, RESPONSE_FRAME_LEN);

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
	  sendErrorResponse();
	  return;
	}

	resetKeepAliveTimer();

	switch(cmd_buf[0]) {
	case CRC_ERROR:
		sendPreviousResponse();
		break;
	case GET_STATUS:

		pollEncoder(0);
		pollEncoder(1);

		if (!stop_poll_PD) {
			getADCValue();
		}

		sendResponseOnCMD(GET_STATUS, CMD_ACCEPTED);

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
		sendErrorResponseCode();
		cur_action = NONE_ACTION;
		work_status = READY_STATUS;
		setFSMGlobalState(IDLE_STATE);
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
		setParamsADC(cmd_buf[1], cmd_buf[2]);
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
