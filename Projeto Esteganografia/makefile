PROG = steg
CC = gcc
CFLAGS = -Wall -ansi -pedantic -std=c11
OBJS = main.o funcoes.o

$(PROG): $(OBJS)
	$(CC) -o $(PROG) $(OBJS) -lm
main.o: funcoes.h
	$(CC) $(CFLAGS) -c main.c
funcoes.o:
	$(CC) $(CFLAGS) -c funcoes.c -lm
clean:
	rm -f core $(PROG) $(OBJS)
