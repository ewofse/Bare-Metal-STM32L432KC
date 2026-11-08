CPU 	 = -mcpu=cortex-m4 -mthumb
INCLUDES = -I. -Idrivers -Istm32l432kc -Im4 -Isetup -Iutil -Ilib/printf

OPTS 	 = -Os
LTOPTS 	 = -fdata-sections -ffunction-sections

LINKOPTS = -nostartfiles -Wl,--gc-sections
LDFLAGS  = -T stm32l432kc.ld
LIBS 	 = 

CFLAGS   = -std=c99 -ffreestanding -pedantic \
		   $(CPU) $(OPTS) $(INCLUDES) $(LTOPTS) -Wall 

OPENOCD  = openocd -f interface/stlink.cfg -f target/stm32l4x.cfg
SERIAL   = /dev/ttyACM0
BAUD     = 115200

.PHONY: flash term gdbserver gdb clean

stm32l432kc.elf: setup/*.c lib/printf/printf.c src/test_spi.c \
	drivers/spi.o drivers/led.o drivers/usart.o drivers/systick.o \
	drivers/gpio.o drivers/gpio_irq.o util/cbuffer.o
	arm-none-eabi-gcc $(CFLAGS) $(LINKOPTS) $(LDFLAGS) $(LIBS) -o $@ $^

%.o: %.c
	arm-none-eabi-gcc $(CFLAGS) -c $< -o $@

clean:
	-rm -f *.elf *.bin *.o drivers/*.o util/*.o

flash: stm32l432kc.elf
	$(OPENOCD) -c "program $< verify reset exit"

term:
	screen $(SERIAL) $(BAUD)

gdbserver:
	$(OPENOCD)

gdb: stm32l432kc.elf
	arm-none-eabi-gdb $< -ex "target extended-remote :3333"

