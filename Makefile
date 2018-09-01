CC=gcc

OBJ=$(filter-out test.o, $(patsubst %.c,%.o,$(wildcard *.c)))

INCLUDE=
CFLAGES=-g -Wall
LIB= -lpthread

target=pv

all:$(OBJ)
	$(CC) $^ -o $(target) $(LIB)

%.o:%.c
	$(CC) $(CFLAGES) -c $< -o $@ $(INCLUDE)

clean:
	rm -rf *.o $(target)
