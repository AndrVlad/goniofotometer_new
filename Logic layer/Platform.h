#include <stdint.h>

#include "Encoder.h"
#include "Motor.h"

typedef struct platform_t {
	encoder_t* encoder;
	motor_t* motor;
	uint32_t offset_position;
};

extern platform_t horizontal, vertical;
