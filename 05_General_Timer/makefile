TOOLCHAIN = arm-none-eabi
PROCESSOR = cortex-m0
AFLAGS    = -mcpu=cortex-m0 -mthumb -mfloat-abi=soft
CFLAGS    = -mcpu=cortex-m0 -mthumb -mfloat-abi=soft -ggdb -Wall -O0 -std=c99 -ffunction-sections -fdata-sections # -MMD -MP
LDFLAGS   = -Wl,--gc-sections --specs=rdimon.specs --specs=nano.specs -Wl,--no-warn-rwx-segment -Wl,-Map=final.map

INCLUDES  = -I CMSIS/Device -I CMSIS/Include -I HAL/Inc
SYMBOLS   = -DUSE_HAL_DRIVER -DSTM32F070xB

all:final

final:final.elf
	$(TOOLCHAIN)-objdump -S $< > final.list
	$(TOOLCHAIN)-size --format=berkeley $<

final.elf:startup_stm32f070xb.o system_stm32f0xx.o main.o stm32f0xx_hal.o hal_msp.o stm32f0xx_hal_cortex.o stm32f0xx_hal_rcc.o stm32f0xx_hal_gpio.o interrupts.o stm32f0xx_hal_tim.o
	$(TOOLCHAIN)-gcc $(AFLAGS) $(LDFLAGS) -T linker.ld -o $@ $^

stm32f0xx_hal_tim.o:HAL/Src/stm32f0xx_hal_tim.c
	$(TOOLCHAIN)-gcc $(CFLAGS) $(INCLUDES) $(SYMBOLS) -o $@ -c $<

interrupts.o:interrupts.c
	$(TOOLCHAIN)-gcc $(CFLAGS) $(INCLUDES) $(SYMBOLS) -o $@ -c $<

stm32f0xx_hal_gpio.o:HAL/Src/stm32f0xx_hal_gpio.c
	$(TOOLCHAIN)-gcc $(CFLAGS) $(INCLUDES) $(SYMBOLS) -o $@ -c $<

stm32f0xx_hal_rcc.o:HAL/Src/stm32f0xx_hal_rcc.c
	$(TOOLCHAIN)-gcc $(CFLAGS) $(INCLUDES) $(SYMBOLS) -o $@ -c $<

stm32f0xx_hal_cortex.o:HAL/Src/stm32f0xx_hal_cortex.c
	$(TOOLCHAIN)-gcc $(CFLAGS) $(INCLUDES) $(SYMBOLS) -o $@ -c $<

hal_msp.o:hal_msp.c
	$(TOOLCHAIN)-gcc $(CFLAGS) $(INCLUDES) $(SYMBOLS) -o $@ -c $<

stm32f0xx_hal.o:HAL/Src/stm32f0xx_hal.c
	$(TOOLCHAIN)-gcc $(CFLAGS) $(INCLUDES) $(SYMBOLS) -o $@ -c $<

main.o:main.c
	$(TOOLCHAIN)-gcc $(CFLAGS) $(INCLUDES) $(SYMBOLS) -o $@ -c $<

system_stm32f0xx.o:CMSIS/system_stm32f0xx.c
	$(TOOLCHAIN)-gcc $(CFLAGS) $(INCLUDES) $(SYMBOLS) -o $@ -c $<

startup_stm32f070xb.o:CMSIS/Startup/startup_stm32f070xb.s
	$(TOOLCHAIN)-as $(AFLAGS) -o $@ -c $<

load:
	openocd -f board/st_nucleo_f0.cfg

clean:
	rm -rf *.o *.map *.list *.elf