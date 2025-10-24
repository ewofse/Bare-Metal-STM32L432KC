INCLUDES = -Idrivers -ISTM32L432KC -IM4 -Isetup
CFLAGS = -Os -std=c99 -ffreestanding -nostartfiles -mcpu=cortex-m33 -Wall

.PHONY: clean

stm32l432kc.elf: setup/*.c src/test_systick_irq.c led.o systick.o
	arm-none-eabi-gcc $(CFLAGS) $(INCLUDES) -T stm32l432kc.ld $^ -o $@

%.o: %.c
	arm-none-eabi-gcc $(CFLAGS) $(INCLUDES) -c $^

clean:
	-rm *.elf *.o

