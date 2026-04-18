#ifndef PC_PROTOCOL_H
#define PC_PROTOCOL_H

#define RESPONSE_FRAME_LEN 			33
#define CMD_FRAME_LEN 				6

#define CRC_ERROR 					0x0
#define GET_STATUS 					0x1
#define EQUATORIAL_MEASUREMENT		0x2
#define MERIDIONAL_MEASUREMENT		0x3
#define STATIC_MEASUREMENT 			0x5
#define ACTIVE_HORIZONTAL_PLATFORM	0xA

void parserCMD();

#endif
