CC = gcc
CFLAGS = -c -Wall -std=c99
OBJECTS = main.o
LIBRARY = -lncurses

main: $(OBJECTS)
	$(CC) -o main $(OBJECTS) $(LIBRARY) && ./main

main.o: main.c
	$(CC) $(CFLAGS) main.c


clean:
	rm *.o main *.out
