vpath %.c = src/
vpath %.h = inc/

SRC += $(wildcard *.c)
SRC += $(wildcard src/*.c)

CROSS = arm-none-linux-gnueabi-
CC = $(CROSS)gcc

CPPFLAGS += -I inc/
CPPFLAGS += -I inc/jpeg/

LDFLAGS += -L lib/
LDFLAGS += -ljpeg


album.elf:$(SRC)
	$(CC) $^ -o $@ $(CPPFLAGS) $(LDFLAGS) -NDEBUG

debug.elf:$(SRC)
	$(CC) $^ -o $@ $(CPPFLAGS) $(LDFLAGS) -DDEBUG

clean:
	$(RM) *.elf src/*.o

distclean:clean
	$(RM) core .*.sw? src/.*.sw?
