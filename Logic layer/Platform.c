#include "Platform.h"

platform_t horizontal, vertical;
platform_t* current_platform = &horizontal;

void initPlatforms() {
	horizontal.motor = &h_motor;
	horizontal.encoder = &h_encoder;
	vertical.motor = &v_motor;
	vertical.encoder = &v_encoder;
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
		setEncoderPollFrequency(200);
		break;
	case 60: // разрешение 10 минут
		setMotorFrequency(current_platform->motor, 163);
		setEncoderPollFrequency(1000);
		break;
	case 29: // разрешение 5 минут
		setMotorFrequency(current_platform->motor, 115);
		setEncoderPollFrequency(1000);
		break;
	case 6: // разрешение 1 минута
		setMotorFrequency(current_platform->motor, 27);
		setEncoderPollFrequency(1000);
		break;
	}
	return;
};

void setSpecifiedPlatformSpeed(uint32_t frequency_hz) {
	setMotorFrequency(current_platform->motor, frequency_hz);
	return;
};

void setPlatformDirection(uint32_t target_position) {

	uint32_t current_enc_val = current_platform->encoder->cur_value;

	if (target_position < current_enc_val) {
		if ((current_enc_val - target_position) > (ENCODER_RESOLUTION - current_enc_val + target_position)) {
			setMotorDirection(current_platform->motor, FORWARD);
		} else {
			setMotorDirection(current_platform->motor, BACKWARD);
		}
	} else {
		if ((ENCODER_RESOLUTION - target_position + current_enc_val) < (target_position - current_enc_val)) {
			setMotorDirection(current_platform->motor, BACKWARD);
		} else {
			setMotorDirection(current_platform->motor, FORWARD);
		}
	}

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

void stopPlatforms() {
	stopMotorRotation(horizontal.motor);
	stopMotorRotation(vertical.motor);
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

uint32_t getOffsetPosition(uint8_t platform_num) {
	return current_platform->offset_position;
};

uint32_t getInvertedEncoderVal(uint8_t encoder_num) {
	if (encoder_num) {
		return getInvVal(encoder_num);
	} else {
		return getInvVal(encoder_num);
	}
}

void updateEncoderVal(uint8_t encoder_num) {
	pollEncoder(encoder_num);
	return;
}
