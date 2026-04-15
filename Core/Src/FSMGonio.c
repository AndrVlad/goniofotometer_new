/*
 * FSMGonio.c
 *
 *  Created on: Apr 14, 2026
 *      Author: Admin
 */

#include "Common.h"
#include "FSMGonio.h"

enum FSMGlobalState curStateGlobal = INIT_STATE;

void setFSMGlobalState(uint8_t state) {
	curStateGlobal = state;
}

void dispatchFSMGlobal() {
	switch(curStateGlobal) {
	case IDLE_STATE:

		if (uart1_rx_complete) {
			uart1_rx_complete = 0;
		}

		if (uart3_rx_complete) {
			parserCMD();
		}

		if (spi3_rx_complete || spi4_rx_complete) {
			spi3_rx_complete = spi4_rx_complete = 0;
		}

		break;
	case DYNAMIC_MEASUREMENT_STATE:
		dispatchFSMMeasurement();
		break;
	case STATIC_MEASUREMENT_STATE:
		dispatchFSMMeasurement();
		break;
	case ERROR_STATE:

		if (uart1_rx_complete) {
			uart1_rx_complete = 0;
		}

		if (uart3_rx_complete) {
			parserCMD();
		}

		if (spi3_rx_complete || spi4_rx_complete) {
			spi3_rx_complete = spi4_rx_complete = 0;
		}

		break;
	case CALIBRATION_STATE:



		break;
	case TEST_ROTATION_STATE:

		if (uart1_rx_complete) {
			uart1_rx_complete = 0;
		}

		if (uart3_rx_complete) {
			parserCMD();
		}

		if (spi3_rx_complete || spi4_rx_complete) {
			spi3_rx_complete = spi4_rx_complete = 0;
		}

		break;
	}
}
