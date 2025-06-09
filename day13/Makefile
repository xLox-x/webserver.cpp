objects = server client threadpoll benchmark
all:$(objects)
CFLAGS=-std=c++11 -g
LDFLAGS=-lpthread
CC =g++
SRC=$(wildcard src/*.cpp)

server: $(SRC) server.cpp
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)
	
client: $(SRC) client.cpp
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

threadpoll: $(SRC) ThreadPoolTest.cpp
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

benchmark: $(SRC) benchmark.cpp
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

.PHONY:clean
clean:
	rm -f $(objects)
	rm -f *.o