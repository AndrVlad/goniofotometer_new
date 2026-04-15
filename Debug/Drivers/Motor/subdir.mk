################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/Motor/Motor.c 

OBJS += \
./Drivers/Motor/Motor.o 

C_DEPS += \
./Drivers/Motor/Motor.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/Motor/%.o Drivers/Motor/%.su Drivers/Motor/%.cyclo: ../Drivers/Motor/%.c Drivers/Motor/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F722xx -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-Motor

clean-Drivers-2f-Motor:
	-$(RM) ./Drivers/Motor/Motor.cyclo ./Drivers/Motor/Motor.d ./Drivers/Motor/Motor.o ./Drivers/Motor/Motor.su

.PHONY: clean-Drivers-2f-Motor

