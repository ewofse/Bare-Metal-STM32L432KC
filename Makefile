INCLUDES = -I. -Idrivers -Istm32l432kc -Im4 -Isetup -Iutil
CFLAGS = -Os -std=c99 -ffreestanding -nostartfiles -mcpu=cortex-m33 -Wall -pedantic

.PHONY: clean

stm32l432kc.elf: setup/*.c src/test_usart.c led.o systick.o usart.o cbuffer.o
	arm-none-eabi-gcc $(CFLAGS) $(INCLUDES) -T stm32l432kc.ld $^ -o $@

%.o: %.c
	arm-none-eabi-gcc $(CFLAGS) $(INCLUDES) -c $^

clean:
	-rm -f *.elf *.o

