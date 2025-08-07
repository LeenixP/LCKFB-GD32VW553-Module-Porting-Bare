################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Firmware/RISCV/env_Eclipse/handlers.c \
../Firmware/RISCV/env_Eclipse/init.c \
../Firmware/RISCV/env_Eclipse/your_printf.c 

S_UPPER_SRCS += \
../Firmware/RISCV/env_Eclipse/entry.S \
../Firmware/RISCV/env_Eclipse/start.S 

C_DEPS += \
./Firmware/RISCV/env_Eclipse/handlers.d \
./Firmware/RISCV/env_Eclipse/init.d \
./Firmware/RISCV/env_Eclipse/your_printf.d 

OBJS += \
./Firmware/RISCV/env_Eclipse/entry.o \
./Firmware/RISCV/env_Eclipse/handlers.o \
./Firmware/RISCV/env_Eclipse/init.o \
./Firmware/RISCV/env_Eclipse/start.o \
./Firmware/RISCV/env_Eclipse/your_printf.o 


# Each subdirectory must supply rules for building sources it contributes
Firmware/RISCV/env_Eclipse/%.o: ../Firmware/RISCV/env_Eclipse/%.S Firmware/RISCV/env_Eclipse/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GD RISC-V MCU Assembler'
	riscv-nuclei-elf-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medlow -msmall-data-limit=8 -mdiv -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -Wa,-adhlns=$@.lst   -x assembler-with-cpp -I"../Firmware/RISCV/drivers" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Firmware/RISCV/env_Eclipse/%.o: ../Firmware/RISCV/env_Eclipse/%.c Firmware/RISCV/env_Eclipse/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GD RISC-V MCU C Compiler'
	riscv-nuclei-elf-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medlow -msmall-data-limit=8 -mdiv -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -std=gnu11 -DGD_ECLIPSE_GCC -DUSE_STDPERIPH_DRIVER -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -Wa,-adhlns=$@.lst   -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-Firmware-2f-RISCV-2f-env_Eclipse

clean-Firmware-2f-RISCV-2f-env_Eclipse:
	-$(RM) ./Firmware/RISCV/env_Eclipse/entry.o ./Firmware/RISCV/env_Eclipse/handlers.d ./Firmware/RISCV/env_Eclipse/handlers.o ./Firmware/RISCV/env_Eclipse/init.d ./Firmware/RISCV/env_Eclipse/init.o ./Firmware/RISCV/env_Eclipse/start.o ./Firmware/RISCV/env_Eclipse/your_printf.d ./Firmware/RISCV/env_Eclipse/your_printf.o

.PHONY: clean-Firmware-2f-RISCV-2f-env_Eclipse

