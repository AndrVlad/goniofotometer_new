#ifndef PLATFORM_H
#define PLATFORM_H

#include <stdint.h>

#include "Encoder.h"
#include "Motor.h"

typedef struct {
	encoder_t* encoder;
	motor_t* motor;
	uint32_t offset_position;
} platform_t;

extern platform_t horizontal, vertical;

void setOffsetPosition(platform_t* platform);
void setPlatformSpeed(uint32_t step);
void setCurrentPlatform(platform_t* platform);
void setPlatformDirection(uint32_t target_position);
void startPlatformRotation();

#endif
