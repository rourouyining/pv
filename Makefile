CC=gcc

OBJ=$(patsubst %.c,%.o,$(wildcard *.c))

INCLUDE=
CFLAGES=-g -Wall
LIB=

target=test

all:$(OBJ)
	$(CC) $^ -o $(target) $(LIB)

%.o:%.c
	$(CC) $(CFLAGES) -c $< -o $@ $(INCLUDE)

clean:
	rm -rf *.o $(target)
