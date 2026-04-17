#include <stdint.h>

#include "Encoder.h"
#include "Motor.h"

typedef struct  {
	encoder_t* encoder;
	motor_t* motor;
	uint32_t offset_position;
} platform_t;

extern platform_t horizontal, vertical;
