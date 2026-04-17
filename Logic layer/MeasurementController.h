
#include "Platform.h"

enum meas_type_t {
	EQUATORIAL,
	MERIDIONAL
};

typedef struct {
	enum meas_type_t meas_type;
	platform_t platform;
	uint32_t accel_pos;
	uint32_t start_pos;
	uint32_t end_pos;
	uint32_t meas_step;
} measurement_t;

void handleDynamicMeasurement();
void initDynamicMeasurement();
void handleStaticMeasurement();
void initStaticMeasurement();
