################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/S27KS0642.c \
../Core/Src/extmem_manager.c \
../Core/Src/gpio.c \
../Core/Src/main.c \
../Core/Src/memorymap.c \
../Core/Src/sbs.c \
../Core/Src/stm32h7rsxx_hal_msp.c \
../Core/Src/stm32h7rsxx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32h7rsxx.c \
../Core/Src/user_driver.c \
../Core/Src/xspi.c 

C_DEPS += \
./Core/Src/S27KS0642.d \
./Core/Src/extmem_manager.d \
./Core/Src/gpio.d \
./Core/Src/main.d \
./Core/Src/memorymap.d \
./Core/Src/sbs.d \
./Core/Src/stm32h7rsxx_hal_msp.d \
./Core/Src/stm32h7rsxx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32h7rsxx.d \
./Core/Src/user_driver.d \
./Core/Src/xspi.d 

OBJS += \
./Core/Src/S27KS0642.o \
./Core/Src/extmem_manager.o \
./Core/Src/gpio.o \
./Core/Src/main.o \
./Core/Src/memorymap.o \
./Core/Src/sbs.o \
./Core/Src/stm32h7rsxx_hal_msp.o \
./Core/Src/stm32h7rsxx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32h7rsxx.o \
./Core/Src/user_driver.o \
./Core/Src/xspi.o 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H7R7xx -c -I../Core/Inc -I../../Drivers/STM32H7RSxx_HAL_Driver/Inc -I../../Drivers/STM32H7RSxx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32H7RSxx/Include -I../../Drivers/CMSIS/Include -I../../Middlewares/ST/STM32_ExtMem_Manager -I../../Middlewares/ST/STM32_ExtMem_Manager/boot -I../../Middlewares/ST/STM32_ExtMem_Manager/sal -I../../Middlewares/ST/STM32_ExtMem_Manager/nor_sfdp -I../../Middlewares/ST/STM32_ExtMem_Manager/psram -I../../Middlewares/ST/STM32_ExtMem_Manager/sdcard -I../../Middlewares/ST/STM32_ExtMem_Manager/user -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/S27KS0642.cyclo ./Core/Src/S27KS0642.d ./Core/Src/S27KS0642.o ./Core/Src/S27KS0642.su ./Core/Src/extmem_manager.cyclo ./Core/Src/extmem_manager.d ./Core/Src/extmem_manager.o ./Core/Src/extmem_manager.su ./Core/Src/gpio.cyclo ./Core/Src/gpio.d ./Core/Src/gpio.o ./Core/Src/gpio.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/memorymap.cyclo ./Core/Src/memorymap.d ./Core/Src/memorymap.o ./Core/Src/memorymap.su ./Core/Src/sbs.cyclo ./Core/Src/sbs.d ./Core/Src/sbs.o ./Core/Src/sbs.su ./Core/Src/stm32h7rsxx_hal_msp.cyclo ./Core/Src/stm32h7rsxx_hal_msp.d ./Core/Src/stm32h7rsxx_hal_msp.o ./Core/Src/stm32h7rsxx_hal_msp.su ./Core/Src/stm32h7rsxx_it.cyclo ./Core/Src/stm32h7rsxx_it.d ./Core/Src/stm32h7rsxx_it.o ./Core/Src/stm32h7rsxx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32h7rsxx.cyclo ./Core/Src/system_stm32h7rsxx.d ./Core/Src/system_stm32h7rsxx.o ./Core/Src/system_stm32h7rsxx.su ./Core/Src/user_driver.cyclo ./Core/Src/user_driver.d ./Core/Src/user_driver.o ./Core/Src/user_driver.su ./Core/Src/xspi.cyclo ./Core/Src/xspi.d ./Core/Src/xspi.o ./Core/Src/xspi.su

.PHONY: clean-Core-2f-Src

