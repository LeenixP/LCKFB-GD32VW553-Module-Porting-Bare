################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../BSP_Code/bsp_as608.c 

C_DEPS += \
./BSP_Code/bsp_as608.d 

OBJS += \
./BSP_Code/bsp_as608.o 


# Each subdirectory must supply rules for building sources it contributes
BSP_Code/%.o: ../BSP_Code/%.c BSP_Code/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GD RISC-V MCU C Compiler'
	riscv-nuclei-elf-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medlow -msmall-data-limit=8 -mdiv -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -std=gnu11 -DGD_ECLIPSE_GCC -DUSE_STDPERIPH_DRIVER -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -Wa,-adhlns=$@.lst   -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-BSP_Code

clean-BSP_Code:
	-$(RM) ./BSP_Code/bsp_as608.d ./BSP_Code/bsp_as608.o

.PHONY: clean-BSP_Code

