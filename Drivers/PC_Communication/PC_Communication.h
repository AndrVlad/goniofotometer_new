/*
 * PC_Communication.h
 *
 *  Created on: Apr 14, 2026
 *      Author: Admin
 */

#ifndef PC_COMMUNICATION_PC_COMMUNICATION_H_
#define PC_COMMUNICATION_PC_COMMUNICATION_H_

#define CRC_ERROR 					0x0
#define GET_STATUS 					0x1
#define EQUATORIAL_MEASUREMENT		0x2
#define MERIDIONAL_MEASUREMENT		0x3
#define STATIC_MEASUREMENT 			0x5


void parserCMD();

#endif /* PC_COMMUNICATION_PC_COMMUNICATION_H_ */
