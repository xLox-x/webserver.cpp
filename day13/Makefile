server=server.out
client=client.out
threadTest=threadTest.out
benchmark=benchmark.out
objects=$(server) $(client) $(threadTest) $(benchmark)
all:$(objects)
SRC=$(wildcard src/*.cpp)
CFLAGS=-std=c++11 -g
LDFLAGS=-lpthread
CC =g++

$(server): server.cpp $(SRC)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

$(client): client.cpp $(SRC)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

$(threadTest): ThreadPoolTest.cpp src/ThreadPool.cpp
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

$(benchmark): benchmark.cpp $(SRC)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

.PHONY:clean
clean:
	rm -f $(objects)
	rm -f *.o