
enum meas_type_t {
	EQUATORIAL,
	MERIDIONAL
};

struct measurement_t {
	meas_type_t meas_type;
	platform_t platform;
	uint32_t accel_pos;
	uint32_t start_pos;
	uint32_t end_pos;
	uint32_t meas_step;
};

void handleDynamicMeasurement();
void initDynamicMeasurement();
void handleStaticMeasurement();
void initStaticMeasurement();
