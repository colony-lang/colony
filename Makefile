# CC=gcc
CC=clang
# CC=musl-clang
CFLAGS=-c -Wall -O0 -g
# CFLAGS=-c -Wall -O3
LDFLAGS=-lm -lpthread
SOURCES=main.c ctx.c object/object.c object/bool.c object/i64.c object/f64.c object/bytes.c object/str.c object/mut_dict.c object/dict.c object/mut_list.c object/list.c object/ns.c object/code.c object/struct.c object/union.c lib/builtins.c
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
