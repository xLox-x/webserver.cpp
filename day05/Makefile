server=server.out
client=client.out
objects=$(server) $(client)
all:$(objects)
SERVER_SRC=util.cpp server.cpp Epoll.cpp InetAddress.cpp Socket.cpp Channel.cpp
CLIENT_SRC=util.cpp client.cpp
CFLAGS=
LDFLAGS=
CC=g++

$(server): $(SERVER_SRC)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

$(client): $(CLIENT_SRC)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

.PHONY:clean
clean:
	rm -f $(objects)
	rm -f *.o