objects=server.out
all:$(objects)
CFLAGS=-std=c++14 -g
LDFLAGS=-lpthread
CC=g++
TCP=$(wildcard tcp/*.cpp)

$(objects): $(TCP) echo_server.cpp
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

.PHONY:clean
clean:
	rm -f $(objects)
	rm -f *.o