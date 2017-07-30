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


debug:$(SRC)
	$(CC) $^ -o $@ $(CPPFLAGS) $(LDFLAGS) -DDEBUG

album:$(SRC)
	$(CC) $^ -o $@ $(CPPFLAGS) $(LDFLAGS) -NDEBUG

clean:
	$(RM) album debug

distclean:clean
	$(RM) core .*.sw? src/*.o src/.*.sw?
