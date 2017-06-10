PROG = steg
CC = gcc
CFLAGS = -Wall -ansi -pedantic -std=c11
OBJS = main.o cipher.o ppm.o bmp.o

$(PROG): $(OBJS)
	$(CC) -o $(PROG) $(OBJS) -lm
	rm -f $(OBJS)
main.o: cipher.o ppm.o bmp.o 
	$(CC) $(CFLAGS) -c main.c
cipher.o:
	$(CC) $(CFLAGS) -c ./libraries/cipher.c -lm
ppm.o: cipher.o
	$(CC) $(CFLAGS) -c ./libraries/ppm.c -lm
bmp.o: cipher.o
	$(CC) $(CFLAGS) -c ./libraries/bmp.c -lm
clean:
	rm -f $(OBJS)
