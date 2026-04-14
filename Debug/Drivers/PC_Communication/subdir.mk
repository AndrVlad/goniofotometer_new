################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/PC_Communication/PC_Communication.c 

OBJS += \
./Drivers/PC_Communication/PC_Communication.o 

C_DEPS += \
./Drivers/PC_Communication/PC_Communication.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/PC_Communication/%.o Drivers/PC_Communication/%.su Drivers/PC_Communication/%.cyclo: ../Drivers/PC_Communication/%.c Drivers/PC_Communication/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F722xx -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-PC_Communication

clean-Drivers-2f-PC_Communication:
	-$(RM) ./Drivers/PC_Communication/PC_Communication.cyclo ./Drivers/PC_Communication/PC_Communication.d ./Drivers/PC_Communication/PC_Communication.o ./Drivers/PC_Communication/PC_Communication.su

.PHONY: clean-Drivers-2f-PC_Communication

