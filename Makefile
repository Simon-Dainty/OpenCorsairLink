CC = gcc
LDFLAGS = -L/usr/lib -L/usr/local/lib -lusb-1.0
CFLAGS = -I/usr/include/libusb-1.0 -I/usr/local/include/libusb-1.0
OBJS = corsairlink.o device.o lowlevel_asetek.o lowlevel_hid.o protocol_asetek.o

default: all

all: corsairlink4.elf
	
%.elf: $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@ 

%.o: %.c
	$(CC) $(CFLAGS) -g -c -o $@ $<

clean:
	rm *.elf
