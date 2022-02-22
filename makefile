CC = gcc
CFLAGS = -c -Wall -std=c99
OBJECTS = hss.o
LIBRARY = -lncurses
BINS = hss

.PHONY: clean

all: $(OBJECTS)
	$(CC) -o $(BINS) $(OBJECTS) $(LIBRARY) 

clean:
	rm -f *.o hss 
