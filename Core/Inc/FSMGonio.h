/*
 * FSMGonio.h
 *
 *  Created on: Apr 14, 2026
 *      Author: Admin
 */

#ifndef INC_FSMGONIO_H_
#define INC_FSMGONIO_H_

enum FSMGlobalState {
	INIT_STATE,
	IDLE_STATE,
	DYNAMIC_MEASUREMENT_STATE,
	STATIC_MEASUREMENT_STATE,
	ERROR_STATE,
	CALIBRATION_STATE,
	TEST_ROTATION_STATE
};

void dispatchFSMGlobal();
void setFSMGlobalState(uint8_t state);

#endif /* INC_FSMGONIO_H_ */
