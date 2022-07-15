################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/adc_tempsensor.c \
../Core/Src/adxl375_i2c.c \
../Core/Src/adxl375_spi.c \
../Core/Src/aht20_i2c.c \
../Core/Src/apds9960_i2c.c \
../Core/Src/bh1750_i2c.c \
../Core/Src/bme680_i2c.c \
../Core/Src/comm_abstraction.c \
../Core/Src/commented_code.c \
../Core/Src/lis2mdl_i2c.c \
../Core/Src/lis3mdl_i2c.c \
../Core/Src/lps277_i2c.c \
../Core/Src/lps277_spi.c \
../Core/Src/lsm6dso32_spi.c \
../Core/Src/lsm6dsox_i2c.c \
../Core/Src/lsmdso32_i2c.c \
../Core/Src/main.c \
../Core/Src/rtc_timestamp.c \
../Core/Src/sensor_framework.c \
../Core/Src/set_drdy.c \
../Core/Src/stm32u5xx_hal_msp.c \
../Core/Src/stm32u5xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32u5xx.c \
../Core/Src/test_file.c \
../Core/Src/timers.c \
../Core/Src/tsl2591_i2c.c \
../Core/Src/vcnl4040_i2c.c 

OBJS += \
./Core/Src/adc_tempsensor.o \
./Core/Src/adxl375_i2c.o \
./Core/Src/adxl375_spi.o \
./Core/Src/aht20_i2c.o \
./Core/Src/apds9960_i2c.o \
./Core/Src/bh1750_i2c.o \
./Core/Src/bme680_i2c.o \
./Core/Src/comm_abstraction.o \
./Core/Src/commented_code.o \
./Core/Src/lis2mdl_i2c.o \
./Core/Src/lis3mdl_i2c.o \
./Core/Src/lps277_i2c.o \
./Core/Src/lps277_spi.o \
./Core/Src/lsm6dso32_spi.o \
./Core/Src/lsm6dsox_i2c.o \
./Core/Src/lsmdso32_i2c.o \
./Core/Src/main.o \
./Core/Src/rtc_timestamp.o \
./Core/Src/sensor_framework.o \
./Core/Src/set_drdy.o \
./Core/Src/stm32u5xx_hal_msp.o \
./Core/Src/stm32u5xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32u5xx.o \
./Core/Src/test_file.o \
./Core/Src/timers.o \
./Core/Src/tsl2591_i2c.o \
./Core/Src/vcnl4040_i2c.o 

C_DEPS += \
./Core/Src/adc_tempsensor.d \
./Core/Src/adxl375_i2c.d \
./Core/Src/adxl375_spi.d \
./Core/Src/aht20_i2c.d \
./Core/Src/apds9960_i2c.d \
./Core/Src/bh1750_i2c.d \
./Core/Src/bme680_i2c.d \
./Core/Src/comm_abstraction.d \
./Core/Src/commented_code.d \
./Core/Src/lis2mdl_i2c.d \
./Core/Src/lis3mdl_i2c.d \
./Core/Src/lps277_i2c.d \
./Core/Src/lps277_spi.d \
./Core/Src/lsm6dso32_spi.d \
./Core/Src/lsm6dsox_i2c.d \
./Core/Src/lsmdso32_i2c.d \
./Core/Src/main.d \
./Core/Src/rtc_timestamp.d \
./Core/Src/sensor_framework.d \
./Core/Src/set_drdy.d \
./Core/Src/stm32u5xx_hal_msp.d \
./Core/Src/stm32u5xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32u5xx.d \
./Core/Src/test_file.d \
./Core/Src/timers.d \
./Core/Src/tsl2591_i2c.d \
./Core/Src/vcnl4040_i2c.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U575xx -c -I../Core/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/adc_tempsensor.d ./Core/Src/adc_tempsensor.o ./Core/Src/adc_tempsensor.su ./Core/Src/adxl375_i2c.d ./Core/Src/adxl375_i2c.o ./Core/Src/adxl375_i2c.su ./Core/Src/adxl375_spi.d ./Core/Src/adxl375_spi.o ./Core/Src/adxl375_spi.su ./Core/Src/aht20_i2c.d ./Core/Src/aht20_i2c.o ./Core/Src/aht20_i2c.su ./Core/Src/apds9960_i2c.d ./Core/Src/apds9960_i2c.o ./Core/Src/apds9960_i2c.su ./Core/Src/bh1750_i2c.d ./Core/Src/bh1750_i2c.o ./Core/Src/bh1750_i2c.su ./Core/Src/bme680_i2c.d ./Core/Src/bme680_i2c.o ./Core/Src/bme680_i2c.su ./Core/Src/comm_abstraction.d ./Core/Src/comm_abstraction.o ./Core/Src/comm_abstraction.su ./Core/Src/commented_code.d ./Core/Src/commented_code.o ./Core/Src/commented_code.su ./Core/Src/lis2mdl_i2c.d ./Core/Src/lis2mdl_i2c.o ./Core/Src/lis2mdl_i2c.su ./Core/Src/lis3mdl_i2c.d ./Core/Src/lis3mdl_i2c.o ./Core/Src/lis3mdl_i2c.su ./Core/Src/lps277_i2c.d ./Core/Src/lps277_i2c.o ./Core/Src/lps277_i2c.su ./Core/Src/lps277_spi.d ./Core/Src/lps277_spi.o ./Core/Src/lps277_spi.su ./Core/Src/lsm6dso32_spi.d ./Core/Src/lsm6dso32_spi.o ./Core/Src/lsm6dso32_spi.su ./Core/Src/lsm6dsox_i2c.d ./Core/Src/lsm6dsox_i2c.o ./Core/Src/lsm6dsox_i2c.su ./Core/Src/lsmdso32_i2c.d ./Core/Src/lsmdso32_i2c.o ./Core/Src/lsmdso32_i2c.su ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/rtc_timestamp.d ./Core/Src/rtc_timestamp.o ./Core/Src/rtc_timestamp.su ./Core/Src/sensor_framework.d ./Core/Src/sensor_framework.o ./Core/Src/sensor_framework.su ./Core/Src/set_drdy.d ./Core/Src/set_drdy.o ./Core/Src/set_drdy.su ./Core/Src/stm32u5xx_hal_msp.d ./Core/Src/stm32u5xx_hal_msp.o ./Core/Src/stm32u5xx_hal_msp.su ./Core/Src/stm32u5xx_it.d ./Core/Src/stm32u5xx_it.o ./Core/Src/stm32u5xx_it.su ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32u5xx.d ./Core/Src/system_stm32u5xx.o ./Core/Src/system_stm32u5xx.su ./Core/Src/test_file.d ./Core/Src/test_file.o ./Core/Src/test_file.su ./Core/Src/timers.d ./Core/Src/timers.o ./Core/Src/timers.su ./Core/Src/tsl2591_i2c.d ./Core/Src/tsl2591_i2c.o ./Core/Src/tsl2591_i2c.su ./Core/Src/vcnl4040_i2c.d ./Core/Src/vcnl4040_i2c.o ./Core/Src/vcnl4040_i2c.su

.PHONY: clean-Core-2f-Src

