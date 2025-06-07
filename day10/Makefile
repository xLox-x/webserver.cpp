server=server.out
client=client.out
threadTest=threadTest.out
objects=$(server) $(client) $(threadTest)
all:$(objects)
SRC=$(wildcard src/*.cpp)
CFLAGS=
LDFLAGS=-pthread
CC=g++

$(server): server.cpp $(SRC)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

$(client): client.cpp $(SRC)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

$(threadTest): ThreadPoolTest.cpp src/ThreadPool.cpp
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

.PHONY:clean
clean:
	rm -f $(objects)
	rm -f *.o