################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../component/uart/lpuart_adapter.c 

C_DEPS += \
./component/uart/lpuart_adapter.d 

OBJS += \
./component/uart/lpuart_adapter.o 


# Each subdirectory must supply rules for building sources it contributes
component/uart/%.o: ../component/uart/%.c component/uart/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_MKE18F512VLL16 -DSERIAL_PORT_TYPE_UART=1 -DCPU_MKE18F512VLL16_cm4 -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\tpala\Documents\MCUXpressoIDE_24.9.25\workspace\hvpke18f_led_blinky\source" -I"C:\Users\tpala\Documents\MCUXpressoIDE_24.9.25\workspace\hvpke18f_led_blinky" -I"C:\Users\tpala\Documents\MCUXpressoIDE_24.9.25\workspace\hvpke18f_led_blinky\drivers" -I"C:\Users\tpala\Documents\MCUXpressoIDE_24.9.25\workspace\hvpke18f_led_blinky\device" -I"C:\Users\tpala\Documents\MCUXpressoIDE_24.9.25\workspace\hvpke18f_led_blinky\utilities" -I"C:\Users\tpala\Documents\MCUXpressoIDE_24.9.25\workspace\hvpke18f_led_blinky\component\uart" -I"C:\Users\tpala\Documents\MCUXpressoIDE_24.9.25\workspace\hvpke18f_led_blinky\component\serial_manager" -I"C:\Users\tpala\Documents\MCUXpressoIDE_24.9.25\workspace\hvpke18f_led_blinky\component\lists" -I"C:\Users\tpala\Documents\MCUXpressoIDE_24.9.25\workspace\hvpke18f_led_blinky\CMSIS" -I"C:\Users\tpala\Documents\MCUXpressoIDE_24.9.25\workspace\hvpke18f_led_blinky\board" -O0 -fno-common -g3 -gdwarf-4 -Wall -c  -ffunction-sections  -fdata-sections  -ffreestanding  -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-component-2f-uart

clean-component-2f-uart:
	-$(RM) ./component/uart/lpuart_adapter.d ./component/uart/lpuart_adapter.o

.PHONY: clean-component-2f-uart

