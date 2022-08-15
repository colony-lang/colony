# CC=gcc
CC=clang
# CC=musl-clang
CFLAGS=-c -Wall -O0 -g
# CFLAGS=-c -Wall -O3
LDFLAGS=-lm -lpthread
SOURCES=main.c \
	core/ctx.c \
	core/builtins.c \
	object/object.c \
	object/bytes.c \
	object/module.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=colony

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm $(OBJECTS)
	rm $(EXECUTABLE)
