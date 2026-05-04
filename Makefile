CPU 	 = -mcpu=cortex-m4 -mthumb
INCLUDES = -I. -Idrivers -Istm32l432kc -Im4 -Isetup -Iutil -Ilib/printf

OPTS 	 = -Os
LTOPTS 	 = -fdata-sections -ffunction-sections

LINKOPTS = -nostartfiles -Wl,--gc-sections
LDFLAGS  = -T stm32l432kc.ld
LIBS 	 = 

CFLAGS   = -std=c99 -ffreestanding -pedantic \
		   $(CPU) $(OPTS) $(INCLUDES) $(LTOPTS) -Wall 

.PHONY: clean flash

stm32l432kc.elf: setup/*.c lib/printf/printf.c src/test_printf.c \
                 drivers/systick.o drivers/usart.o util/cbuffer.o
	arm-none-eabi-gcc $(CFLAGS) $(LINKOPTS) $(LDFLAGS) $(LIBS) -o $@ $^

%.o: %.c
	arm-none-eabi-gcc $(CFLAGS) -c $< -o $@

flash: stm32l432kc.elf
	cp $< /Volumes/NODE_L432KC; diskutil eject /Volumes/NODE_L432KC

clean:
	-rm -f *.elf *.bin *.o

