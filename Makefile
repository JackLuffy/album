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


album:$(SRC)
	$(CC) $^ -o $@ $(CPPFLAGS) $(LDFLAGS)

clean:
	$(RM) album

distclean:clean
	$(RM) core .*.sw? src/*.o src/.*.sw?
