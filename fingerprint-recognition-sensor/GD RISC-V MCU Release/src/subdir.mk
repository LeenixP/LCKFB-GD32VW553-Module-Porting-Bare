################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/gd32vw553h_eval.c \
../src/gd32vw55x_it.c \
../src/main.c \
../src/systick.c 

C_DEPS += \
./src/gd32vw553h_eval.d \
./src/gd32vw55x_it.d \
./src/main.d \
./src/systick.d 

OBJS += \
./src/gd32vw553h_eval.o \
./src/gd32vw55x_it.o \
./src/main.o \
./src/systick.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GD RISC-V MCU C Compiler'
	riscv-nuclei-elf-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medlow -msmall-data-limit=8 -mdiv -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -std=gnu11 -DGD_ECLIPSE_GCC -DUSE_STDPERIPH_DRIVER -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -Wa,-adhlns=$@.lst   -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/gd32vw553h_eval.d ./src/gd32vw553h_eval.o ./src/gd32vw55x_it.d ./src/gd32vw55x_it.o ./src/main.d ./src/main.o ./src/systick.d ./src/systick.o

.PHONY: clean-src

