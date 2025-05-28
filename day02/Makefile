server=server.out
client=client.out
objects=$(server) $(client)
all:$(objects)
SRC= util.cpp
CFLAGS=
LDFLAGS=
CC=g++

$(server): server.cpp $(SRC)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

$(client): client.cpp $(SRC)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

.PHONY:clean
clean:
	rm -f $(objects)
	rm -f *.o