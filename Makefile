CC=clang
# CC=musl-clang
CFLAGS=-c -Wall -O0 -g
# CFLAGS=-c -Wall -O3
LDFLAGS=-lm -lpthread
SOURCES=main.c ctx.c object.c i64.c builtins.c
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
