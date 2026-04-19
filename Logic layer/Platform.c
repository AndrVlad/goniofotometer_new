#include "Platform.h"

platform_t horizontal, vertical;
platform_t* current_platform = &horizontal;

void initPlatforms() {
	return;
}

void acceleratePlatform() {
	accelerateMotor(current_platform->motor);
	return;
}

bool isPlatformStopped() {
	if(isMotorStopped(current_platform->motor)) {
		return true;
	} else {
		return false;
	}

}
bool isPlatformAccelerated() {
	if (isMotorAccelerated(current_platform->motor)) {
		return true;
	} else {
		return false;
	}
};

void deceleratePlatform() {
	decelerateMotor(current_platform->motor);
	return;
}

void setCurrentPlatform(platform_t* platform) {
	current_platform = platform;
	return;
};

void setOffsetPosition() {
	horizontal.offset_position = horizontal.encoder->cur_value;
	vertical.offset_position = vertical.encoder->cur_value;
	return;
};
void setPlatformSpeed(uint32_t step) {

	switch(step) {
	case 1820: // разрешение 5 градусов
	case 365:
	case 182:
		setMotorFrequency(current_platform->motor, 407);
		setEncoderPollFrequency(current_platform->encoder,200);
		break;
	case 60: // разрешение 10 минут
		setMotorFrequency(current_platform->motor, 163);
		setEncoderPollFrequency(current_platform->encoder,1000);
		break;
	case 29: // разрешение 5 минут
		setMotorFrequency(current_platform->motor, 115);
		setEncoderPollFrequency(current_platform->encoder,1000);
		break;
	case 6: // разрешение 1 минута
		setMotorFrequency(current_platform->motor, 27);
		setEncoderPollFrequency(current_platform->encoder,1000);
		break;
	}
	return;
};

void setSpecifiedPlatformSpeed(uint32_t frequency_hz) {
	setMotorFrequency(current_platform->motor, frequency_hz);
	return;
};

void setPlatformDirection(uint32_t target_position) {
	return;
};
void startPlatformRotation() {
	startMotorRotation(current_platform->motor);
	return;
}

void stopPlatform() {
	stopMotorRotation(current_platform->motor);
	return;
}

bool isPlatformRotationForward() {
	if(getMotorDirection(current_platform->motor) == FORWARD) {
		return true;
	}

	return false;
}

void invertPlatformDirection() {
	if (getMotorDirection(current_platform->motor) == FORWARD) {
		setMotorDirection(current_platform->motor, BACKWARD);
	} else {
		setMotorDirection(current_platform->motor, FORWARD);
	}
	return;
};
