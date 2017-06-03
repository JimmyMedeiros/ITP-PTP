PROG = steg
CC = gcc
CFLAGS = -Wall -ansi -pedantic -std=c11
OBJS = main.o

$(PROG): $(OBJS)
	$(CC) -o $(PROG) $(OBJS) -lm

	main.o:
		$(CC) $(CFLAGS) -c main.c
	clean:
		rm -f core $(PROG) $(OBJS)
