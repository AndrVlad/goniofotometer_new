#include "Common.h"
#include "FSMGonio.h"
#include "MeasurementController.h"
#include "PC_Protocol.h"
#include "Platform.h"
#include "PhotodetectorController.h"

void dispatchDynamicMeasurement();
void dispatchStaticMeasurement();
void dispatchCalibration();
void dispatchTestRotation();

enum FSMGlobalState curStateGlobal = INIT_STATE;
enum FSMActionState curActionState = NONE_ACTION;

uint8_t getFSMActionState() {
	return curActionState;
}

uint8_t getFSMGlobalState() {
	return curStateGlobal;
}

void setFSMGlobalState(uint8_t state) {
	curStateGlobal = state;
}

void setFSMActionState(uint8_t state) {
	curActionState = state;
}

void resetGonio() {
	setFSMGlobalState(ERROR_STATE);
	setFSMActionState(NONE_ACTION);
	stopMeasurement();
	resetProtocolModule();
};

void dispatchFSMGlobal() {

	if(isErrorOccured()) {
		setFSMGlobalState(ERROR_STATE);
		setFSMActionState(NONE_ACTION);
	}

	switch(curStateGlobal) {
	case IDLE_STATE:

		if (uart1_rx_complete) {
			uart1_rx_complete = 0;
		}

		if (uart3_rx_complete) {
			uart3_rx_complete = 0;
			parserCMD();
		}

		break;
	case DYNAMIC_MEASUREMENT_STATE:

		if (uart3_rx_complete) {
			uart3_rx_complete = 0;
			parserCMD();
		}

		dispatchDynamicMeasurement();
		break;
	case STATIC_MEASUREMENT_STATE:

		if (uart3_rx_complete) {
			uart3_rx_complete = 0;
			parserCMD();
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

		break;
	case CALIBRATION_STATE:

		if (uart3_rx_complete) {
			parserCMD();
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

		dispatchTestRotation();

		break;
	}
}

void dispatchTestRotation() {
	switch (curActionState) {
	case ACCELERATION:
		// вызов обработчика пробного вращения
		handleTestRotation();
		if (isPlatformAccelerated()) { 	// платформа разогнана
			setFSMActionState(MOVING);	// смена состояния
		} else {	// платформа не разогнана
			if (tim4_ovflw) {
				tim4_ovflw = 0;
				// обработчик увеличения частоты вращения ШД
				acceleratePlatform();
			}
		}
		break;
	case MOVING:
		if(isPlatformReachTestPosition()) { // платформа достигла заданной позиции
			setFSMActionState(DECELERATION);
			// выполнение остановки платформы
			stopPlatform();
		}
		handleTestRotation();
		break;

	case DECELERATION:
		if (isPlatformStopped()) { // по остановке платформы сбросить состояние и подсостояния
			setFSMGlobalState(IDLE_STATE);
			setFSMActionState(NONE_ACTION);
		}
		break;
	}
	return;
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
		handleDynamicMeasurement();
		break;
	case POLL_PD:
		if (uart1_rx_complete) {
			uart1_rx_complete = 0;
			savePhotodetectorData();
		}

		if (isPlatformReachEndPosition()) {
			setFSMActionState(DECELERATION);
		}

		handleDynamicMeasurement();
		break;
	case DECELERATION:
		if (uart1_rx_complete) {
			uart1_rx_complete = 0;
			savePhotodetectorData();
		}
		if (isPlatformStopped() && isADCDataAvailable()) {
			if (isADCDataAvailable()) {
				setFSMActionState(WAITING);
			} else {
				setFSMGlobalState(IDLE_STATE);
				setFSMActionState(NONE_ACTION);
			}

		} else {
			if (tim12_ovflw) {
				tim12_ovflw = 0;
				deceleratePlatform();
			}
		}
		break;
	case WAITING:
		if (!isADCDataAvailable()) {
			setFSMGlobalState(IDLE_STATE);
			setFSMActionState(NONE_ACTION);
		}
		break;
	}
}

void dispatchStaticMeasurement() {

	switch(curActionState) {
	case POLL_PD:
		if (tim14_ovflw) {
			pollPD();
		}

		if (uart1_rx_complete) {
			uart1_rx_complete = 0;
			savePhotodetectorData();
		}

		if (tim5_ovflw) {
			setFSMActionState(WAITING);
		}
		break;
	case WAITING:
		if (uart1_rx_complete) {
			uart1_rx_complete = 0;
			savePhotodetectorData();
		}

		if (!isADCDataAvailable()) {
			setFSMGlobalState(IDLE_STATE);
			setFSMActionState(NONE_ACTION);
		}
		break;
	}
	return;
}

void dispatchCalibration() {
	switch (curActionState) {
	case COEFF_SETTING:
		if (uart1_rx_complete) {
			uart1_rx_complete = 0;
			handleCoeffSetting();
			if (!isADCDataAvailable()) {
				setFSMActionState(NONE_ACTION);
				setFSMGlobalState(IDLE_STATE);
			}

		}
		break;
	case ACCUMULATION_PD_DATA:

		if(tim10_ovflw) {
			pollPhotodetector();
		}

		if (uart1_rx_complete) {
			uart1_rx_complete = 0;
			handleCalibration();
		}

		if (isCalibrationEnd() && isADCDataAvailable()) {
			setFSMActionState(WAITING);
		}

		break;
	case WAITING:
		if (!isADCDataAvailable()) {
			setFSMGlobalState(IDLE_STATE);
			setFSMActionState(NONE_ACTION);
		}
		break;
	}
	return;
}



