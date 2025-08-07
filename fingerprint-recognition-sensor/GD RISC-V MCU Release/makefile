################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include msdk/Firmware/RISCV/stubs/subdir.mk
-include Firmware/RISCV/stubs/subdir.mk
-include Firmware/RISCV/env_Eclipse/subdir.mk
-include Firmware/GD32VW55x_standard_peripheral/Source/subdir.mk
-include Firmware/GD32VW55x_standard_peripheral/subdir.mk
-include BSP_Code/subdir.mk
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := fingerprint-recognition-sensor
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH_BIN += \
fingerprint-recognition-sensor.bin \

SECONDARY_LIST += \
fingerprint-recognition-sensor.lst \

SECONDARY_SIZE += \
fingerprint-recognition-sensor.siz \


# All Target
all: main-build

# Main-build Target
main-build: fingerprint-recognition-sensor.elf secondary-outputs

# Tool invocations
fingerprint-recognition-sensor.elf: $(OBJS) $(USER_OBJS) makefile $(OPTIONAL_TOOL_DEPS)
	@echo 'Building target: $@'
	@echo 'Invoking: GD RISC-V MCU C Linker'
	riscv-nuclei-elf-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medlow -msmall-data-limit=8 -mdiv -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -Wl,-Map,"fingerprint-recognition-sensor.map" -nostartfiles -Xlinker --gc-sections -L"../ldscripts/" --specs=nano.specs --specs=nosys.specs -o "fingerprint-recognition-sensor.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

fingerprint-recognition-sensor.bin: fingerprint-recognition-sensor.elf makefile $(OPTIONAL_TOOL_DEPS)
	@echo 'Invoking: GD RISC-V MCU Flash Image(Bin)'
	riscv-nuclei-elf-objcopy -O binary  "fingerprint-recognition-sensor.elf"  "fingerprint-recognition-sensor.bin"
	@echo 'Finished building: $@'
	@echo ' '

fingerprint-recognition-sensor.lst: fingerprint-recognition-sensor.elf makefile $(OPTIONAL_TOOL_DEPS)
	@echo 'Invoking: GD RISC-V MCU Listing'
	riscv-nuclei-elf-objdump --source --all-headers --demangle --line-numbers --wide "fingerprint-recognition-sensor.elf" > "fingerprint-recognition-sensor.lst"
	@echo 'Finished building: $@'
	@echo ' '

fingerprint-recognition-sensor.siz: fingerprint-recognition-sensor.elf makefile $(OPTIONAL_TOOL_DEPS)
	@echo 'Invoking: GD RISC-V MCU Print Size'
	riscv-nuclei-elf-size --format=berkeley "fingerprint-recognition-sensor.elf"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) fingerprint-recognition-sensor.bin fingerprint-recognition-sensor.elf fingerprint-recognition-sensor.lst fingerprint-recognition-sensor.siz
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH_BIN) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents main-build

-include ../makefile.targets
