server=server.out
client=client.out
objects=$(server) $(client)
all:$(objects)
SERVER_SRC=$(wildcard src/*.cpp)
CLIENT_SRC=src/util.cpp client.cpp
CFLAGS=
LDFLAGS=
CC=g++

$(server): server.cpp $(SERVER_SRC)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

$(client): $(CLIENT_SRC)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

.PHONY:clean
clean:
	rm -f $(objects)
	rm -f *.o