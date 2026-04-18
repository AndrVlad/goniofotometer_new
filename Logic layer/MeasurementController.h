#ifndef MEASUREMENT_CONTROLLER_H
#define MEASUREMENT_CONTROLLER_H
#include "Platform.h"

#define ACCEL_OFFSET 5

enum meas_type_t {
	EQUATORIAL,
	MERIDIONAL
};

typedef struct {
	enum meas_type_t meas_type;
	platform_t* platform;
	uint32_t accel_pos;
	uint32_t start_pos;
	uint32_t end_pos;
	uint32_t meas_step;
	uint32_t next_step_val;
} measurement_t;

void handleDynamicMeasurement();
void initDynamicMeasurement(enum meas_type_t meas_type, uint16_t start_angle_item, uint16_t end_angle_item, uint16_t step_item);
void handleStaticMeasurement();
void initStaticMeasurement();
void setActivePlatform(uint8_t platf_id);

#endif
