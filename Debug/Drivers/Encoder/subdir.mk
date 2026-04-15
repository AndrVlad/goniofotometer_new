################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/Encoder/Encoder.c 

OBJS += \
./Drivers/Encoder/Encoder.o 

C_DEPS += \
./Drivers/Encoder/Encoder.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/Encoder/%.o Drivers/Encoder/%.su Drivers/Encoder/%.cyclo: ../Drivers/Encoder/%.c Drivers/Encoder/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F722xx -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-Encoder

clean-Drivers-2f-Encoder:
	-$(RM) ./Drivers/Encoder/Encoder.cyclo ./Drivers/Encoder/Encoder.d ./Drivers/Encoder/Encoder.o ./Drivers/Encoder/Encoder.su

.PHONY: clean-Drivers-2f-Encoder

