################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/Photodetector/Photodetector.c 

OBJS += \
./Drivers/Photodetector/Photodetector.o 

C_DEPS += \
./Drivers/Photodetector/Photodetector.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/Photodetector/%.o Drivers/Photodetector/%.su Drivers/Photodetector/%.cyclo: ../Drivers/Photodetector/%.c Drivers/Photodetector/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F722xx -c -I../Core/Inc -I"C:/Users/Admin/STM32CubeIDE/workspace_1.12.0/goniofotometer_new/Drivers/Timer" -I"C:/Users/Admin/STM32CubeIDE/workspace_1.12.0/goniofotometer_new/Drivers/Encoder" -I"C:/Users/Admin/STM32CubeIDE/workspace_1.12.0/goniofotometer_new/Logic layer" -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-Photodetector

clean-Drivers-2f-Photodetector:
	-$(RM) ./Drivers/Photodetector/Photodetector.cyclo ./Drivers/Photodetector/Photodetector.d ./Drivers/Photodetector/Photodetector.o ./Drivers/Photodetector/Photodetector.su

.PHONY: clean-Drivers-2f-Photodetector

