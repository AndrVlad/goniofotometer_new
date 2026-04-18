#include "MeasurementController.h"
#include "FSMGonio.h"
#include "PC_Protocol.h"
#include "Platform.h"
#include "Encoder.h"
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
bool reach_start_position, reach_accel_position, reach_end_position = 0;

measurement_t measurement;

void setActivePlatform(uint8_t platf_id) {
	if(platf_id == VERTICAL_PL) {
		measurement.platform = &vertical;
	} else {
		measurement.platform = &horizontal;
	}
	setCurrentPlatform(measurement.platform);
}

uint32_t calculateEncPosition(uint32_t val) {
	uint32_t result = 0;
	return result;
}

void handleDynamicMeasurement() {
	  // State - move to acceleration position
	  if (!reach_accel_position) {
		  //trans_states = 1;
		  if ((measurement.platform->encoder->cur_value >= measurement.accel_pos - ENC_TOLERANCE)
				  && (measurement.platform->encoder->cur_value <= measurement.accel_pos + ENC_TOLERANCE)) {

			  if (!isPlatformRotationForward()) {
				  stopPlatform();
				  invertPlatformRotation();
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
			  trans_states = 0;

			  if ((measurement.platform->encoder->cur_value >= measurement.start_pos - ENC_TOLERANCE)
					  && (measurement.platform->encoder->cur_value <= measurement.start_pos + ENC_TOLERANCE)) {

				  reach_start_position = 1;

				  pollPhotodetector();
			  }
		  }

		  // State - move to end position
		  if (reach_start_position) {

			  if (!reach_end_position) {

				  if ((encoder1_data >= end_position_drv1) && (encoder1_data <= end_position_drv1 + ENCODER_TOLERANCE)) {

					  HAL_UART_Receive_DMA(&huart1, uart1_rx_buffer, 5);
					  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_SET);
					  wait_adc_data_flag = 1;
					  //encoder_data_buf_trg[enc_cnt_trg] = encoder1_data;
					  //enc_cnt_trg++;
					  usDelay(30);
					  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_RESET);
					  test_counter_adc_data2++;
					  reach_end_position = 1;
					  return;

					  /* was here
					  // measurement end but adc buffer is not empty
					  if (data_buf_counter > 0) {
						  // clearing the part of the buffer that does not include useful data
						  clearSpecifiedElemOfBuffer(adc_data_buf,33,data_buf_counter*3+1);
						  data_status = _READY_;
					  }

					  // reset flags and state
					  data_buf_counter = 0;
					  data_elem_cnt = 1;
					  cur_action = NONE;
					  wait_flag = 0;
					  ready_status = READY_;
					  reach_end_position = 1;
					  wait_adc_data_flag = 0;

					  // stop measurement
					  HAL_TIM_Base_Stop_IT(&htim2); // stop motor
					  HAL_TIM_Base_Stop_IT(&htim7); // stop SPI timer */

				  } else {
					  // while not reached end_position
					  /* normal rotation */
					  /*
					  if ((encoder1_data >= (encoder1_increment_res - 4)) && (encoder1_data <= (encoder1_increment_res + 4))) {
					 		encoder1_increment_res += meas_res_drv1;
						  if (encoder1_increment_res >= ENCODER_RESOLUTION) {
							  encoder1_increment_res -= ENCODER_RESOLUTION;
						  }
						  */
					/* normal rotation end */
					  /* reverse rotation */
					  if ((encoder1_data >= (encoder1_increment_res - 4)) && (encoder1_data <= (encoder1_increment_res + 4))) {

						  if ((encoder1_increment_res - meas_res_drv1) < 0) {
							  encoder1_increment_res = ENCODER_RESOLUTION - abs(encoder1_increment_res - meas_res_drv1);
						  } else {
							  encoder1_increment_res -= meas_res_drv1;
						  }
						/* reverse rotation end */

						HAL_UART_Receive_DMA(&huart1, uart1_rx_buffer, 5);

						HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_SET);
						wait_adc_data_flag = 1;
						//encoder_data_buf_trg[enc_cnt_trg] = encoder1_data;
						//enc_cnt_trg++;
						usDelay(30);

						HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_RESET);
						test_counter_adc_data2++;

					  }

					  if (full_rotation) {
						if ((encoder1_data >= control_pos - 60) && (encoder1_data <= control_pos + 60)) {
							end_position_drv1 = start_position_drv1;
						}
					  }

				  }
			  }
		  }
	  }

	  if (reach_end_position && !wait_adc_data_flag && data_status == NONE_) {
		  if (data_buf_counter > 0) {
			  // clearing the part of the buffer that does not include useful data
			  clearSpecifiedElemOfBuffer(adc_data_buf,33,data_buf_counter*3+1);
			  memcpy(adc_data_buf_safe, adc_data_buf,33);
			  data_status = _READY_;
		  }

		  // reset flags and state
		  data_buf_counter = 0;
		  data_elem_cnt = 1;
		  cur_action = NONE;
		  wait_flag = 0;
		  ready_status = READY_;
		  reach_end_position = 1;
		  wait_adc_data_flag = 0;

		  stop_poll = 0;

		  resetNVICPriority();

		  // stop measurement
		  stopMotorRotationReq(chosen_drv);
		  //stopMotorRotation(chosen_drv);
		  //HAL_TIM_Base_Stop_IT(&htim2); // stop motor
		  //HAL_TIM_Base_Stop_IT(&htim7); // stop SPI timer
	  }
	return;
}

void initDynamicMeasurement(enum meas_type_t meas_type, uint16_t start_angle_item, uint16_t end_angle_item, uint16_t step_item) {

	uint16_t accel_angle, start_angle, end_angle, step;

	if (meas_type == MERIDIONAL) {
		setActivePlatform(VERTICAL_PL);
	}

	start_angle = (range_angle_items[start_angle_item-1]);
	end_angle = 360 - range_angle_items[end_angle_item-1];
	accel_angle = start_angle + ACCEL_OFFSET;
	step = step_angle_items[step_item-1];

	// reset flags
	reach_start_position = reach_accel_position = reach_end_position = 0;

	measurement.accel_pos = calculateEncPosition(((accel_angle * ENCODER_RESOLUTION) / 360));
	measurement.start_pos = calculateEncPosition(((start_angle * ENCODER_RESOLUTION) / 360));
	measurement.end_pos = calculateEncPosition(((end_angle * ENCODER_RESOLUTION) / 360));
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

		measurement.end_pos = calculateEncPosition((((end_angle+4) * ENCODER_RESOLUTION) / 360));
	}

	setFSMGlobalState(DYNAMIC_MEASUREMENT_STATE);
	setFSMActionState(ACCELERATION);

	setPlatformSpeed(DEFAULT_MOTOR_FREQ);
	setPlatformDirection(measurement.accel_pos);
	startPlatformRotation();
};

void handleStaticMeasurement() {
	return;
}
void initStaticMeasurement() {
	return;
}

void savePhotodetectorData() {
	return;
};

bool isPlatformReachStartPosition() {
	return reach_start_position;
};

bool isPlatformReachEndPosition() {
	return reach_end_position;
}
