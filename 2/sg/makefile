CC = gcc
CFLAGS = -std=c2x \
  -Wall -Wconversion -Werror -Wextra -Wpedantic -Wwrite-strings \
  -O2 \
  -D_POSIX_C_SOURCE=200809L
LDFLAGS = -lX11
objects = sg.o sg_test.o
executable = sg_test

.PHONY: all clean

all: $(executable)

clean:
	$(RM) $(objects) $(executable)

$(executable): $(objects)
	$(CC) $(objects) $(LDFLAGS) -o $(executable)

sg.o: sg.c sg.h
sg_test.o: sg_test.c sg.h
