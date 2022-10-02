CC=gcc
# CC=clang
# CC=musl-clang
CFLAGS=-c -Wall -O0 -g
LDFLAGS=-lm -lpthread
SOURCES= colony.c main.c
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
