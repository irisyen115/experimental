CC = gcc
CFLAGS = -Wall -pthread

all: deadlock mutex rc

deadlock: deadlock.c
	$(CC) $(CFLAGS) -o deadlock deadlock.cpp

mutex: mutex.c
	$(CC) $(CFLAGS) -o mutex mutex.cpp

rc: rc.c
	$(CC) $(CFLAGS) -o rc rc.cpp

clean:
	rm -f deadlock mutex rc
