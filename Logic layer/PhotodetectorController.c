#include "PhotodetectorController.h"
#include "Photodetector.h"
#include "PC_Protocol.h"
#include "Timer.h"

enum adc_freq_t {
	FREQ_16_HZ,
	FREQ_242_HZ
};

uint8_t adc_params_tmp, data_counter, adc_data_cnt, calib_buf_cnt = 0;
bool coeff_setting_success, calibration_end, calibration_success = 0;
uint8_t calibration_buffer[CALIB_DATA_SAMPLES_NUM], adc_values_buf[CALIB_DATA_SAMPLES_NUM] = {0};

bool checkCRCPhotodetectorData(uint8_t* data_buf);

uint8_t* getADCValue() {
	uint8_t* pd_data;
	if(checkCRCPhotodetectorData(getPDData())) {
		return pd_data;
	} else {
		setError(ADC_CRC_ERROR);
	}
	return 0;
}

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

uint32_t calculateMedianVal(uint32_t* buf, uint16_t size, uint8_t limit) {
	uint8_t end_limit = size - (limit + 1);
	uint64_t median_val = 0;
	uint32_t result;
	for (uint16_t i = limit; i <= end_limit; i++) {
		median_val += buf[i];
	}
	result = median_val / (size - limit*2);
	return result;
}

void swap(uint32_t* a, uint32_t* b) {
    uint32_t tmp = *a;
    *a = *b;
    *b = tmp;
}

void bubbleSort(uint32_t *buf, uint16_t size)
{
	while (size--)
	{
		bool swapped = false;

		for (int i = 0; i < size; i++)
		{
			if (buf[i] > buf[i + 1])
			{
				swap(&buf[i], &buf[i + 1]);
				swapped = true;
			}
		}

		if (swapped == false)
			break;
	}
}

uint32_t getPDOffsetVal() {

	// преобразование значений АЦП
	uint32_t adc_values_buf[CALIB_DATA_SAMPLES_NUM];
	for (uint16_t i = 0, j = 0; i < CALIB_DATA_SAMPLES_NUM * 3; i += 3, j++) {
		adc_values_buf[j] = calibration_buffer[i];
		adc_values_buf[j] |= calibration_buffer[i+1] << 8;
		adc_values_buf[j] |= calibration_buffer[i+2] << 16;
	}

	// сортировка
	bubbleSort(adc_values_buf, CALIB_DATA_SAMPLES_NUM);

	// вычисление значения смещения
	uint32_t offset = calculateMedianVal(adc_values_buf, CALIB_DATA_SAMPLES_NUM, 12);
	return offset;
}

void handleCoeffSetting() {

	uint8_t* rx_buf = getPDData();
	if (checkCRCPhotodetectorData(rx_buf)) {
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

void initADCCalibration() {
	startCalibrationTimer();
	return;
}

void handleCalibration() {

	uint8_t* rx_buf = getPDData();

	if (!checkCRCPhotodetectorData(rx_buf)) {
		setError(0x2);
		calibration_end = 1;
		calibration_success = 0;
	}

	for (uint8_t i = 0; i < 3; i++, calib_buf_cnt++) {
	  calibration_buffer[calib_buf_cnt] = rx_buf[i];
	}

	adc_data_cnt++;

	if (!(adc_data_cnt == CALIB_DATA_SAMPLES_NUM)) {
	  return;
	} else {
		stopCalibrationTimer();
		uint32_t pd_offset_val = getPDOffsetVal();
		saveOffsetCalibrationData(pd_offset_val);
	}

	return;
};
