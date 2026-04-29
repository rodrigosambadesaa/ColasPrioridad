CC=gcc
CFLAGS=-Wall -Wextra -Werror -std=c11 -O2

OBJ=main.o cola.o colaprio.o

all: app

app: $(OBJ)
	$(CC) $(CFLAGS) -o app $(OBJ)

main.o: main.c colaprio.h cola.h
	$(CC) $(CFLAGS) -c main.c

cola.o: cola.c cola.h
	$(CC) $(CFLAGS) -c cola.c

colaprio.o: colaprio.c colaprio.h cola.h
	$(CC) $(CFLAGS) -c colaprio.c

clean:
	rm -f *.o app
