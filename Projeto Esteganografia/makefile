PROG = steg
CC = gcc
CFLAGS = -Wall -ansi -pedantic -std=c11
OBJS = main.o ppm.o cipher.o

$(PROG): $(OBJS)
	$(CC) -o $(PROG) $(OBJS) -lm
	rm -f $(OBJS)
main.o: ppm.h cipher.h
	$(CC) $(CFLAGS) -c main.c
ppm.o: cipher.h
	$(CC) $(CFLAGS) -c ./libraries/ppm.c -lm
cipher.o:
	$(CC) $(CFLAGS) -c ./libraries/cipher.c -lm
clean:
	rm -f $(OBJS)
