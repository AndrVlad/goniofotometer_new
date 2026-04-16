/*
 * FSMGonio.c
 *
 *  Created on: Apr 14, 2026
 *      Author: Admin
 */

#include "Common.h"
#include "FSMGonio.h"

enum FSMGlobalState curStateGlobal = INIT_STATE;
enum FSMActionState curActionState = NONE_ACTION;

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

		if (uart3_rx_complete) {
			urart3_rx_complete = 0;
			parserCMD();
		}

		if (spi3_rx_complete || spi4_rx_complete) {
			spi3_rx_complete = spi4_rx_complete = 0;
		}

		dispatchDynamicMeasurement();

		break;
	case STATIC_MEASUREMENT_STATE:
		dispatchStaticMeasurement();
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
			uart3_rx_complete = 0;
			parserCMD();
		}

		if (spi3_rx_complete || spi4_rx_complete) {
			spi3_rx_complete = spi4_rx_complete = 0;
			dispatchTestRotation();
		}

		break;
	}
}

void dispatchTestRotation() {
	switch (curActionState) {
	case ACCELERATION:
		handleTestRotation(); // осуществляет останов и смену состояний.
		if (isMotorAccelerated(motor)) {
			setFSMGlobalState(MOVING);
		} else {
			if (tim4_ovflw) {
				tim4_ovflw = 0;
				accelerateMotor(motor);
			}
		}
		break;
	case MOVING:
		break;
		handleTestRotation();
	}
}

void dispatchDynamicMeasurement() {
	switch (curActionState) {
	case ACCELERATION:
		if (isMotorAccelerated(motor)) {
			setFSMGlobalState(MOVING);
		} else {
			if (tim4_ovflw) {
				tim4_ovflw = 0;
				accelerateMotor(motor);
			}
		}
		break;
	case MOVING:
	case POLL_PD:
		if (uart1_rx_complete) {
			uart1_rx_complete = 0;
			savePhotodetectorData();
		}
		 // получает последнее значение с энкодера, триггерит АЦП и отслеживает позиционирование, сменяя флаг.
		handleDynamicMeasurement();
		break;
	case DECELERATION:
		if (isMotorStopped(motor)) {
			setFSMGlobalState(IDLE_STATE);
		} else {
			if (tim12_ovflw) {
				tim12_ovflw = 0;
				decelerateMotor();
			}
		}
		break;
	}
};


