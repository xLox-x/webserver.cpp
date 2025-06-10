server=server.out
objects=$(server)
all:$(objects)
CFLAGS=-std=c++14 -g
LDFLAGS=-lpthread
CC=g++
TCP=$(wildcard tcp/*.cpp)

$(server):echo_server.cpp $(TCP)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

.PHONY:clean
clean:
	rm -f $(objects)
	rm -f *.o