################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Lib/Fonts/font12.c \
../Core/Lib/Fonts/font16.c \
../Core/Lib/Fonts/font20.c \
../Core/Lib/Fonts/font24.c \
../Core/Lib/Fonts/font8.c 

OBJS += \
./Core/Lib/Fonts/font12.o \
./Core/Lib/Fonts/font16.o \
./Core/Lib/Fonts/font20.o \
./Core/Lib/Fonts/font24.o \
./Core/Lib/Fonts/font8.o 

C_DEPS += \
./Core/Lib/Fonts/font12.d \
./Core/Lib/Fonts/font16.d \
./Core/Lib/Fonts/font20.d \
./Core/Lib/Fonts/font24.d \
./Core/Lib/Fonts/font8.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Lib/Fonts/%.o Core/Lib/Fonts/%.su Core/Lib/Fonts/%.cyclo: ../Core/Lib/Fonts/%.c Core/Lib/Fonts/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F107xC -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"/home/agus/STM32CubeIDE/workspace_1.19.0/MKS-TFT32_L-V30-test/Core/Lib" -I"/home/agus/STM32CubeIDE/workspace_1.19.0/MKS-TFT32_L-V30-test/Core/Lib/Fonts" -I"/home/agus/STM32CubeIDE/workspace_1.19.0/MKS-TFT32_L-V30-test/Core/Lib/ili9341" -I"/home/agus/STM32CubeIDE/workspace_1.19.0/MKS-TFT32_L-V30-test/Core/Lib/stm32f1xx" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Lib-2f-Fonts

clean-Core-2f-Lib-2f-Fonts:
	-$(RM) ./Core/Lib/Fonts/font12.cyclo ./Core/Lib/Fonts/font12.d ./Core/Lib/Fonts/font12.o ./Core/Lib/Fonts/font12.su ./Core/Lib/Fonts/font16.cyclo ./Core/Lib/Fonts/font16.d ./Core/Lib/Fonts/font16.o ./Core/Lib/Fonts/font16.su ./Core/Lib/Fonts/font20.cyclo ./Core/Lib/Fonts/font20.d ./Core/Lib/Fonts/font20.o ./Core/Lib/Fonts/font20.su ./Core/Lib/Fonts/font24.cyclo ./Core/Lib/Fonts/font24.d ./Core/Lib/Fonts/font24.o ./Core/Lib/Fonts/font24.su ./Core/Lib/Fonts/font8.cyclo ./Core/Lib/Fonts/font8.d ./Core/Lib/Fonts/font8.o ./Core/Lib/Fonts/font8.su

.PHONY: clean-Core-2f-Lib-2f-Fonts

