INCLUDES = -I. -Idrivers -Istm32l432kc -Im4 -Isetup -Iutil
CFLAGS = -Os -std=c99 -ffreestanding -nostartfiles -mcpu=cortex-m4 -Wall -pedantic

.PHONY: clean

stm32l432kc.elf: setup/*.c src/temp.c usart.o systick.o cbuffer.o led.o
	arm-none-eabi-gcc $(CFLAGS) $(INCLUDES) -T stm32l432kc.ld $^ -o $@

%.o: %.c
	arm-none-eabi-gcc $(CFLAGS) $(INCLUDES) -c $^

clean:
	-rm -f *.elf *.o

