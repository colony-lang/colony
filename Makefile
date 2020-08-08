CC=gcc
CFLAGS=-c -Wall -O0 -g
LDFLAGS=-lm -lpthread
SOURCES=colony.c vm.c
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
