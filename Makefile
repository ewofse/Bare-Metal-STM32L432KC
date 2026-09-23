CPU 	 = -mcpu=cortex-m4 -mthumb
INCLUDES = -I. -Idrivers -Istm32l432kc -Im4 -Isetup -Iutil -Ilib/printf

OPTS 	 = -Os
LTOPTS 	 = -fdata-sections -ffunction-sections

LINKOPTS = -nostartfiles -Wl,--gc-sections
LDFLAGS  = -T stm32l432kc.ld
LIBS 	 = 

CFLAGS   = -std=c99 -ffreestanding -pedantic \
		   $(CPU) $(OPTS) $(INCLUDES) $(LTOPTS) -Wall 

.PHONY: clean flash eject

stm32l432kc.elf: setup/*.c lib/printf/printf.c src/test_gpio.c \
	drivers/gpio.o drivers/systick.o
	arm-none-eabi-gcc $(CFLAGS) $(LINKOPTS) $(LDFLAGS) $(LIBS) -o $@ $^

%.o: %.c
	arm-none-eabi-gcc $(CFLAGS) -c $< -o $@

flash: stm32l432kc.elf
	cp $< /mnt/d 

eject:
	sudo umount /mnt/d

clean:
	-rm -f *.elf *.bin *.o drivers/*.o util/*.o .DS_Store

