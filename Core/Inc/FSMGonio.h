#ifndef INC_FSMGONIO_H_
#define INC_FSMGONIO_H_

#include <stdint.h>

enum FSMGlobalState {
	INIT_STATE,
	IDLE_STATE,
	DYNAMIC_MEASUREMENT_STATE,
	STATIC_MEASUREMENT_STATE,
	ERROR_STATE,
	CALIBRATION_STATE,
	TEST_ROTATION_STATE
};

enum FSMActionState {
	NONE_ACTION,
	ACCELERATION,
	MOVING,
	POLL_PD,
	DECELERATION,
	COEFF_SETTING,
	WAITING,
	ACCUMULATION_PD_DATA
};

void dispatchFSMGlobal();
void setFSMGlobalState(uint8_t state);
void setFSMActionState(uint8_t state);

#endif /* INC_FSMGONIO_H_ */
