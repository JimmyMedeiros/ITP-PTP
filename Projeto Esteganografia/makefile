PROG = steg
CC = gcc
CFLAGS = -Wall -ansi -pedantic -std=c11
OBJS = main.o cipher.o ppm.o bmp.o gif.o

$(PROG): $(OBJS)
	$(CC) -o $(PROG) $(OBJS)
	rm -f $(OBJS)
main.o: cipher.o ppm.o bmp.o gif.o
	$(CC) $(CFLAGS) -c main.c
cipher.o:
	$(CC) $(CFLAGS) -c ./libraries/cipher.c
ppm.o: cipher.o
	$(CC) $(CFLAGS) -c ./libraries/ppm.c
bmp.o: cipher.o
	$(CC) $(CFLAGS) -c ./libraries/bmp.c
gif.o: cipher.o
	$(CC) $(CFLAGS) -c ./libraries/gif.c
clean:
	rm -f $(OBJS)
