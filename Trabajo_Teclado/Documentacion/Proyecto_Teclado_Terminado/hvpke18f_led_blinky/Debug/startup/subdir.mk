################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../startup/startup_mke18f16.c 

C_DEPS += \
./startup/startup_mke18f16.d 

OBJS += \
./startup/startup_mke18f16.o 


# Each subdirectory must supply rules for building sources it contributes
startup/%.o: ../startup/%.c startup/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_MKE18F512VLL16 -DSERIAL_PORT_TYPE_UART=1 -DCPU_MKE18F512VLL16_cm4 -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\tpala\Documents\MCUXpressoIDE_24.9.25\workspace\hvpke18f_led_blinky\source" -I"C:\Users\tpala\Documents\MCUXpressoIDE_24.9.25\workspace\hvpke18f_led_blinky" -I"C:\Users\tpala\Documents\MCUXpressoIDE_24.9.25\workspace\hvpke18f_led_blinky\drivers" -I"C:\Users\tpala\Documents\MCUXpressoIDE_24.9.25\workspace\hvpke18f_led_blinky\device" -I"C:\Users\tpala\Documents\MCUXpressoIDE_24.9.25\workspace\hvpke18f_led_blinky\utilities" -I"C:\Users\tpala\Documents\MCUXpressoIDE_24.9.25\workspace\hvpke18f_led_blinky\component\uart" -I"C:\Users\tpala\Documents\MCUXpressoIDE_24.9.25\workspace\hvpke18f_led_blinky\component\serial_manager" -I"C:\Users\tpala\Documents\MCUXpressoIDE_24.9.25\workspace\hvpke18f_led_blinky\component\lists" -I"C:\Users\tpala\Documents\MCUXpressoIDE_24.9.25\workspace\hvpke18f_led_blinky\CMSIS" -I"C:\Users\tpala\Documents\MCUXpressoIDE_24.9.25\workspace\hvpke18f_led_blinky\board" -O0 -fno-common -g3 -gdwarf-4 -Wall -c  -ffunction-sections  -fdata-sections  -ffreestanding  -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-startup

clean-startup:
	-$(RM) ./startup/startup_mke18f16.d ./startup/startup_mke18f16.o

.PHONY: clean-startup

