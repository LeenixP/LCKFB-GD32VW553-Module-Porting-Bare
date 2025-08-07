################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Firmware/GD32VW55x_standard_peripheral/system_gd32vw55x.c 

C_DEPS += \
./Firmware/GD32VW55x_standard_peripheral/system_gd32vw55x.d 

OBJS += \
./Firmware/GD32VW55x_standard_peripheral/system_gd32vw55x.o 


# Each subdirectory must supply rules for building sources it contributes
Firmware/GD32VW55x_standard_peripheral/%.o: ../Firmware/GD32VW55x_standard_peripheral/%.c Firmware/GD32VW55x_standard_peripheral/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GD RISC-V MCU C Compiler'
	riscv-nuclei-elf-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medlow -msmall-data-limit=8 -mdiv -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -std=gnu11 -DGD_ECLIPSE_GCC -DUSE_STDPERIPH_DRIVER -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -Wa,-adhlns=$@.lst   -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-Firmware-2f-GD32VW55x_standard_peripheral

clean-Firmware-2f-GD32VW55x_standard_peripheral:
	-$(RM) ./Firmware/GD32VW55x_standard_peripheral/system_gd32vw55x.d ./Firmware/GD32VW55x_standard_peripheral/system_gd32vw55x.o

.PHONY: clean-Firmware-2f-GD32VW55x_standard_peripheral

