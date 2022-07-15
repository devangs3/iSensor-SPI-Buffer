################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/adc_tempsensor.c \
../Core/Src/bh1750_i2c.c \
../Core/Src/bme680_i2c.c \
../Core/Src/lis2mdl_i2c.c \
../Core/Src/lis2mdl_spi.c \
../Core/Src/lps277_i2c.c \
../Core/Src/lps277_spi.c \
../Core/Src/lsm6dsox_i2c.c \
../Core/Src/main.c \
../Core/Src/rtc_timestamp.c \
../Core/Src/sensor_framework.c \
../Core/Src/stm32u5xx_hal_msp.c \
../Core/Src/stm32u5xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32u5xx.c 

OBJS += \
./Core/Src/adc_tempsensor.o \
./Core/Src/bh1750_i2c.o \
./Core/Src/bme680_i2c.o \
./Core/Src/lis2mdl_i2c.o \
./Core/Src/lis2mdl_spi.o \
./Core/Src/lps277_i2c.o \
./Core/Src/lps277_spi.o \
./Core/Src/lsm6dsox_i2c.o \
./Core/Src/main.o \
./Core/Src/rtc_timestamp.o \
./Core/Src/sensor_framework.o \
./Core/Src/stm32u5xx_hal_msp.o \
./Core/Src/stm32u5xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32u5xx.o 

C_DEPS += \
./Core/Src/adc_tempsensor.d \
./Core/Src/bh1750_i2c.d \
./Core/Src/bme680_i2c.d \
./Core/Src/lis2mdl_i2c.d \
./Core/Src/lis2mdl_spi.d \
./Core/Src/lps277_i2c.d \
./Core/Src/lps277_spi.d \
./Core/Src/lsm6dsox_i2c.d \
./Core/Src/main.d \
./Core/Src/rtc_timestamp.d \
./Core/Src/sensor_framework.d \
./Core/Src/stm32u5xx_hal_msp.d \
./Core/Src/stm32u5xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32u5xx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32U575xx -c -I../Core/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/adc_tempsensor.d ./Core/Src/adc_tempsensor.o ./Core/Src/adc_tempsensor.su ./Core/Src/bh1750_i2c.d ./Core/Src/bh1750_i2c.o ./Core/Src/bh1750_i2c.su ./Core/Src/bme680_i2c.d ./Core/Src/bme680_i2c.o ./Core/Src/bme680_i2c.su ./Core/Src/lis2mdl_i2c.d ./Core/Src/lis2mdl_i2c.o ./Core/Src/lis2mdl_i2c.su ./Core/Src/lis2mdl_spi.d ./Core/Src/lis2mdl_spi.o ./Core/Src/lis2mdl_spi.su ./Core/Src/lps277_i2c.d ./Core/Src/lps277_i2c.o ./Core/Src/lps277_i2c.su ./Core/Src/lps277_spi.d ./Core/Src/lps277_spi.o ./Core/Src/lps277_spi.su ./Core/Src/lsm6dsox_i2c.d ./Core/Src/lsm6dsox_i2c.o ./Core/Src/lsm6dsox_i2c.su ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/rtc_timestamp.d ./Core/Src/rtc_timestamp.o ./Core/Src/rtc_timestamp.su ./Core/Src/sensor_framework.d ./Core/Src/sensor_framework.o ./Core/Src/sensor_framework.su ./Core/Src/stm32u5xx_hal_msp.d ./Core/Src/stm32u5xx_hal_msp.o ./Core/Src/stm32u5xx_hal_msp.su ./Core/Src/stm32u5xx_it.d ./Core/Src/stm32u5xx_it.o ./Core/Src/stm32u5xx_it.su ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32u5xx.d ./Core/Src/system_stm32u5xx.o ./Core/Src/system_stm32u5xx.su

.PHONY: clean-Core-2f-Src

