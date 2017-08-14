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


album.out:$(SRC)
	$(CC) $^ -o $@ $(CPPFLAGS) $(LDFLAGS) -NDEBUG

debug.out:$(SRC)
	$(CC) $^ -o $@ $(CPPFLAGS) $(LDFLAGS) -DDEBUG

clean:
	$(RM) *.out src/*.o

distclean:clean
	$(RM) core .*.sw? src/.*.sw?
