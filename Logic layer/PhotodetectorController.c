#include "PhotodetectorController.h"
#include "Photodetector.h"
#include "PC_Protocol.h"

enum adc_freq_t {
	FREQ_16_HZ,
	FREQ_242_HZ
};

uint8_t adc_params_tmp, data_counter, adc_data_cnt = 0;
bool coeff_setting_success, calibration_end, calibration_success = 0;
uint8_t calibration_buffer[CALIB_DATA_SAMPLES_NUM] = {0};

uint8_t getADCAmplifierValInverted(uint8_t value);

bool checkCRCPhotodetectorData(uint8_t* data_buf) {
	if ((((data_buf[0] + data_buf[1] + data_buf[2]) & 0xFF) == data_buf[3]) && (data_buf[4] == 0xA5)) {
		return true;
	}
	return false;
};

bool isCalibrationEnd() {
	return calibration_end;
};
bool isCalibrationSuccess() {
	return calibration_success;
}

bool isSuccessCoeffSetting() {
	return coeff_setting_success;
};

void setParamsADC(uint8_t coeff_val, uint8_t ADC_freq) {
	uint8_t adc_params;

	adc_params = getADCAmplifierValInverted(coeff_val);

	// определение содержимого команды для установки частоты дискретизации c инверсией второго полубайта
	if (ADC_freq == FREQ_242_HZ) { 	// частота дискретизации 242Гц
		adc_params |= 0b10000000;
	}

	if (ADC_freq == FREQ_16_HZ) {
		adc_params |= 0b00001000;
	}

	adc_params_tmp = adc_params;

	sendDataPD(adc_params_tmp);
};

uint8_t getADCAmplifierValInverted(uint8_t value) {

	switch(value) {
		case 1:
			return 0b00000111;
		case 2:
			return 0b00010110;
		case 4:
			return 0b00100101;
		case 8:
			return 0b00110100;
		case 16:
			return 0b01000011;
		case 32:
			return 0b01010010;
		case 64:
			return 0b01100001;
		case 128:
			return 0b01110000;
		default:
			return 1;
	}
}

void handleCoeffSetting() {

	uint8_t* rx_buf = getPDData();
	if (checkCRCPhotodetectorData(getPDData())) {
		// проверка на совпадение второго полубайта ответа с первым полубайтом запроса
		if (rx_buf[0] != (adc_params_tmp >> 4)) {
			setError(0x1);
			coeff_setting_success = 0;
			return;
		} else {
			coeff_setting_success = 1;
			return;
		}
	} else {
		setError(0x2);
		coeff_setting_success = 0;
	}
}

void handleCalibration() {

	uint8_t* rx_buf = getPDData();

	for (uint8_t i = 0; i < 3; i++, j++) {
	  calibration_buffer[j] = rx_buf[i];
	}

	adc_data_cnt++;

	if (!(adc_data_cnt == 50)) {
	  return;
	} else {
		HAL_TIM_Base_Stop_IT(&htim10);

			  convertAdcValues(uart1_rx_calibration_buffer, data_buf_counter * 3);
			  bubbleSort(adc_values_buf, data_buf_counter);
			  photodetector_offset_val = calculateMedianVal(adc_values_buf, data_buf_counter, 12);

			  data_buf_counter = 0;
			  data_elem_cnt_calib = 0;
			  wait_flag = 0;

			  clearBuffer(adc_data_buf,33);

			  adc_data_buf[1] = photodetector_offset_val;
			  adc_data_buf[2] = photodetector_offset_val >> 8;
			  adc_data_buf[3] = photodetector_offset_val >> 16;

			  adc_data_buf[4] = adc_data_buf[1];
			  adc_data_buf[5] = adc_data_buf[2];
			  adc_data_buf[6] = adc_data_buf[3];

			  data_status = _READY_;
			  end_calibration_flag = 1;
	}


	}

	if (end_calibration_flag) {
	  if (data_status == NONE_){
		  cur_action = NONE;
		  ready_status = READY_;
		  end_calibration_flag = 0;
	  }
	}



	stopCalibrationTimer();

	return;
};
