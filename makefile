CC = gcc
CFLAGS = -Wall -g -lm

PROGRAM = myht
OBJS = main.o libhash.o
DEPS = libhash.h

all = PROGRAM

$(PROGRAM):	$(OBJS)
	$(CC) -o $(PROGRAM) $(OBJS) $(CFLAGS)

main.o: main.c $(DEPS)
	$(CC) -c main.c $(CFLAGS)

libhash.o: libhash.c libhash.h
	$(CC) -c libhash.c $(CFLAGS)

clean:
	rm -rf $(OBJS)

purge:
	rm -rf $(OBJS) $(PROGRAM)