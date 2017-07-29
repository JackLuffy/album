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

debug:$(SRC)
	$(CC) $^ -o $@ $(CPPFLAGS) $(LDFLAGS) -DDEBUG

clean:
	$(RM) album debuge

distclean:clean
	$(RM) core .*.sw? src/*.o src/.*.sw?
