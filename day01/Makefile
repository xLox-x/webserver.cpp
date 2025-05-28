server=server.out
client=client.out
objects=$(server) $(client)
all:$(objects)

CFLAGS=
LDFLAGS=
CC=g++

$(server): server.cpp
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

$(client): client.cpp
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

.PHONY:clean
clean:
	rm -f $(objects)
	rm -f *.o