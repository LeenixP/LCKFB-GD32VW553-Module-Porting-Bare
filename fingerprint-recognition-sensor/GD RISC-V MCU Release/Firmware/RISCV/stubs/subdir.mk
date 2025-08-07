################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Firmware/RISCV/stubs/_exit.c \
../Firmware/RISCV/stubs/close.c \
../Firmware/RISCV/stubs/fstat.c \
../Firmware/RISCV/stubs/isatty.c \
../Firmware/RISCV/stubs/lseek.c \
../Firmware/RISCV/stubs/read.c \
../Firmware/RISCV/stubs/sbrk.c \
../Firmware/RISCV/stubs/write.c \
../Firmware/RISCV/stubs/write_hex.c 

C_DEPS += \
./Firmware/RISCV/stubs/_exit.d \
./Firmware/RISCV/stubs/close.d \
./Firmware/RISCV/stubs/fstat.d \
./Firmware/RISCV/stubs/isatty.d \
./Firmware/RISCV/stubs/lseek.d \
./Firmware/RISCV/stubs/read.d \
./Firmware/RISCV/stubs/sbrk.d \
./Firmware/RISCV/stubs/write.d \
./Firmware/RISCV/stubs/write_hex.d 

OBJS += \
./Firmware/RISCV/stubs/_exit.o \
./Firmware/RISCV/stubs/close.o \
./Firmware/RISCV/stubs/fstat.o \
./Firmware/RISCV/stubs/isatty.o \
./Firmware/RISCV/stubs/lseek.o \
./Firmware/RISCV/stubs/read.o \
./Firmware/RISCV/stubs/sbrk.o \
./Firmware/RISCV/stubs/write.o \
./Firmware/RISCV/stubs/write_hex.o 


# Each subdirectory must supply rules for building sources it contributes
Firmware/RISCV/stubs/%.o: ../Firmware/RISCV/stubs/%.c Firmware/RISCV/stubs/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GD RISC-V MCU C Compiler'
	riscv-nuclei-elf-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medlow -msmall-data-limit=8 -mdiv -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -std=gnu11 -DGD_ECLIPSE_GCC -DUSE_STDPERIPH_DRIVER -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -Wa,-adhlns=$@.lst   -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-Firmware-2f-RISCV-2f-stubs

clean-Firmware-2f-RISCV-2f-stubs:
	-$(RM) ./Firmware/RISCV/stubs/_exit.d ./Firmware/RISCV/stubs/_exit.o ./Firmware/RISCV/stubs/close.d ./Firmware/RISCV/stubs/close.o ./Firmware/RISCV/stubs/fstat.d ./Firmware/RISCV/stubs/fstat.o ./Firmware/RISCV/stubs/isatty.d ./Firmware/RISCV/stubs/isatty.o ./Firmware/RISCV/stubs/lseek.d ./Firmware/RISCV/stubs/lseek.o ./Firmware/RISCV/stubs/read.d ./Firmware/RISCV/stubs/read.o ./Firmware/RISCV/stubs/sbrk.d ./Firmware/RISCV/stubs/sbrk.o ./Firmware/RISCV/stubs/write.d ./Firmware/RISCV/stubs/write.o ./Firmware/RISCV/stubs/write_hex.d ./Firmware/RISCV/stubs/write_hex.o

.PHONY: clean-Firmware-2f-RISCV-2f-stubs

