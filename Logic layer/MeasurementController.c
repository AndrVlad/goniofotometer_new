#include "MeasurementController.h"
#include "FSMGonio.h"
#include "PC_Protocol.h"
#include "Platform.h"
#include "Encoder.h"
#include "Photodetector.h"
#include "RingBuffer.h"
#include <stdbool.h>
#include <stdlib.h>

enum activePlatform {
	HORIZONTAL_PL = 0x0,
	VERTICAL_PL = 0xFF
};

uint8_t range_angle_items[8] 	= 	{180,150,120,90,60,30,10,5};
uint16_t step_angle_items[8] 	= 	{365,182,60,29,6,3,1,1820}; // The values are set in arc seconds.
uint32_t time_interval_items[9] = 	{36001000,18001000,6001000,601000,301000,101000,10000,5000,1000}; // values for TIMER_5 ARR
uint16_t time_step_items[12] 	= 	{50000,25000,10000,5000,2500,1000,500,250,100,50,25,10}; // values for TIMER ARR
int32_t end_position_tmp, control_position = 0;
bool full_rotation = 0;
bool reach_start_position, reach_accel_position, reach_end_position, reach_test_position = 0;

measurement_t measurement;

void setActivePlatform(uint8_t platf_id) {
	if(platf_id == VERTICAL_PL) {
		measurement.platform = &vertical;
	} else {
		measurement.platform = &horizontal;
	}
	setCurrentPlatform(measurement.platform);
}

uint32_t calculateEncPosition(uint32_t val, uint32_t offset) {
	uint32_t result = 0;
	return result;
}

void handleDynamicMeasurement() {
	  // State - move to acceleration position
	  if (!reach_accel_position) {
		  if ((measurement.platform->encoder->cur_value >= measurement.accel_pos - ENC_TOLERANCE)
				  && (measurement.platform->encoder->cur_value <= measurement.accel_pos + ENC_TOLERANCE)) {

			  if (!isPlatformRotationForward()) {
				  stopPlatform();
				  invertPlatformDirection();
				  startPlatformRotation();
				  setPlatformSpeed(measurement.meas_step);
			  } else {
				  setPlatformSpeed(measurement.meas_step);
			  }

			  reach_accel_position = 1;
		  }
	  }

	  // State - move to start position
	  if (reach_accel_position) {

		  if (!reach_start_position) {

			  if ((measurement.platform->encoder->cur_value >= measurement.start_pos - ENC_TOLERANCE)
					  && (measurement.platform->encoder->cur_value <= measurement.start_pos + ENC_TOLERANCE)) {

				  reach_start_position = 1;

				  pollPhotodetector();
			  }
		  }

		  // State - move to end position
		  if (reach_start_position) {

			  if (!reach_end_position) {

				  if ((measurement.platform->encoder->cur_value >= measurement.end_pos)
						  && (measurement.platform->encoder->cur_value <= measurement.end_pos + ENC_TOLERANCE)) {

					  pollPhotodetector();
					  reach_end_position = 1;
					  return;

				  } else {

					  if ((measurement.platform->encoder->cur_value >= (measurement.next_step_val - ENC_TOLERANCE))
							  && (measurement.platform->encoder->cur_value <= (measurement.next_step_val + ENC_TOLERANCE))) {

						  if ((measurement.next_step_val - measurement.meas_step) < 0) {
							  measurement.next_step_val = ENCODER_RESOLUTION - abs(measurement.next_step_val - measurement.meas_step);
						  } else {
							  measurement.next_step_val -= measurement.meas_step;
						  }

						  pollPhotodetector();
					  }

					  if (full_rotation) {
						  if ((measurement.platform->encoder->cur_value >= control_position - ENC_TOLERANCE)
								&& (measurement.platform->encoder->cur_value <= control_position + ENC_TOLERANCE)) {
							  measurement.platform->encoder->cur_value = end_position_tmp;
						  }
					  }

				  }
			  }
		  }
	  }

	return;
}

void initDynamicMeasurement(enum meas_type_t meas_type, uint16_t start_angle_item, uint16_t end_angle_item, uint16_t step_item) {

	uint16_t accel_angle, start_angle, end_angle, step;

	clearRingBuf();

	if (meas_type == MERIDIONAL) {
		setActivePlatform(VERTICAL_PL);
	}

	start_angle = (range_angle_items[start_angle_item-1]);
	end_angle = 360 - range_angle_items[end_angle_item-1];
	accel_angle = start_angle + ACCEL_OFFSET;
	step = step_angle_items[step_item-1];

	// reset flags
	reach_start_position = reach_accel_position = reach_end_position = 0;

	measurement.accel_pos = calculateEncPosition(((accel_angle * ENCODER_RESOLUTION) / 360),measurement.platform->offset_position);
	measurement.start_pos = calculateEncPosition(((start_angle * ENCODER_RESOLUTION) / 360),measurement.platform->offset_position);
	measurement.end_pos = calculateEncPosition(((end_angle * ENCODER_RESOLUTION) / 360),measurement.platform->offset_position);
	measurement.meas_step = step;

	if ((measurement.start_pos - measurement.meas_step) < 0) {
		measurement.next_step_val = ENCODER_RESOLUTION - abs(measurement.start_pos - measurement.meas_step);
	} else {
		measurement.next_step_val = measurement.start_pos - measurement.meas_step;
	}

	if (start_angle == 180 && end_angle == 180) {
		full_rotation = 1;
	} else {
		full_rotation = 0;
	}

	if (full_rotation) {

		end_position_tmp = measurement.end_pos;

		if ((end_position_tmp - 720) < 0) {
			control_position = ENCODER_RESOLUTION - abs(end_position_tmp - 720);
		} else {
			control_position = end_position_tmp - 720;
		}

		measurement.end_pos = calculateEncPosition((((end_angle+4) * ENCODER_RESOLUTION) / 360),measurement.platform->offset_position);
	}

	setFSMGlobalState(DYNAMIC_MEASUREMENT_STATE);
	setFSMActionState(ACCELERATION);

	setPlatformSpeed(DEFAULT_MOTOR_FREQ_HZ);
	setPlatformDirection(measurement.accel_pos);
	startPlatformRotation();
};

void handleStaticMeasurement() {
	return;
}
void initStaticMeasurement() {
	return;
}

void handleTestRotation() {

	return;
}

void initTestRotation(uint8_t lsb_angle, uint8_t msb_angle, uint8_t type) {
	uint32_t temp_pos, test_angle;
	// получение заданного угла из команды
	test_angle = 0;
	test_angle = msb_angle << 8;
	test_angle |= lsb_angle;
	test_angle = 360 - test_angle;

	temp_pos = (test_angle * ENCODER_RESOLUTION) / 360;

	if(type == ABSOLUTE) { // вращение на абсолютный угол по лимбу
		measurement.test_pos = calculateEncPosition(temp_pos,measurement.platform->offset_position);
	} else {			// вращение на угол относительно текущей позиции
		measurement.test_pos = calculateEncPosition(temp_pos,measurement.platform->encoder->cur_value);
	}

	setPlatformDirection(measurement.test_pos);
	startPlatformRotation();
	return;
};

bool isPlatformReachStartPosition() {
	return reach_start_position;
};

bool isPlatformReachEndPosition() {
	return reach_end_position;
}

bool isPlatformReachTestPosition() {
	return reach_test_position;
}
