OBJ := main.o list.o
CC = gcc
CFLAGS =-c -Wall -I./include
LDFLAGS =
PROG = richard

all: $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $(PROG)

main.o: ./src/main.c
	$(CC) $(CFLAGS) ./src/main.c

list.o: ./src/list.c
	$(CC) $(CFLAGS) ./src/list.c

clean:
	rm ./richard *.o
