/*
 * FSMGonio.c
 *
 *  Created on: Apr 14, 2026
 *      Author: Admin
 */

#include "Common.h"
#include "FSMGonio.h"
#include "MeasurementController.h"
#include "PC_Protocol.h"
#include "Platform.h"

void dispatchDynamicMeasurement();
void dispatchStaticMeasurement();
void dispatchCalibration();
void handleTestRotation();

enum FSMGlobalState curStateGlobal = INIT_STATE;
enum FSMActionState curActionState = NONE_ACTION;

void setFSMGlobalState(uint8_t state) {
	curStateGlobal = state;
}

void setFSMActionState(uint8_t state) {
	curActionState = state;
}

void dispatchFSMGlobal() {
	switch(curStateGlobal) {
	case IDLE_STATE:

		if (uart1_rx_complete) {
			uart1_rx_complete = 0;
		}

		if (uart3_rx_complete) {
			uart3_rx_complete = 0;
			parserCMD();
		}

		if (spi3_rx_complete || spi4_rx_complete) {
			spi3_rx_complete = spi4_rx_complete = 0;
		}

		break;
	case DYNAMIC_MEASUREMENT_STATE:

		if (uart3_rx_complete) {
			uart3_rx_complete = 0;
			parserCMD();
		}

		if (spi3_rx_complete || spi4_rx_complete) {
			spi3_rx_complete = spi4_rx_complete = 0;
		}

		dispatchDynamicMeasurement();
		break;
	case STATIC_MEASUREMENT_STATE:

		if (uart3_rx_complete) {
			uart3_rx_complete = 0;
			parserCMD();
		}

		if (spi3_rx_complete || spi4_rx_complete) {
			spi3_rx_complete = spi4_rx_complete = 0;
		}

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

		if (uart3_rx_complete) {
			parserCMD();
		}

		if (spi3_rx_complete || spi4_rx_complete) {
			spi3_rx_complete = spi4_rx_complete = 0;
		}

		dispatchCalibration();

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
		if (isPlatformAccelerated()) {
			setFSMActionState(MOVING);
		} else {
			if (tim4_ovflw) {
				tim4_ovflw = 0;
				acceleratePlatform();
			}
		}
		break;
	case MOVING:
		break;
		handleTestRotation();
	case DECELERATION:
		if (isPlatformStopped()) {
			setFSMGlobalState(IDLE_STATE);
			setFSMActionState(NONE_ACTION);
		}
		break;
	}

}

void dispatchDynamicMeasurement() {
	switch (curActionState) {
	case ACCELERATION:
		if (isPlatformAccelerated()) {
			setFSMActionState(MOVING);
		} else {
			if (tim4_ovflw) {
				tim4_ovflw = 0;
				acceleratePlatform();
			}
		}
		break;
	case MOVING:
		if (isPlatformReachStartPosition()) {
			setFSMActionState(POLL_PD);
		}
	case POLL_PD:
		if (uart1_rx_complete) {
			uart1_rx_complete = 0;
			savePhotodetectorData();
		}

		if (isPlatformReachEndPosition()) {
			setFSMActionState(DECELERATION);
		}

		 // получает последнее значение с энкодера, триггерит АЦП и отслеживает позиционирование, сменяя флаг.
		handleDynamicMeasurement();
		break;
	case DECELERATION:
		if (isPlatformStopped()) {
			setFSMGlobalState(IDLE_STATE);
			setFSMActionState(NONE_ACTION);
		} else {
			if (tim12_ovflw) {
				tim12_ovflw = 0;
				deceleratePlatform();
			}
		}
		break;
	}
}

void dispatchStaticMeasurement() {
	return;
}

void dispatchCalibration() {
	return;
}

void handleTestRotation() {
	return;
}

