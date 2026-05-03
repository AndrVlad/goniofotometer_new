#ifndef PC_PROTOCOL_H
#define PC_PROTOCOL_H

#include <stdbool.h>

#define RESPONSE_FRAME_LEN 			33
#define CMD_FRAME_LEN 				6

#define CRC_ERROR 					0xFF
#define GET_STATUS 					0x1
#define EQUATORIAL_MEASUREMENT		0x2
#define MERIDIONAL_MEASUREMENT		0x3
#define STATIC_MEASUREMENT 			0x5
#define EMERGENCY_STOP				0x7
#define ACTIVE_HORIZONTAL_PLATFORM	0xA
#define GET_ADC_DATA				0xB
#define GET_ERROR_CODE				0xC
#define TEST_ANGLE_ROTATION			0x10
#define SET_ADC_PARAMS				0x14
#define SET_PLATFORM_OFFSET			0x17
#define START_ADC_CALIBRATION		0x1A

#define ADC_CRC_ERROR				0x02

bool isADCDataAvailable();
bool isErrorOccured();
void parserCMD();
void setError(uint8_t error_code);
void saveOffsetData(uint32_t);
void saveOffsetCalibrationData(uint32_t offset);
void savePhotodetectorData();
void resetProtocolModule();
void initProtocolModule();

#endif
