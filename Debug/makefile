################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32F7xx_HAL_Driver/Src/subdir.mk
-include Drivers/Photodetector/subdir.mk
-include Drivers/PC_Communication/subdir.mk
-include Drivers/Motor/subdir.mk
-include Drivers/Encoder/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := goniofotometer_new
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
goniofotometer_new.elf \

MAP_FILES += \
goniofotometer_new.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
goniofotometer_new.list \


# All Target
all: main-build

# Main-build Target
main-build: goniofotometer_new.elf secondary-outputs

# Tool invocations
goniofotometer_new.elf goniofotometer_new.map: $(OBJS) $(USER_OBJS) C:\Users\Admin\STM32CubeIDE\workspace_1.12.0\goniofotometer_new\STM32F722VCTX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "goniofotometer_new.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m7 -T"C:\Users\Admin\STM32CubeIDE\workspace_1.12.0\goniofotometer_new\STM32F722VCTX_FLASH.ld" --specs=nosys.specs -Wl,-Map="goniofotometer_new.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

goniofotometer_new.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "goniofotometer_new.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) default.size.stdout goniofotometer_new.elf goniofotometer_new.list goniofotometer_new.map
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
