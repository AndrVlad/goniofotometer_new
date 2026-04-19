#ifndef PLATFORM_H
#define PLATFORM_H

#include <stdint.h>
#include <stdbool.h>
#include "Encoder.h"
#include "Motor.h"

#define DEFAULT_MOTOR_FREQ_HZ 1500

typedef struct {
	encoder_t* encoder;
	motor_t* motor;
	uint32_t offset_position;
} platform_t;

extern platform_t horizontal, vertical;

void setOffsetPosition();
void setPlatformSpeed(uint32_t step);
void setCurrentPlatform(platform_t* platform);
void setPlatformDirection(uint32_t target_position);
void invertPlatformDirection();
void startPlatformRotation();
void stopPlatform();

bool isPlatformStopped();
bool isPlatformAccelerated();
bool isPlatformRotationForward();
bool isPlatformReachTestPosition();

void acceleratePlatform();
void deceleratePlatform();

#endif
