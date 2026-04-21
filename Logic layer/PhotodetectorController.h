#ifndef PHOTODETECTORCONTROLLER_H_
#define PHOTODETECTORCONTROLLER_H_

#include <stdint.h>
#include <stdbool.h>

#define CALIB_DATA_SAMPLES_NUM 50

void setParamsADC(uint8_t coeff_val, uint8_t ADC_freq);
void handleCoeffSetting();
bool isSuccessCoeffSetting();
bool isCalibrationEnd();
bool isCalibrationSuccess();
void initADCCalibration();
uint8_t* getADCValue();
void pollPD();

#endif /* PHOTODETECTORCONTROLLER_H_ */
