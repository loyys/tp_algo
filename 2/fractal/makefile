point_dir = ../point/
sg_dir = ../sg/
CC = gcc
CFLAGS = -std=c2x \
  -Wall -Wconversion -Werror -Wextra -Wpedantic -Wwrite-strings \
  -O2 \
  -D_POSIX_C_SOURCE=200809L -I$(point_dir) -I$(sg_dir)
LDFLAGS = -lX11 -lm
vpath %.c $(point_dir):$(sg_dir)
vpath %.h $(point_dir):$(sg_dir)
objects = fractal.o main.o point.o sg.o
executable = fractal

.PHONY: all clean

all: $(executable)

clean:
	$(RM) $(objects) $(executable)

$(executable): $(objects)
	$(CC) $(objects) $(LDFLAGS) -o $(executable)

fractal.o: fractal.c point.h sg.h fractal.h
main.o: main.c sg.h fractal.h
point.o: point.c point.h
sg.o: sg.c sg.h
