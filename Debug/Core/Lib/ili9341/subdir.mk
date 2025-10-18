################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Lib/ili9341/ili9325.c 

OBJS += \
./Core/Lib/ili9341/ili9325.o 

C_DEPS += \
./Core/Lib/ili9341/ili9325.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Lib/ili9341/%.o Core/Lib/ili9341/%.su Core/Lib/ili9341/%.cyclo: ../Core/Lib/ili9341/%.c Core/Lib/ili9341/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F107xC -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"/home/agus/STM32CubeIDE/workspace_1.19.0/MKS-TFT32_L-V30-test/Core/Lib" -I"/home/agus/STM32CubeIDE/workspace_1.19.0/MKS-TFT32_L-V30-test/Core/Lib/Fonts" -I"/home/agus/STM32CubeIDE/workspace_1.19.0/MKS-TFT32_L-V30-test/Core/Lib/ili9341" -I"/home/agus/STM32CubeIDE/workspace_1.19.0/MKS-TFT32_L-V30-test/Core/Lib/stm32f1xx" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Lib-2f-ili9341

clean-Core-2f-Lib-2f-ili9341:
	-$(RM) ./Core/Lib/ili9341/ili9325.cyclo ./Core/Lib/ili9341/ili9325.d ./Core/Lib/ili9341/ili9325.o ./Core/Lib/ili9341/ili9325.su

.PHONY: clean-Core-2f-Lib-2f-ili9341

