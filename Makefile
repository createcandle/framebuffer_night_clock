CC=aarch64-linux-gnu-gcc

CFLAGS = -Wall -pedantic -ansi -static -std=c99
LIBS = -lpng -lz -lm
SRCS = fbclock.c framebuffer.c
HEADERS = fbclock.h framebuffer.h pngimage.h

.PHONY: all clean


all: fbclock


fbclock: $(SRCS) $(HEADERS)
	$(CC) $(CFLAGS) $(INCFLAGS) $(LIBFLAGS) -o $@ $(SRCS) $(LIBS)

clean:
	rm -f fbclock *~


