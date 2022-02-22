CC = gcc
CFLAGS = -c -Wall -std=c99
OBJECTS = main.o
LIBRARY = -lncurses
BINS = hss

.PHONY: clean

main: $(OBJECTS)
	$(CC) -o $(BINS) $(OBJECTS) $(LIBRARY) 

clean:
	rm -f *.o hss 
