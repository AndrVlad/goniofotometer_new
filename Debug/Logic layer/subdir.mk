################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Logic\ layer/MeasurementController.c \
../Logic\ layer/PC_Protocol.c \
../Logic\ layer/PhotodetectorController.c \
../Logic\ layer/Platform.c 

OBJS += \
./Logic\ layer/MeasurementController.o \
./Logic\ layer/PC_Protocol.o \
./Logic\ layer/PhotodetectorController.o \
./Logic\ layer/Platform.o 

C_DEPS += \
./Logic\ layer/MeasurementController.d \
./Logic\ layer/PC_Protocol.d \
./Logic\ layer/PhotodetectorController.d \
./Logic\ layer/Platform.d 


# Each subdirectory must supply rules for building sources it contributes
Logic\ layer/MeasurementController.o: ../Logic\ layer/MeasurementController.c Logic\ layer/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F722xx -c -I../Core/Inc -I"C:/Users/Admin/STM32CubeIDE/workspace_1.12.0/goniofotometer_new/Drivers/Photodetector" -I"C:/Users/Admin/STM32CubeIDE/workspace_1.12.0/goniofotometer_new/Drivers/Timer" -I"C:/Users/Admin/STM32CubeIDE/workspace_1.12.0/goniofotometer_new/Drivers/PC_Communication" -I"C:/Users/Admin/STM32CubeIDE/workspace_1.12.0/goniofotometer_new/Drivers/Motor" -I"C:/Users/Admin/STM32CubeIDE/workspace_1.12.0/goniofotometer_new/Drivers/Encoder" -I"C:/Users/Admin/STM32CubeIDE/workspace_1.12.0/goniofotometer_new/Logic layer" -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"Logic layer/MeasurementController.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Logic\ layer/PC_Protocol.o: ../Logic\ layer/PC_Protocol.c Logic\ layer/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F722xx -c -I../Core/Inc -I"C:/Users/Admin/STM32CubeIDE/workspace_1.12.0/goniofotometer_new/Drivers/Photodetector" -I"C:/Users/Admin/STM32CubeIDE/workspace_1.12.0/goniofotometer_new/Drivers/Timer" -I"C:/Users/Admin/STM32CubeIDE/workspace_1.12.0/goniofotometer_new/Drivers/PC_Communication" -I"C:/Users/Admin/STM32CubeIDE/workspace_1.12.0/goniofotometer_new/Drivers/Motor" -I"C:/Users/Admin/STM32CubeIDE/workspace_1.12.0/goniofotometer_new/Drivers/Encoder" -I"C:/Users/Admin/STM32CubeIDE/workspace_1.12.0/goniofotometer_new/Logic layer" -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"Logic layer/PC_Protocol.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Logic\ layer/PhotodetectorController.o: ../Logic\ layer/PhotodetectorController.c Logic\ layer/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F722xx -c -I../Core/Inc -I"C:/Users/Admin/STM32CubeIDE/workspace_1.12.0/goniofotometer_new/Drivers/Photodetector" -I"C:/Users/Admin/STM32CubeIDE/workspace_1.12.0/goniofotometer_new/Drivers/Timer" -I"C:/Users/Admin/STM32CubeIDE/workspace_1.12.0/goniofotometer_new/Drivers/PC_Communication" -I"C:/Users/Admin/STM32CubeIDE/workspace_1.12.0/goniofotometer_new/Drivers/Motor" -I"C:/Users/Admin/STM32CubeIDE/workspace_1.12.0/goniofotometer_new/Drivers/Encoder" -I"C:/Users/Admin/STM32CubeIDE/workspace_1.12.0/goniofotometer_new/Logic layer" -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"Logic layer/PhotodetectorController.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Logic\ layer/Platform.o: ../Logic\ layer/Platform.c Logic\ layer/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F722xx -c -I../Core/Inc -I"C:/Users/Admin/STM32CubeIDE/workspace_1.12.0/goniofotometer_new/Drivers/Photodetector" -I"C:/Users/Admin/STM32CubeIDE/workspace_1.12.0/goniofotometer_new/Drivers/Timer" -I"C:/Users/Admin/STM32CubeIDE/workspace_1.12.0/goniofotometer_new/Drivers/PC_Communication" -I"C:/Users/Admin/STM32CubeIDE/workspace_1.12.0/goniofotometer_new/Drivers/Motor" -I"C:/Users/Admin/STM32CubeIDE/workspace_1.12.0/goniofotometer_new/Drivers/Encoder" -I"C:/Users/Admin/STM32CubeIDE/workspace_1.12.0/goniofotometer_new/Logic layer" -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"Logic layer/Platform.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Logic-20-layer

clean-Logic-20-layer:
	-$(RM) ./Logic\ layer/MeasurementController.cyclo ./Logic\ layer/MeasurementController.d ./Logic\ layer/MeasurementController.o ./Logic\ layer/MeasurementController.su ./Logic\ layer/PC_Protocol.cyclo ./Logic\ layer/PC_Protocol.d ./Logic\ layer/PC_Protocol.o ./Logic\ layer/PC_Protocol.su ./Logic\ layer/PhotodetectorController.cyclo ./Logic\ layer/PhotodetectorController.d ./Logic\ layer/PhotodetectorController.o ./Logic\ layer/PhotodetectorController.su ./Logic\ layer/Platform.cyclo ./Logic\ layer/Platform.d ./Logic\ layer/Platform.o ./Logic\ layer/Platform.su

.PHONY: clean-Logic-20-layer

