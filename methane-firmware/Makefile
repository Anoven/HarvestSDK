# Makefile created by gnomad

VERSION_INFO = $(shell echo \"Version: `git branch -vv|grep -e ^\*|tail -c +3`\\\\\nCompiled: `date` @`hostname`\")

DATESTAMP = $(shell echo \"`date +%Y\ %m\ %d`\")
TIMESTAMP = $(shell echo \"`date +%H\ %M\ %S`\")

PROG = main
CC = msp430-gcc
CXX = msp430-g++
OBJDUMP = msp430-objdump
OBJCOPY = msp430-objcopy
SIZE = msp430-size
MSPDEBUG = mspdebug 
MSPFLASHER = MSP430Flasher
PYTHONMSP430TOOLS = ../python/bt.py
BTDEV = /dev/rfcomm9
CFLAGS = -Os -O3 -std=gnu99 -Wall -mmcu=msp430fr5969 -DVERSION_INFO=\"$(VERSION_INFO)\" -DTIMESTAMP=\"$(TIMESTAMP)\" -DDATESTAMP=\"$(DATESTAMP)\"
CFLAGS += -Wl,--section-start -Wl,.fram_vars=0xB100
FET = rf2500#tilib --allow-fw-update
GDB = msp430-gdb
GDBTUI = $(GDB)tui
USBDEV = 003:030

OBJS=$(PROG).o pins.o spi.o clock.o cc1200_spi.o  cc1200.o device_info.o rtc.o
#OBJS += acc.o
#cc1200.o cc1200_spi.o clock.o device_info.o vibration.o dma.o 

all: $(PROG).elf  $(PROG).lst
	$(SIZE) --format=SysV $(PROG).elf

.PHONY: all clean install mspdebug debug gdb tui ddd

$(PROG).elf: $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(PROG).elf

%.o: %.cpp
	@$(CXX) $(CFLAGS) -c $< -o $@

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

%.o: %.S
	@$(CC) $(CFLAGS) -c -x assembler-with-cpp $<

%.lst: %.elf
	$(OBJDUMP) -DS $< >$@

clean:
	rm -fr $(PROG).elf $(PROG).hex $(PROG).lst $(OBJS) *.o

install: $(PROG).elf
	$(OBJCOPY) -O ihex $(PROG).elf $(PROG).hex  
	$(MSPDEBUG) $(FET) "prog $(PROG).elf"
	#$(MSPFLASHER) -w "$(PROG).hex" -v -g -z [VCC]
	


bt: $(PROG).elf
	python2 $(PYTHONMSP430TOOLS) -e -r -v -p $(BTDEV)  $(PROG).elf

mspdebug: $(PROG).elf
	$(MSPDEBUG) $(FET)

debug: $(PROG).elf
	$(MSPDEBUG) $(FET) gdb

gdb: $(PROG).elf
	$(GDB) $(PROG).elf
 
tui: $(PROG).elf
	$(GDBTUI) $(PROG).elf
 
ddd: $(PROG).elf
	ddd --debugger $(GDB) $(PROG).elf

main.o: pins.h portmacros.h bitop.h
